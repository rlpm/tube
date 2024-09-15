// Stonecutters CS351 S03 -*- C++ -*-

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>
#include <sys/types.h>

class Exception {
public:
  Exception(std::string w, std::string f, size_t l) : _what(w), _file(f), _line(l) {};
  ~Exception() {};
  std::string ToString();

private:
  std::string _what;  // The excepted text
  std::string _file;  // the filename
  size_t _line;  // the line number
};

// MACROS ARE EVIL!!! :)
#define EXCEPTION(__x__) Exception(__x__,__FILE__,__LINE__);

std::ostream& operator<<(std::ostream&,Exception&);

#endif
