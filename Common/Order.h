// Stonecutters CS351 S03 -*- C++ -*-

#ifndef ORDER_H
#define ORDER_H

#include "Coord.h"
#include <string>
#include <sstream>

class istream;  //Forward Declare



class Order {
 public:
  enum UnitType {
#define XX(a) a,
#include "UnitTypes"
#undef XX
    __UT_END__
  };
  enum CmdType{
// Do a little Macro dance
#define XX(a) a,
#include "CommandTypes"
#undef XX
    __CT_END__
  };

  Order(UnitType,CmdType,Coord,int);
  Order(istream &i) { i >> *this; };
  ~Order(){};

  UnitType GetUnit() const {return _unit; };
  CmdType GetCmd() const {return _cmd; };
  Coord GetCoord() const {return _loc; };
  int GetCt() const {return _count; };
  void DecCt(int dec) { _count-=dec; };
  string ToString() const;
  friend ostream & operator<<(ostream &o, const Order &d) {
    o << d.ToString(); return o;
  };

  friend istream& operator>>(istream &, Order &);

  void _reset_count(); // set City work automatically

  // helpers for client error checking
  static bool NeedsCoord(CmdType);
  static bool NeedsWait(UnitType);
  static bool ValidCommand(UnitType,CmdType);

 private:
  UnitType _unit;
  CmdType _cmd;
  Coord _loc;
  int _count;
}; 



#endif
