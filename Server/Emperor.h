// Stonecutters CS351 S03 -*- C++ -*-

#ifndef EMPEROR_H
#define EMPEROR_H

#include "Boat.h"

class Emperor:public Boat{
public:
  Emperor(Empire*);
  ~Emperor();

  // virtual methods from GridAble returns the type of boat
  virtual char GridTestChar() const { return 'E'; };

private:
  static const int __maxcap = 10; // Emperors hold 10 armies
};

#endif
