// Stonecutters CS351 S03 -*- C++ -*-
// $Id: Mountain.h,v 1.7 2003/05/09 03:49:58 rlpm Exp $

#ifndef MOUNTAIN_H
#define MOUNTAIN_H

#include <cassert>
#include "Static.h"

class Mobile;

class Mountain: public Static{
public:
  Mountain() : Static(ContactsMsg::Terrain::MT) {};
  ~Mountain(){};

  // most everything is done within Static
  void PlaceMobile(Mobile*){assert(0);};  // can't place anything into a mountain
  void RemoveMobile(Mobile*){assert(0);}; // can't take anything out of a mountain
  Active* GetVisible() { return NULL; };  // can't see anything on a mountain
  
  // test/debug from GridAble
  virtual char GridTestChar() const { return '^'; };
};
#endif
