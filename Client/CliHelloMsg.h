// Stonecutters CS351 S03 -*- C++ -*-
// $Id: CliHelloMsg.h,v 1.1 2003/05/05 22:53:27 rlpm Exp $

#ifndef CLIHELLOMSG_H
#define CLIHELLOMSG_H

// includes
#include "HelloMsg.h"

// forward declare
class Model;
class istream;

class CliHelloMsg : public HelloMsg {
public:
  CliHelloMsg(int v, Type t, string id, string vl) : HelloMsg(v,t,id,vl) {};
  CliHelloMsg(istream &i) : HelloMsg(i) {};
  virtual void Execute(Model*);

  static Message* GenMsg(istream &i) {
    return new CliHelloMsg(i);
  }

private:
};

#endif // CLIHELLOMSG_H
