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
  SvrMarkMsg(Type t, int c, std::string tx) : MarkMsg(t,c,tx) {};
  SvrMarkMsg(std::istream &i) : MarkMsg(i) {};
  virtual void Execute(Model*);

  static Message* GenMsg(std::istream &i) {
    return new SvrMarkMsg(i);
  }

private:
};

#endif // SVRMARKMSG_H
