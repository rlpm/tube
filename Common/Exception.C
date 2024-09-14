// Stonecutters CS351 S03 -*- C++ -*-
// $Id: Exception.C,v 1.1 2003/05/03 00:21:42 rlpm Exp $

#include <iostream>
#include <sstream>
#include <string>
#include "Exception.h"

string Exception::ToString() {
  ostringstream o;
  o << _file << ":" << _line << " " << _what;
  return o.str();
}

ostream& operator<<(ostream &o, Exception &e) {
  o << e.ToString();
  return o;
}
