// Stonecutters CS351 S03 -*- C++ -*-

#ifndef SVRCQMSG_H
#define SVRCQMSG_H

// includes
#include "CqMsg.h"

// forward declare
class Model;
class Commander;
class istream;

class SvrCqMsg : public CqMsg {
public:
  SvrCqMsg(int t, bool p, string x) : CqMsg(t,p,x) {};
  SvrCqMsg(istream &i) : CqMsg(i) {};
  virtual void Execute(Model*);

  static Message* GenMsg(istream &i) {
    return new SvrCqMsg(i);
  }
};

#endif // SVRCQMSG_H
