// Stonecutters CS351 S03 -*- C++ -*-

#ifndef STATIC_H
#define STATIC_H

//class includes
#include "GridAble.h"
#include "Order.h"
#include "ContactsMsg.h"

//forward declarations
class Message;
class Empire;
class Mobile;
class City;
class Land;
class Water;
class Active;
//Static base class
class Static: public GridAble
{
  friend class World;
public:
  virtual ~Static() {};
  virtual bool IsFloat() const;  //is the static floatable (water)
  virtual bool IsWalk(Active*) const;   //is the static walkable (land)
  virtual bool IsPrioAttack(Active*) const;
  virtual bool IsAttackable(Active*) const;
  virtual void PlaceMobile(Mobile *) = 0;
  virtual void RemoveMobile(Mobile*) = 0;
  virtual Active* GetVisible() = 0;
  // return the neighbor who is walkable or floatable and least
  // distant from another coord
  Static* MinMove(bool, Coord, Active*);
  bool GetStandingOrder(Empire*, Order&) const;

  // helper method for sending Contacts Message
  ContactsMsg::Terrain GetTerrain(Empire*,bool&);

  // For testing/debugging
  virtual char GridTestChar() const { return '?'; };

protected:
 //protected ctor, wont be instantiated directly
  Static(ContactsMsg::Terrain::Type t) : _type(t) {};
private:
  Static(const Static&);  //no value semantics
  void operator=(const Static&); //no value semantics
  std::vector< std::vector<Order> > _orders;
  std::vector<bool> _seen; // whether each empire has seen us
  ContactsMsg::Terrain::Type _type;
};

#endif
