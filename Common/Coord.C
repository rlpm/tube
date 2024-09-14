// Stonecutters CS351 S03 -*- C++ -*-
// $Id: Coord.C,v 1.6 2003/05/08 23:52:41 rlpm Exp $

#include "Coord.h"
#include "Grid.h"
#include "FrameParser.h"
#include  <assert.h>

Coord::Coord(int X, int Y) : _x(X),_y(Y) {}

Coord::~Coord() {}

string Coord::ToString(){
  ostringstream os;
  os << _x <<' '<< _y;
  return os.str();
}

bool Coord::operator==(const Coord& loc) const
{
  return ((_x == loc._x) && (_y==loc._y));
}


bool Coord::operator!=(const Coord& loc) const
{
  return !(*this == loc);
}

ostream& operator<<(ostream& os, const Coord& C){
  os << C.GetX() << ' ' << C.GetY();
  return os;
}

istream& operator>>(istream& is, Coord& C){
  is >> C._x >> C._y;
  FrameParser::SkipSpace(is);
  return is;
}
