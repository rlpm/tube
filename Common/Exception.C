// Stonecutters CS351 S03 -*- C++ -*-

#include <iostream>
#include <sstream>
#include <string>
#include "Exception.h"

std::string Exception::ToString() {
  std::ostringstream o;
  o << _file << ":" << _line << " " << _what;
  return o.str();
}

std::ostream& operator<<(std::ostream &o, Exception &e) {
  o << e.ToString();
  return o;
}
