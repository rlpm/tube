// Stonecutters CS351 S03 -*- C++ -*-

#include <cassert>
#include <cmath>
#include "Grid.h"
#include "GridAble.h"
#include "Coord.h"
#include "Neighborhood.h"

Grid::Grid(Coord size) : _size(size)
{
  _grid.resize(_size.GetX()); 
  for (int i = 0; i < _size.GetX(); i++) {
    _grid[i].resize(_size.GetY());
    for (int j=0;j<_size.GetY();j++) {
      _grid[i][j] = NULL;
    }
  }
}

Grid::~Grid() {
  for (int i = 0; i < _size.GetX(); i++) {
    for (int j=0;j<_size.GetY();j++) {
      if(_grid[i][j])
        delete _grid[i][j];
    }
  }
}


bool Grid::Put(GridAble* gable, Coord loc)
{
  Normalize(loc);
  if (_grid[loc.GetX()][loc.GetY()]) return false;
  if (gable->GetGrid() != NULL) return false;
  gable->SetGrid(this);
  _grid[loc.GetX()][loc.GetY()] = gable;
  gable->SetLoc(loc);
  return true;
}

GridAble* Grid::Get(Coord loc) const
{
  Normalize(loc);
  return(_grid[loc.GetX()][loc.GetY()]);
}

// gets a vector of neighborhood cells
Neighborhood Grid::GetNeighborhood(Coord o)
{
  Normalize(o);
  Neighborhood n;
  
  for (int i=NORTH;i<=SOUTHEAST;i++) {
    n.push_back(Get(CoordAtDir(o,static_cast<Direction>(i))));
  }

  return n;
}

Coord Grid::CoordAtDir(const Coord loc, const Direction dir) const
{
  Coord ret(loc);
  if (dir == NORTH || dir == NORTHWEST || dir == NORTHEAST)
    ret.SetY(ret.GetY()-1);
  if (dir == SOUTH || dir == SOUTHWEST || dir == SOUTHEAST)
    ret.SetY(ret.GetY()+1);
  if (dir == WEST || dir == SOUTHWEST || dir == NORTHWEST)
    ret.SetX(ret.GetX()-1);
  if (dir == EAST || dir == SOUTHEAST || dir == NORTHEAST)
    ret.SetX(ret.GetX()+1);

  Normalize(ret);
  return ret;
}

bool Grid::Clear(GridAble *gable)
{
  if (gable->_g != this) return false;
  _grid[gable->_loc.GetX()][gable->_loc.GetY()] = NULL;
  gable->_g = NULL;
  return true;
}

void Grid::Normalize(Coord &C) const
{
  int x = C.GetX();
  while(x < 0)
    x += _size.GetX();
  while(x >= _size.GetX())
    x -= _size.GetX();

  int y = C.GetY();
  while(y < 0)
    y += _size.GetY();
  while(y >= _size.GetY())
    y -= _size.GetY();

  C.SetX(x);
  C.SetY(y);

  return;
}

GridAble* Grid::MinDist(std::vector<GridAble*> from, Coord to){
  Normalize(to);
  if (!from.size()) return NULL;                // nowhere passed in
  std::vector<GridAble*> least;                      // to store possible directions
  size_t leastdist =_size.GetX() + _size.GetY();// greater than max dist

  for(unsigned int i = 0; i < from.size(); i++){         // to check all directions
    Coord C;
    bool goodC = from[i]->GetLoc(C);
    assert(goodC);

    size_t tempdist = Distance(C,to);

    if(tempdist < leastdist){ // need to reset leastdist, once we find one
      least.clear();
    }
    if(tempdist <= leastdist){
      least.push_back(from[i]);
      leastdist = tempdist;
    }
  }  
  // make sure we found at least one...
  assert(least.size());

  if (least.size() == 1) return least[0];
  else return least[random() % least.size()];
}

// Calculate distance between two points
size_t Grid::Distance(Coord from, Coord to) {
  Normalize(from);
  Normalize(to);

  int tmp;
  // flip x across near edge if necessary
  tmp = from.GetX();
  DoFlip(tmp, to.GetX(), _size.GetX());
  from.SetX(tmp);

  // flip y across near edge if necessary
  tmp = from.GetY();
  DoFlip(tmp, to.GetY(), _size.GetY());
  from.SetY(tmp);

  // we need to move diagonally then directly from origin to destination
  int tempX = from.GetX(), tempY = from.GetY(), tempdist = 0;
  while(!((tempX == to.GetX()) || (tempY == to.GetY()))) {
    if(tempX < to.GetX()) {
      tempX++; // we are too far west
    } else if(tempX > to.GetX()) {
      tempX--; // we are too far east
    }
    if(tempY < to.GetY()) {
	tempY++; // we are too far north
    } else if(tempY > to.GetY()) {
      tempY--; // we are too far south
    }
    tempdist++;
  }

  from = Coord(tempX,tempY);

  // determine straight distance
  int strttemp = abs(tempX - to.GetX()) + abs(tempY - to.GetY());

  tempdist += strttemp;

  return tempdist;
}

// If we have to travel more than half the distance, flip over near edge
void Grid::DoFlip(int &from, int to, int max) {
  int diff = to - from;

  if(abs(diff) > (max / 2)) {
    // flip the sign of max to get other edge
    if (diff < 0)
      max *= -1;
    from += max;
  }
}
