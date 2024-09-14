// Stonecutters C2351 S03 -*- C++ -*-

#include <iostream>
#include "City.h"
#include "Army.h"
#include "Cruiser.h"
#include "Destroyer.h"
#include "Emperor.h"
#include "Empire.h"

City::City(Empire* e) : Active(e,Order(Order::CT, Order::GR, Coord(0,0), 60)),
			Static(ContactsMsg::Terrain::__TR_END__), _size(1) {}

City::~City(){}

void City::Grow(){
  int _growth = 0;
  if (_size!=1)
    _growth = rand()%(_size * _size);
  if(!_growth)
    _size += 1;
}

// updates based on the order code within contained 'Order'
void City::Update(){
  if (GetOrder().GetCt()) { // still have work to do
    if(GetOrder().GetCt() > _size){
      // do a little work then quit
      GetOrder().DecCt(_size);
      return;
    } else {
      // set to 0 work remaining
      GetOrder().DecCt(GetOrder().GetCt());
    }
  }

  bool getstandingorders = true;

  if (GetOrder().GetCmd() == Order::GR) {
    Grow();
  } else {
    // do the actual building
    getstandingorders = Build(GetOrder().GetCmd());
  }
    
  if (getstandingorders) {
    if (!GetStandingOrders()) {
      // if no standing order, reset the current order
      Order newo(GetOrder());
      newo._reset_count(); // make sure to reset city work
      SetOrder(newo);
    }
  }
}

// done updating, time to make something
bool City::Build(Order::CmdType which){
  Neighborhood current = GetNeighborhood();
  vector<Static*> validloc;

  // check for valid spots to place unit
  for(int ct = 0; ct <8; ct++){
    Static* temp = dynamic_cast<Static*>(current[ct]);
    assert(temp);
    if((which == Order::BA && temp->IsWalk(this)) ||
       (which != Order::BA && temp->IsFloat())) {
      validloc.push_back(temp);
    }
  }

  // if nowhere to put it, wait until next update
  if(validloc.empty())
    return false;

  // otherwise, create the new guy
  Mobile *newguy;

  if (which == Order::BA) {
    newguy = new Army(GetEmpire());
  } else if (which == Order::BC) {
    newguy = new Cruiser(GetEmpire());
  } else if (which == Order::BD) {
    newguy = new Destroyer(GetEmpire());
  } else if (which == Order::BE) {
    newguy = new Emperor(GetEmpire());
  } else {
    // BAD!!!
    assert(0);
  }

  // place the guy
  Static *where = validloc[random() % validloc.size()];
  where->PlaceMobile(newguy);

  return true;
}

bool City::GetHitBy(Active *e) {
  if (_size == 1) {
    GetEmpire()->RemoveActive(this);
    e->GetEmpire()->AddActive(this);
  } else {
    _size--;
  }
  return true; // cities never die, just change ownership
}

// return current location Coordinate
Coord City::GetLoc() {
  Coord c;
  bool goodloc = Static::GetLoc(c);
  assert (goodloc);
  return c;
}
