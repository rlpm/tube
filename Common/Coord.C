// Stonecutters CS351 S03 -*- C++ -*-

#include "Coord.h"
#include "Grid.h"
#include "FrameParser.h"
#include <cassert>

Coord::Coord(int X, int Y) : _x(X),_y(Y) {}

Coord::~Coord() {}

std::string Coord::ToString(){
  std::ostringstream os;
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

std::ostream& operator<<(std::ostream& os, const Coord& C){
  os << C.GetX() << ' ' << C.GetY();
  return os;
}

std::istream& operator>>(std::istream& is, Coord& C){
  is >> C._x >> C._y;
  FrameParser::SkipSpace(is);
  return is;
}
