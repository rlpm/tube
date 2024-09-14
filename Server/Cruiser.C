// Stonecutters CS351 S03 -*- C++ -*-
// $Id: Cruiser.C,v 1.9 2003/05/08 21:31:41 rlpm Exp $

#include "Cruiser.h"

Cruiser::Cruiser(Empire* E):Boat(E,__maxcap,Order::CR){}

Cruiser::~Cruiser(){}
