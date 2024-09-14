// Stonecutters CS351 S03 -*- C++ -*-

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
