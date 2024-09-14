// Stonecutters CS351 S03 -*- C++ -*-

#ifndef SVRMARKMSG_H
#define SVRMARKMSG_H

// includes
#include "MarkMsg.h"

// forward declare
class Model;
class Commander;
class istream;

class SvrMarkMsg : public MarkMsg {
public:
  SvrMarkMsg(Type t, int c, string tx) : MarkMsg(t,c,tx) {};
  SvrMarkMsg(istream &i) : MarkMsg(i) {};
  virtual void Execute(Model*);

  static Message* GenMsg(istream &i) {
    return new SvrMarkMsg(i);
  }

private:
};

#endif // SVRMARKMSG_H
