// Stonecutters CS351 S03 -*- C++ -*-

#ifndef COUNTDOWN_H
#define COUNTDOWN_H

#include <sys/time.h>
#include <sys/types.h>

// a class to countdown a number of seconds
// operator bool() returns true if the time
// has elapsed, otherwise false

class Countdown {
public:
  Countdown(size_t);
  ~Countdown(){};
  operator bool() const;

private:
  timeval _tv;
};

#endif // COUNTDOWN_H
