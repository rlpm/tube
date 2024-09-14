// Stonecutters CS351 S03 -*- C++ -*-
// $Id: Water.C,v 1.12 2003/05/13 22:43:30 rory Exp $

#include "Water.h"
#include "Boat.h"
#include "Army.h"

bool Water::IsFloat() const {
  return (_boat == NULL);
}


bool Water::IsWalk(Active* a) const {
  if(_boat == NULL)             // Army's can't walk on water
    return false;
  if(a->GetEmpire() != _boat->GetEmpire()) // Don't get on an
    return false;                          //  enemy's boat.
  return (!(_boat->IsFull()));  // Don't walk onto a full boat
}

void Water::PlaceMobile(Mobile *M){
  Boat* B = dynamic_cast<Boat*>(M); // check if it's a boat
  if (B) {
    assert(!_boat);                 // paranoia about replacing a boat
    _boat = B;                      // set our pointer to new boat
    M->SetHolder(this);             // set boats pointer to 'this'
  } else {
    assert(_boat);                   // paranoia for boat
    Army *A = dynamic_cast<Army*>(M);// check for some army
    assert (A);
    _boat->PlaceArmy(A);             // place army in boat
  }
}

void Water::RemoveMobile(Mobile *M) {
  Boat* B = dynamic_cast<Boat*>(M);
  if (B) {
    if (_boat != M) assert(0); // trying to remove boat that isn't here
    M->SetHolder(NULL);        // remove boat's knowledge of 'this'
    _boat = NULL;
  } else {
    Army *A = dynamic_cast<Army*>(M); 
    assert (A);               // make sure there's an army there
    _boat->RemoveArmy(A);     // remove it
  }
}

// returns whether or not there is a boat and if it is attackable by allegiance
bool Water::IsAttackable(Active *e) const {
  if (_boat) return _boat->IsAttackable(e);
  else return false;
}
