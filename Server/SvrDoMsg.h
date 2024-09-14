// Stonecutters CS351 S03 -*- C++ -*-

#ifndef SVRDOMSG_H
#define SVRDOMSG_H

// includes
#include "DoMsg.h"

// forward declare
class Model;
class istream;

class SvrDoMsg : public DoMsg {
public:
  SvrDoMsg(int i, Order o) : DoMsg(i,o) {};
  SvrDoMsg(istream &i) : DoMsg(i) {};
  virtual void Execute(Model*);

  static Message* GenMsg(istream &i) {
    return new SvrDoMsg(i);
  }

private:
};

#endif // SVRDOMSG_H
