// Stonecutters CS351 S03 -*- C++ -*-

#ifndef SVRDOMSG_H
#define SVRDOMSG_H

// includes
#include "DoMsg.h"

// forward declare
class Model;

class SvrDoMsg : public DoMsg {
public:
  SvrDoMsg(int i, Order o) : DoMsg(i,o) {};
  SvrDoMsg(std::istream &i) : DoMsg(i) {};
  virtual void Execute(Model*);

  static Message* GenMsg(std::istream &i) {
    return new SvrDoMsg(i);
  }

private:
};

#endif // SVRDOMSG_H
