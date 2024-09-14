// Stonecutters CS351 S03 -*- C++ -*-

#include <stdlib.h>
#include "Terrain.h"
#include "Curse.h"
#include "Control.h"

Terrain::Terrain(Control *cn, ContactsMsg::Terrain t)
  :_control(cn), _t(t) {}

Terrain::Terrain(Control *cn, ContactsMsg::Active a)
  :_control(cn), _t(a.GetCoord(), Underneath(a.GetOrder().GetUnit()))
{
  _a.push_back(a);
}

Terrain::Terrain(Control *cn, ContactsMsg::Contact c)
  :_control(cn), _t(c.GetCoord(), Underneath(c.GetType()))
{
  _c.push_back(c);
}

void Terrain::Output(Curse *s,Coord c) {
  char w = ' ';
  int color = 0, base = 1;

  // can't have both good and bad guys
  assert(!(_a.size()&&_c.size()));
  
  // can't have more than one bad guy
  assert(!(_c.size()&&(_c.size()!=1)));

  // can't have anything on a mountain
  assert (_t.GetType() != ContactsMsg::Terrain::MT || (_a.size() + _c.size() == 0));

  if (!s->HasColor()) {
    switch (_t.GetType()) {
    case ContactsMsg::Terrain::LD: w = '+';break;
    case ContactsMsg::Terrain::WA: w = '~';break;
    case ContactsMsg::Terrain::MT: w = '%';break;
    default: assert(0); break;
    }      
  } else {
    switch (_t.GetType()) {
    case ContactsMsg::Terrain::LD: color=0;break;
    case ContactsMsg::Terrain::WA: color=1;break;
    case ContactsMsg::Terrain::MT: color=1;base=0;break;
    default: assert(0); break;
    }      
  }

  if (_a.size() || _c.size()) {
    Order::UnitType who;
    if (_c.size()) who = (*(_c.begin())).GetType();
    else who = (*(_a.begin())).GetOrder().GetUnit();

    switch (who) {
    case Order::CT: w = 'c'; break;
    case Order::AR: w = 'a'; break;
    case Order::CR: w = 'r'; break;
    case Order::DE: w = 'd'; break;
    case Order::EM: w = 'e'; break;
    default: assert(0);
    }
    if (_a.size()) {
      w = toupper(w);
    } else {
      if (_control->IsAlly((*(_c.begin())).GetEmp())) {
	base = 2;
      } else {
	base = 3;
      }
    }
  }

  s->PutColorCharAt(c.GetX(),c.GetY(),w,color,base);
}

ContactsMsg::Terrain::Type Terrain::Underneath(Order::UnitType u) {
  switch (u) {
  case Order::CT: return ContactsMsg::Terrain::LD; break;
  case Order::AR: return ContactsMsg::Terrain::LD; break;
  case Order::DE: return ContactsMsg::Terrain::WA; break;
  case Order::CR: return ContactsMsg::Terrain::WA; break;
  case Order::EM: return ContactsMsg::Terrain::WA; break;
  default: assert(0); break;
  }
}
