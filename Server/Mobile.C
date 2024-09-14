// Stonecutters CS351 S03 -*- C++ -*-

#include <stddef.h>
#include "Mobile.h"
#include "Static.h"
#include "Empire.h"

Mobile::Mobile(Empire* E, Order o): Active(E,o) {}

Mobile::~Mobile(){
}

void Mobile::Move(Static * s){
  _holder->RemoveMobile(this);
  s->PlaceMobile(this);  //s is the destination point
}

void Mobile::MoveTo(bool is_walk) {
  Coord dest = GetOrder().GetCoord();
  Static *newholder = GetHolder()->MinMove(is_walk, dest, this);
  if (!newholder) return; //nowhere to go
  GetHolder()->RemoveMobile(this);
  newholder->PlaceMobile(this);
}

Coord Mobile::GetLoc() {
  Coord c;
  bool goodloc = GetHolder()->GetLoc(c);
  assert (goodloc);
  return c;
}

bool Mobile::Attack(Active* A, bool walk, bool prio)
{
  int threshold = 55; // boats don't prioritize attacking
  int temprand;
  
  if(prio)
    threshold = 25;

  temprand = rand() % 99;
  if(temprand < threshold) {
    Static * S = A->GetHolder();
    assert(S);
    A->GetHitBy(this);  
    
    if((walk && S->IsWalk(this)) || (!walk && S->IsFloat())) {
      GetHolder()->RemoveMobile(this);
      S->PlaceMobile(this);
    }
  } else {
    return GetHitBy(A);
  }
  return true;
}
