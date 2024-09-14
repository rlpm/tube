// Stonecutters CS351 S03 -*- C++ -*-

#include "Active.h"
#include "Empire.h"
#include "Static.h"

Active::Active(Empire* me,Order o):_o(o), _w_loc(0) {
  assert(me);
  me->AddActive(this);
  _id=me->GetWorld()->NextSerial();
}

Active::~Active() {
  _e->RemoveActive(this);
}

bool Active::IsAttackable(Active* enemy) const {
  return !(GetEmpire()->IsAllyOf(enemy->GetEmpire()));
}

ContactsMsg::Active Active::GetActive() {
  return ContactsMsg::Active(GetLoc(),GetId(),Hits(),GetOrder());
}

ContactsMsg::Contact Active::GetContact() {
  return ContactsMsg::Contact(GetLoc(),_o.GetUnit(),GetEmpire()->GetId());
}

bool Active::GetStandingOrders() {
  Order t(_o);
  if (GetHolder()->GetStandingOrder(GetEmpire(),t)) {
    SetOrder(t);
    return true;
  }
  return false;
}

void Active::SetOrder(Order o) {
  if (o.GetUnit() != _o.GetUnit()) return; // ignore messages for wrong guy
  _o = o;
  // make sure city rates are set
  _o._reset_count();
}
