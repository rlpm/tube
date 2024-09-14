// Stonecutters CS351 S03 -*- C++ -*-

#include "GridAble.h"
#include "Grid.h"
#include "Neighborhood.h"

GridAble::GridAble() : _g(NULL), _loc(0,0) {}

GridAble::~GridAble() {
  if (_g) _g->Clear(this);
}

// Get the Grid
Grid* GridAble::GetGrid() const {
  return _g;
}

// Set the Grid
bool GridAble::SetGrid(Grid *g) {
  if (_g) return false;
  _g = g;
  return true;
}

// Get the location
bool GridAble::GetLoc(Coord &c) const {
  if (!_g) return false;
  c = _loc;
  return true;
}

// Set the Location
bool GridAble::SetLoc(Coord loc) {
  if (!_g) return false;
  _loc = loc;
  return true;
}

// Get the neighborhood
Neighborhood GridAble::GetNeighborhood() const {
  Coord c;
  bool goodc = GetLoc(c);
  assert(goodc);

  Neighborhood n = GetGrid()->GetNeighborhood(c);
  return n;
}

