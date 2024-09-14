// Stonecutters CS351 S03 -*- C++ -*-

#ifndef WATER_H
#define WATER_H

//include files
#include <stddef.h>
#include "Static.h"
#include "Order.h"
#include "Boat.h"

//forward declarations
class Boat;
class Message;

class Water: public Static {
 public:
  Water() : Static(ContactsMsg::Terrain::WA), _boat(NULL) {};
  ~Water() {};

  // methods from static
  virtual bool IsFloat() const;
  virtual bool IsWalk(Active *) const;
  virtual bool IsAttackable(Active*) const;

  // methods to move things around
  virtual void PlaceMobile(Mobile *);
  virtual void RemoveMobile(Mobile *);

  // used to generate messages
  virtual Active* GetVisible() { return _boat;};

  // test/debug from GridAble
  virtual char GridTestChar() const { return '.'; };

private:
  Boat* _boat; // point at a boat if we have a boat
};
#endif
