// Stonecutters CS351 S03 -*- C++ -*-
// $Id: Army.h,v 1.22 2003/05/13 22:43:30 rory Exp $

#ifndef ARMY_H
#define ARMY_H

// Include files
#include "Mobile.h"
#include "Grid.h"
#include "Order.h"

// forward declarations
class Message;
class Static;
class Boat;

class Army:public Mobile{
public:
  Army(Empire*);
  virtual ~Army();
  void Update();
  // for the following methods, return false if we die
  bool Explore();
  bool March();
  bool Defend();
  bool GetHitBy(Active*);
  virtual int Hits() const { return 1;};
  void SetBoat(Boat*);

  // virtual methods from Active
  virtual bool KeepAlive() const { return true; };
  virtual char GridTestChar() const { return 'A'; };

private:
  bool FindAttackable(Neighborhood, bool&); // set 2nd param to false if we die
  Boat* _carrier;

};

#endif
