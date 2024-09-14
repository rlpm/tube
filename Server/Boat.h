// Stonecutters CS351 S03 -*- C++ -*-

#ifndef BOAT_H
#define BOAT_H

// Include files
#include "Order.h"
#include "Mobile.h"
#include <list>
#include "Neighborhood.h"

// forward declarations
class Water;
class Army;
class Static;

class Boat:public Mobile{
public:
  Boat(Empire*,int,Order::UnitType);
  virtual  ~Boat(){};
 
  int MaxCap() const { return _maxcap; };
  virtual bool IsFull() const {return (_marines.size() == _cap);};
  void Explore();
  void Sail();
  void Defend();
  virtual void Update(); // from Active

  void PlaceArmy(Army*);
  void RemoveArmy(Army*);
  bool GetHitBy(Active*);
  virtual int Hits() const { return _cap; };
  virtual char GridTestChar() const { return 'B'; };
private:
  bool AllyCities(); // Check for allied cities in the nhood
  void UpdateMarines();

  size_t _cap; // Same as _maxcap to begin with
  size_t _maxcap; // Pulled up from boat subclasses ctors
  list<Army*> _marines; // These are the guys on our boats
};

#endif
