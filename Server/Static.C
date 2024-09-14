// Stonecutters CS351 S03 -*- C++ -*-
#include "Mobile.h"
#include "Static.h"
#include "City.h"
#include "Land.h"
#include "Water.h"
#include "Empire.h"
#include <cassert>

bool Static::IsFloat() const
{
   return false;
}

bool Static::IsWalk(Active* a) const
{
   return false;
}

bool Static::IsAttackable(Active* e) const
{
  return false;
}

bool Static::IsPrioAttack(Active* e) const
{
  return false;  //this is to check for city's
}

Static* Static::MinMove(bool is_walk,Coord to, Active* a) {
  Neighborhood n = GetNeighborhood();

  vector<GridAble*> ok;
  for (Neighborhood::iterator i = n.begin() ; i != n.end() ; i++) {
    Static *stmp = dynamic_cast<Static*>(*i);
    assert(stmp);
    if ((is_walk && stmp->IsWalk(a)) || (!is_walk && stmp->IsFloat())) {
	ok.push_back(*i);  
      }
  }
  if (!ok.size()) return NULL;
  GridAble *tmp = GetGrid()->MinDist(ok,to);
  Static *ret = dynamic_cast<Static*>(tmp);
  assert(ret);
  return ret;
}

bool Static::GetStandingOrder(Empire *e, Order &o) const
{
  vector<Order> ord =  _orders[e->GetId()];
  for(int i = ord.size() - 1; i >= 0; i--){
    if(ord[i].GetUnit() == o.GetUnit()){
      o = ord[i];
      return true;
    }
  }
  return false;
}

ContactsMsg::Terrain Static::GetTerrain(Empire *e, bool &notseen) {
  notseen = !_seen[e->GetId()];
  _seen[e->GetId()] = true;
  Coord c;
  bool goodc = GetLoc(c);
  assert(goodc);
  ContactsMsg::Terrain t(c,_type);
  return t;
}
