// Stonecutters CS351 S03 -*- C++ -*-
// $Id: Land.h,v 1.14 2003/05/13 22:43:30 rory Exp $

#ifndef LAND_H
#define LAND_H

//include classes
#include "Static.h"
#include "Order.h"
#include "Army.h"
#include "ContactsMsg.h"

//forward declarations
class Army;
class Message;
class Active;

class Land: public Static{
 public:
  Land():Static(ContactsMsg::Terrain::LD),_army(NULL) {};
  ~Land(){};

  // virtual methods from Static
  virtual bool IsWalk(Active*) const;
  virtual bool IsAttackable(Active*) const;

  // used to move things around
  virtual void PlaceMobile(Mobile*);
  virtual void RemoveMobile(Mobile*);

  // used to generate messages
  virtual Active * GetVisible() { return _army; };

  // test/debug from GridAble
  virtual char GridTestChar() const { return '+'; };

private:
  Army* _army; // point at an army if one's on top

};

#endif
