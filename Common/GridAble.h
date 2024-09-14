// Stonecutters CS351 S03 -*- C++ -*-

#ifndef GRIDABLE_H
#define GRIDABLE_H

// includes
#include "Coord.h"
#include "Neighborhood.h"

// forward declarations
class Grid;

// The GridAble base class
class GridAble {

  friend class Grid; // so it can muck around inside this base class
                     // (but not derived classes)

public:

  virtual ~GridAble(); //  dtor

  // Get the location
  bool GetLoc(Coord &) const;

  // Get the Neighborhood
  Neighborhood GetNeighborhood() const;

protected:

  // Make this class somewhat abstract by defining constructor as protected
  // so it can't be instantiated directly.
  GridAble(); // default ctor

  // Get the grid
  Grid* GetGrid() const;

private:

  // don't allow shallow copies
  GridAble(const GridAble &);
  void operator=(const GridAble &);

  // Set the Grid
  bool SetGrid(Grid *);

  // Set the Location
  bool SetLoc(Coord loc);

  // The grid we're in
  Grid *_g;

  // The location
  Coord _loc;

};

#endif // GRIDABLE_H
