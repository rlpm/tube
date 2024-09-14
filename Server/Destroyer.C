// Stonecutters CS351 S03 -*- C++ -*-
// $Id: Destroyer.C,v 1.10 2003/05/08 21:31:41 rlpm Exp $

#include "Destroyer.h"

Destroyer::Destroyer(Empire *E):Boat(E,__maxcap,Order::DE){}

Destroyer::~Destroyer(){}
