// Stonecutters CS351 S03 -*- C++ -*-

#include "Countdown.h"

Countdown::Countdown(size_t add_secs) {
  gettimeofday(&_tv,0);
  _tv.tv_sec += add_secs;
}

Countdown::operator bool() const {
  timeval tv;
  gettimeofday(&tv,0);

  if (tv.tv_sec > _tv.tv_sec) return true;
  if (tv.tv_sec == _tv.tv_sec && tv.tv_usec >= _tv.tv_usec) return true;
  return false;
}
