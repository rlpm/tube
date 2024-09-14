// Stonecutters CS351 S03 -*- C++ -*-
// $Id: Countdown.h,v 1.1 2003/05/04 01:44:56 rlpm Exp $

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
