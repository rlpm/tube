// Stonecutters CS351 S03 -*- C++ -*-

#ifndef CRUISER_H
#define CRUISER_H

#include "Boat.h"

class Cruiser:public Boat{
public:
  Cruiser(Empire*);
  ~Cruiser();

  // virtual methods from GridAble
  virtual char GridTestChar() const { return 'R'; };

private:
  static const int __maxcap = 5; //Cruisers hold 5 armies
};

#endif
