// Stonecutters CS351 S03 -*- C++ -*-
// $Id: Land.C,v 1.12 2003/05/13 22:43:30 rory Exp $

#include <stddef.h>
#include "Land.h"
#include "Army.h"
#include "Coord.h"

// Return whether or not there is an army
bool Land::IsWalk(Active* a) const {
  return(_army == NULL);
}

// Move army into this particular static
void Land::PlaceMobile(Mobile *M) {
  if (_army) assert(0); // someone already here!
  Army* A = dynamic_cast<Army*>(M);
  assert(A);
  _army = A;
  A->SetHolder(this);
}

// Remove army from this static
void Land::RemoveMobile(Mobile *M) {
  if (_army != M) assert(0); // trying to remove a guy that isn't here
  _army->SetHolder(NULL);
  _army = NULL;
}

// test to see if whatever is contained can be attacked, based on allegiance
bool Land::IsAttackable(Active *e) const {
  if (_army) return _army->IsAttackable(e);
  else return false;
}
