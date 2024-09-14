// Stonecutters CS351 S03 -*- C++ -*-

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>
#include <sys/types.h>

class Exception {
public:
  Exception(string w, string f, size_t l) : _what(w), _file(f), _line(l) {};
  ~Exception() {};
  string ToString();

private:
  string _what;  // The excepted text
  string _file;  // the filename
  size_t _line;  // the line number
};

// MACROS ARE EVIL!!! :)
#define EXCEPTION(__x__) Exception(__x__,__FILE__,__LINE__);

class ostream;

ostream& operator<<(ostream&,Exception&);

#endif
