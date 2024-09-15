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
  CliFailMsg(std::string t) : FailMsg(t) {};
  CliFailMsg(std::istream &i) : FailMsg(i) {};
  virtual void Execute(Model*);

  static Message* GenMsg(std::istream &i) {
    return new CliFailMsg(i);
  }
};

#endif // CLIFAILMSG_H
