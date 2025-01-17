// Stonecutters CS351 S03 -*- C++ -*-

#ifndef SVRFAILMSG_H
#define SVRFAILMSG_H

// includes
#include "FailMsg.h"

// forward declare
class Model;
class istream;

class SvrFailMsg : public FailMsg {
public:
  SvrFailMsg(std::string t) : FailMsg(t) {};
  SvrFailMsg(std::istream &i) : FailMsg(i) {};
  virtual void Execute(Model*);

  static Message* GenMsg(std::istream &i) {
    return new SvrFailMsg(i);
  }
};

#endif // SVRFAILMSG_H
