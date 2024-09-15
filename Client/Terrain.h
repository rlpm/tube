// Stonecutters CS351 S03 -*- C++ -*-

#ifndef TERRAIN_H
#define TERRAIN_H

#include <list>
#include "ContactsMsg.h"
#include "GridAble.h"

class Control;
class Grid;
class Curse;

class Terrain : public GridAble {
  friend class Control;
  friend class Cview;
public:
  Terrain(Control *c,ContactsMsg::Terrain);
  Terrain(Control *c,ContactsMsg::Active);
  Terrain(Control *c,ContactsMsg::Contact);
  ~Terrain(){};
  void Output(Curse*, Coord);

  static ContactsMsg::Terrain::Type Underneath(Order::UnitType);

private:
  Control *_control;
  ContactsMsg::Terrain _t;
  std::list<ContactsMsg::Contact> _c;
  std::list<ContactsMsg::Active> _a;
};

#endif
