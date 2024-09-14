// Stonecutters CS351 S03 -*- C++ -*-

#ifndef GRID_H
#define GRID_H

// includes
#include <vector>
#include "Coord.h"
#include "Neighborhood.h"


// forward declarations
class GridAble;

class Grid
{
  friend class World; //may need to dump the grid

public:

  //enum for directions...may need some re-ordering later
  enum Direction {
    NORTH=0,
    SOUTH,
    EAST,
    WEST,
    NORTHWEST,
    NORTHEAST,
    SOUTHWEST,
    SOUTHEAST
  };
 
  Grid(Coord);  //ctor
  ~Grid();   //dtor

  Coord GetSize() { return _size; };
  bool Put(GridAble*, Coord);
  bool Move(GridAble*, const Direction &);
  bool Clear(GridAble *);
  GridAble* Get(Coord) const;
  Coord CoordAtDir(const Coord, const Direction) const;
  void Normalize(Coord&) const;

  // return the GridAble whose distance to another point is least
  // randomize if more than one is least
  GridAble* MinDist(vector<GridAble*>, Coord);

  // return the distance between 2 points on the torus
  size_t Distance(Coord, Coord);

  Neighborhood GetNeighborhood(Coord);  //returns a vector of the neighborhood

private:

  // flip over near edge if necessary
  void DoFlip(int &,int,int);

  //a vector of coords to be filled with neighborhood coordinates
  vector< vector<GridAble*> > _grid;

  // the size of the grid
  Coord _size;

};

#endif
