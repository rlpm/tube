// Stonecutters CS351 S03 -*- C++ -*-

#ifndef CLICQMSG_H
#define CLICQMSG_H

// includes
#include "CqMsg.h"

// forward declare
class Model;
class Commander;
class istream;

class CliCqMsg : public CqMsg {
public:
  CliCqMsg(int t, bool p, string x) : CqMsg(t,p,x) {};
  CliCqMsg(istream &i) : CqMsg(i) {};
  virtual void Execute(Model*);

  static Message* GenMsg(istream &i) {
    return new CliCqMsg(i);
  }
};

#endif // CLICQMSG_H
