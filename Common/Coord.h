// Stonecutters CS351 S03 -*- C++ -*-

#ifndef COORD_H
#define COORD_H

//include files
#include <iostream>
#include <string>
#include <sstream>

class Coord
{
public:
  Coord(int X = 0, int Y = 0);
  Coord(istream &i) { i >> *this; };
  ~Coord();
  int GetX() const { return _x;};
  int GetY() const { return _y;};
  void SetX(int X){ _x = X; };
  void SetY(int Y){ _y = Y; };
  string ToString();
  bool operator==(const Coord&) const;
  bool operator!=(const Coord&) const;
  friend ostream& operator<<(ostream&, const Coord&);
  friend istream& operator>>(istream&, Coord&);
private:
  int _x , _y;
};

#endif
