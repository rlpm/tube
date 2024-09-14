// Stonecutters CS351 S03 -*- C++ -*-

#ifndef CLIFAILMSG_H
#define CLIFAILMSG_H

// includes
#include "FailMsg.h"

// forward declare
class Model;
class istream;

class CliFailMsg : public FailMsg {
public:
  CliFailMsg(string t) : FailMsg(t) {};
  CliFailMsg(istream &i) : FailMsg(i) {};
  virtual void Execute(Model*);

  static Message* GenMsg(istream &i) {
    return new CliFailMsg(i);
  }
};

#endif // CLIFAILMSG_H
