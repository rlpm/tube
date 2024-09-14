// Stonecutters CS351 S03 -*- C++ -*-

#ifndef MOBILE_H
#define MOBILE_H

//include files

#include <cassert>
#include "Active.h"
#include "Order.h"

//forward declarations
class Message;
class Static;

class Mobile:public Active{
  friend class Static;
public:
  Mobile(Empire*,Order);
  virtual ~Mobile();

  // common for all derived classes
  bool Attack(Active *, bool walk, bool prio=false);

  // virtual methods based here in Mobile
  virtual void Move(Static*);
  void SetHolder(Static *S) { _holder = S;};
  virtual Static* GetHolder() { return _holder;};
  void MoveTo(bool walk);

  // virtual methods from Active
  virtual Coord GetLoc();

private:
  Static* _holder;
};

#endif

