// Stonecutters CS351 S03 -*- C++ -*-
// $Id: Destroyer.h,v 1.12 2003/05/13 22:43:30 rory Exp $

#ifndef DESTROYER_H
#define DESTROYER_H
#include "Boat.h"

class Destroyer:public Boat{
public:
  Destroyer(Empire*);
  ~Destroyer();

  // virtual methods from Active returns D for boat
  virtual char GridTestChar() const { return 'D'; };

private:
  static const int __maxcap = 2; //Destroyers hold 2 armies
};

#endif
