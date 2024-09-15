// Stonecutters CS351 S03 -*- C++ -*-

#include <algorithm>
#include "Empire.h"
#include "Commander.h"
#include "SvrContactsMsg.h"
#include "Active.h"
#include "Static.h"
#include "Mobile.h"

Empire::Empire(World* W) :_w(W)
{
  _w->AddEmpire(this);
}

Empire::~Empire()
{
  // destroy all actives, keepalives first, so we don't accidentally remove
  // a boat before it's marines
  for (std::list<Active*>::iterator i = _actives.begin(); i != _actives.end();) {
    std::list<Active*>::iterator j(i);
    i++;
    if ((*j)->KeepAlive()) {
      Mobile *m = dynamic_cast<Mobile*>(*j);
      if (m) {
	m->GetHolder()->RemoveMobile(m);
      }
      delete *j;
    }
  }

  // do it again - this time, should be all boats
  for (std::list<Active*>::iterator i = _actives.begin(); i != _actives.end();) {
    std::list<Active*>::iterator j(i);
    i++;
    Mobile *m = dynamic_cast<Mobile*>(*j);
    assert(m);
    m->GetHolder()->RemoveMobile(m);
    delete *j;
  }

  // place commanders in allied empires
  for (std::list<Commander*>::iterator i = _cmdrs.begin(); i != _cmdrs.end();) {
    std::list<Commander*>::iterator j(i);
    i++;
    _w->ReassignCommander(*j,this);
  }
  
  // remove this from the world's list
  _w->RemoveEmpire(this);
}

void Empire::Broadcast(Message &m) const {
  for (std::list<Commander*>::const_iterator i = _cmdrs.begin(); i != _cmdrs.end(); i++)
    (*i)->Notify(m);
}

void Empire::AddActive(Active* a)
{
  _actives.push_back(a);
  _w->AddActive(a);
  a->_e = this;
}

void Empire::RemoveActive(Active* a)
{
  std::list<Active*>::iterator i = find(_actives.begin(),_actives.end(),a);
  assert (i!=_actives.end());
  _actives.erase(i);
  a->_e = NULL;
  _w->RemoveActive(a);
}

void Empire::RequestAlly(size_t emp_id, bool yesno)
{
  _allies[emp_id]=yesno;
}

void Empire::AddCommander(Commander *c) {
  _cmdrs.push_back(c);
  c->_empire = this;
}

void Empire::RemoveCommander(Commander *c) {
  std::list<Commander*>::iterator i = find(_cmdrs.begin(),_cmdrs.end(),c);
  assert(i!=_cmdrs.end());
  _cmdrs.erase(i);
  c->_empire = NULL;
}

void Empire::SendContactsMsg() {
  std::vector<ContactsMsg::Contact> c;
  std::vector<ContactsMsg::Terrain> t;
  std::vector<ContactsMsg::Active> a;
  for (std::list<Active*>::const_iterator i = _actives.begin(); i != _actives.end(); i++) {
    a.push_back((*i)->GetActive());
    Neighborhood n = (*i)->GetHolder()->GetNeighborhood();
    for (size_t j=0;j<8;j++) {
      Static *s = dynamic_cast<Static*>(n[j]);
      assert(s);
      Active *act = s->GetVisible();
      if (act) {
	if (act->GetEmpire() != this) {
	  ContactsMsg::Contact who = act->GetContact();
	  std::vector<ContactsMsg::Contact>::iterator found =
	    find(c.begin(),c.end(),who);
	  if (found == c.end())
	    c.push_back(act->GetContact());
	}
      } else {
	bool notseen = true;
	ContactsMsg::Terrain tmp = s->GetTerrain(this,notseen);
	if (notseen) t.push_back(tmp);
      }
    }
  }

  SvrContactsMsg ob(c,t,a);
  Broadcast(ob);
}

bool Empire::Do(int id, Order o) {
  std::list<Active*>::const_iterator i = _actives.begin();
  for (; i != _actives.end(); i++) {
    if ((*i)->GetId() == id) {
      (*i)->SetOrder(o);
      return true;
    }
  }
  if (i == _actives.end())
    return false;
}

void Empire::Tell(Coord c, std::vector<Order> o) {
  GetWorld()->Tell(this,c,o);
}

bool Empire::IsAllyOf(Empire *e) const {
  if(e == this) {
    return true; // no fragging
  } else {
    // check for friendly fire
    bool iwantally = _allies[e->GetId()];
    bool theywantally = e->_allies[GetId()];
    bool bothwant = iwantally && theywantally;
    return (bothwant);
  }
}

bool Empire::CheckAlive() const
{
  for (std::list<Active*>::const_iterator i = _actives.begin();
       i != _actives.end();
       i++) {
    if ((*i)->KeepAlive()) return true;
  }
  return false;
}
