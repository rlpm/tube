// Stonecutters CS351 S03 -*- C++ -*-

#include <algorithm> // for find
#include "Water.h"
#include "Boat.h"
#include "City.h"
#include "Army.h"
#include "Empire.h"
#include "Static.h"

Boat::Boat(Empire *e, int i, Order::UnitType u)
  : Mobile(e,Order(u,Order::XP,Coord(0,0),0)), _cap(i), _maxcap(i) {}

void Boat::Sail(){
  if (GetLoc() != GetOrder().GetCoord()) {
    MoveTo(false); // Move to a floatable location
    UpdateMarines(); // marines must be moved otherwise they fall off boat.
  }
}

void Boat::Explore(){
  Neighborhood n = GetHolder()->GetNeighborhood();
  vector<Active*> armies;
  vector<Boat*> lesserboat; // We don't see a way around dynamic casting here...
  vector<Static*> floatables; 
 
  Boat* tempboat;
  for(int i = 0; i < 8; i++){
    Static *temp = dynamic_cast<Static*>(n[i]);
    tempboat = dynamic_cast<Boat*>(temp->GetVisible());
    if(tempboat!=NULL && !(GetEmpire()->IsAllyOf(tempboat->GetEmpire()))){
      // check for a Boat
      if(tempboat->MaxCap() < MaxCap())        // see if it's a smaller boat
	lesserboat.push_back(tempboat);}
    else if(temp->IsAttackable(this)){ // only attackable things left are armies
      if(!(temp->IsPrioAttack(this))) // boats can't attack cities
	armies.push_back(temp->GetVisible());
    }else if(temp->IsFloat())
      floatables.push_back(temp); // fill vector with places we could float to
  }
  if(armies.size()){  // first try to attack armies
    Attack(armies[random() % armies.size()],false);
    return;
  }
  if(lesserboat.size()){ // then try to attack smaller boats
    Attack(lesserboat[random() % lesserboat.size()],false);
    return;
  }
  
  if(floatables.size()>0) { // finally try to move 
    Move(floatables[random() % floatables.size()]);
    UpdateMarines();
  }
}

void Boat::Defend(){
  //repairs and hold done in update
  vector<Active*> attackables; // holder for armies
  vector< vector<Boat*> > boats;
 
  Neighborhood n = GetHolder()->GetNeighborhood();  // examine neighborhood
  
  Boat * tempboat;
  // this loop is similar to explore except we could attack any boat
  for(int i=0; i<8; i++) {
    Static *temp = dynamic_cast<Static*>(n[i]);
    tempboat = dynamic_cast<Boat*>(temp->GetVisible());
    if(tempboat && !(GetEmpire()->IsAllyOf(tempboat->GetEmpire()))) {
      while (boats.size() < (static_cast<size_t>(tempboat->MaxCap() + 1))) {
	vector<Boat*> tmp;
	boats.push_back(tmp);
      }
      boats[tempboat->MaxCap()].push_back(tempboat);
    } else if(temp->IsAttackable(this) && !temp->IsPrioAttack(this)) {
      attackables.push_back(temp->GetVisible());  
    }
  }
  
  if(attackables.size()>0){
    Attack(attackables[random() % attackables.size()],false);
  } else if(boats.size()) {
    for (size_t i = 0; i< boats.size();i++) {
      if (boats[i].size()) {
	Attack(boats[i][random() % boats[i].size()],false);
	break;
      }
    }
  } else { // if there is nothing to defend we sail on
    Sail();
  }
}

bool Boat::AllyCities(){
  vector<City*> cities; 
  Neighborhood n=GetHolder()->GetNeighborhood();
  for(int i=0; i<8; i++) {
    if(City * C =dynamic_cast<City*>(n[i]))
      cities.push_back(C);
  }
  if(!cities.size()) return false;

// if we are allied to any of the cities, return true
  for(unsigned int i=0; i<cities.size(); i++) {
    if(GetEmpire()->IsAllyOf(cities[i]->GetEmpire())) {
      return true;
    }
  }
 
  return false;

}

void Boat::Update() {
  if(_cap < _maxcap) { //Repairs
    _cap++;

    //if there is an allied city then we increase _cap again
    if(AllyCities())
      _cap++;
  }

  if(GetOrder().GetCt()) {
    GetOrder().DecCt(1);
    return;
  }
  
  if(GetOrder().GetCmd() == Order::SL)
    Sail();
  else if(GetOrder().GetCmd() == Order::DF)
    Defend();
  else if(GetOrder().GetCmd() == Order::XP)
    Explore();
  
  // Army inside boats need to check for standing orders 
  for(list<Army*>::iterator i = _marines.begin(); i != _marines.end(); i++) {
    (*i)->GetStandingOrders();
  }
  
  // need to check for standing order
  GetHolder()->GetStandingOrder(GetEmpire(),GetOrder());
}

void Boat::PlaceArmy(Army* A){
  if(_marines.size() >= static_cast<size_t>(_cap))
    assert(0); // IsWalkable should have returned false;

  _marines.push_back(A);
  A->SetHolder(GetHolder());
  A->SetBoat(this);
}

void Boat::RemoveArmy(Army* A) {
  list<Army*>::iterator i = find(_marines.begin(),_marines.end(),A);
  assert(i!=_marines.end()); // make sure we found it
  _marines.erase(i);
  A->SetHolder(NULL);
  A->SetBoat(NULL);
}

bool Boat::GetHitBy(Active*){
  if (_marines.size() == static_cast<size_t>(_cap)){
    list<Army*>::iterator dead = _marines.begin();
    delete (*dead); // kill a marine from the boat
  }
  _cap--; // decrease the current capacity
  if(_cap <=0) { // check if we sunk
    GetHolder()->RemoveMobile(this);
    delete this;
    return false;
  }
  return true; // return true if we survived
}

// make sure not to drop armies into the drink
void Boat::UpdateMarines() {
  for (list<Army*>::iterator i = _marines.begin(); i != _marines.end() ; i++) {
    (*i)->SetHolder(GetHolder());  
  }
}
