// Stonecutters CS351 S03 -*- C++ -*-

#include <cassert>
#include "Order.h"
#include "FrameParser.h"
#include "Exception.h"

Order::Order(UnitType u,CmdType c, Coord l, int i) 
:_unit(u), _cmd(c), _loc(l), _count(i) {}

void Order::_reset_count() {
  switch(_cmd) {
#define XX(a,b) case (a): _count = b; break;
#include "CityRates"
#undef XX
  default: break;
  }
}

std::istream& operator>> (std::istream & in, Order &o) {
  std::string u;
  o._unit = Order::__UT_END__;
  o._cmd = Order::__CT_END__;
  try {
    u = FrameParser::GrabKW(in);
  }
  catch (Exception e) {
    std::cerr << e;
    throw;
  }

// Do a little Macro dance
#define XX(a) if (u == #a) o._unit = Order::a;
#include "UnitTypes"
#undef XX

  try {
    u = FrameParser::GrabKW(in);
  }
  catch (Exception e) {
    std::cerr << e;
    throw;
  }

// Do a little Macro dance
#define XX(a) if (u == #a) o._cmd = Order::a;
#include "CommandTypes"
#undef XX

  in >> o._loc >> o._count;
  assert(o._unit != Order::__UT_END__);
  assert(o._cmd != Order::__CT_END__);

  FrameParser::SkipSpace(in);

  return in;
}


std::string Order::ToString() const {
  std::ostringstream o;
  switch (_unit) {
#define XX(a) case a: o << #a; break;
#include "UnitTypes"
#undef XX
  default: assert(0); break;
  }
  o << ' ';

  switch (_cmd) {
#define XX(a) case a: o << #a; break;
#include "CommandTypes"
#undef XX
  default: assert(0); break;
  }

  o << ' ' << _loc << ' ' << _count;
  return o.str();
}

bool Order::NeedsCoord(CmdType w) {
  if (w == MA || w == DF || w == SL) return true;
  else return false;
}

bool Order::NeedsWait(UnitType w) {
  if (w == DE || w == Order::CR || w == EM) return true;
  else return false;
}
							   
bool Order::ValidCommand(UnitType u, CmdType c) {
  if (
      ((c == XP || c == WT) && u == CT) ||
      (c == MA && u != AR) ||
      (c == DF && u == CT) ||
      (c == SL && (u == CT || u == AR)) ||
      ((c == BA || c == BD || c == BC || c == BE 
	|| c == GR) && u != CT)
     )
    return false;
  else return true;
}
