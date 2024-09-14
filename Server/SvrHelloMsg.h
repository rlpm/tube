// Stonecutters CS351 S03 -*- C++ -*-
// $Id: SvrHelloMsg.h,v 1.2 2003/05/02 10:08:06 rlpm Exp $

#ifndef SVRHELLOMSG_H
#define SVRHELLOMSG_H

// includes
#include "HelloMsg.h"

// forward declare
class Model;
class Commander;
class istream;

class SvrHelloMsg : public HelloMsg {
public:
  SvrHelloMsg(int v, Type t, string id, string vl) : HelloMsg(v,t,id,vl) {};
  SvrHelloMsg(istream &i) : HelloMsg(i) {};
  virtual void Execute(Model*);

  static Message* GenMsg(istream &i) {
    return new SvrHelloMsg(i);
  }

private:
  static const char *_svrid;
};

#endif // SVRHELLOMSG_H
