// Stonecutters CS351 S03 -*- C++ -*-

#include "Static.h"
#include "Army.h"
#include "Neighborhood.h"
#include "Grid.h"
#include "Boat.h"

Army::Army(Empire *E):Mobile(E,Order(Order::AR, Order::XP, Coord(0,0), 0)),
		      _carrier(NULL){}
Army::~Army(){
  if (_carrier) {
    _carrier->RemoveArmy(this);
  }
}

bool Army::Explore(){
  vector<Static*> walkables;
  Neighborhood n = GetHolder()->GetNeighborhood(); //get the neighborhood

  // try to attack!
  bool stillalive = true;
  if(FindAttackable(n,stillalive)) return stillalive;

  //still have to do the walk stuff on the explore command
  for(int i=0; i<8; i++) {
    Static *temp = dynamic_cast<Static*>(n[i]);
    assert(temp);
    if(temp->IsWalk(this))
      walkables.push_back(temp);
  }
  if(walkables.size()>0) {
    Move(walkables[random() % walkables.size()]);
  }
  return true;
}


bool Army::Defend(){
  Neighborhood n = GetHolder()->GetNeighborhood();

  // try to attack!
  bool stillalive = true;
  if(FindAttackable(n,stillalive)) return stillalive;

  // nothing to defend so we'll move on.
  return March();
}

bool Army::March(){
  Coord dest = GetOrder().GetCoord();
  if (GetLoc() != dest)
    Mobile::MoveTo(true); // Move to a walkable location

  return true;
}

void Army::Update(){
  Order O=GetOrder();
  bool keepgoing = true;
  if(O.GetCmd() == Order::XP) {
    keepgoing = Explore();
  } else if(O.GetCmd() == Order::DF) {
    keepgoing = Defend();
  } else if(O.GetCmd() == Order::MA) {
    keepgoing = March();
  } else if(O.GetCmd() == Order::WT) {
    // don't do anything for wait
  }

  if (keepgoing) {
    GetStandingOrders();
  } // else we were deleted!
}


bool Army::GetHitBy(Active*){
  GetHolder()->RemoveMobile(this);
  delete this; // Die!
  return false;
}

bool Army::FindAttackable(Neighborhood n, bool &stillalive){
  vector<Static*> priorities;  // holder for cities
  vector<Static*> attackables;
  
  for(int i=0; i<8; i++) {
    Static *temp = dynamic_cast<Static*>(n[i]);
    assert(temp);
    if(temp->IsPrioAttack(this)) {
      priorities.push_back(temp);  //found a city to attack
    } else if(temp->IsAttackable(this)) {
      attackables.push_back(temp); //found an attackable
    }
  }
  if(priorities.size()>0) {
    int temp = random() % priorities.size();
    stillalive = Attack(priorities[temp]->GetVisible(), true, true);
    return true;
  } else if(attackables.size()>0) {
    int temp = random() % attackables.size();
    stillalive = Attack(attackables[temp]->GetVisible(), true, true);
    return true;
  } else { 
    return false;
  }
}

void Army::SetBoat(Boat *b) {
  if (b) assert(_carrier== NULL); // make sure we aren't in a boat
  else assert(_carrier);          // make sure we are in a boat
  _carrier = b;
}
