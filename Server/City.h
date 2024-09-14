// Stonecutters CS351 S03 -*- C++ -*-

#ifndef CITY_H
#define CITY_H

//class includes
#include <cassert>
#include "Coord.h"
#include "Active.h"
#include "Static.h"
#include "Order.h"
#include <string>

//forward declarations
class Army;
class Boat;
class Empire;

class City: public Active, public Static {
 public:
  City(Empire*);
  ~City();

  // virtual methods from Active:
  void Update();           // Performs incremental update

  // attacker function
  virtual bool GetHitBy(Active*);

  // return general information about City
  virtual Coord GetLoc();
  virtual int Hits() const{ return _size; };
  virtual Static* GetHolder() { return this; };

  // force City to stick around after an empire dies
  virtual bool KeepAlive() const { return true; };
  virtual char GridTestChar() const { return 'C'; };

  // virtual methods from Static:
  virtual bool IsAttackable(Active* e) const { return Active::IsAttackable(e); };
  virtual bool IsPrioAttack(Active* e) const { return IsAttackable(e); };
  virtual void PlaceMobile(Mobile *) { assert(0); };
  virtual void RemoveMobile(Mobile *) { assert(0); };
  virtual Active* GetVisible() { return this; };
  virtual ContactsMsg::Terrain GetTerrain() { assert(0); };

 private:
  void Grow();                // Grow city
  bool Build(Order::CmdType); // Generic build unit
  Coord FindOpen();           // Finding nearby open space

  int _size;
};
#endif
