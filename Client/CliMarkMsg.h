// Stonecutters CS351 S03 -*- C++ -*-
// $Id: CliMarkMsg.h,v 1.1 2003/05/05 22:53:27 rlpm Exp $

#ifndef CLIMARKMSG_H
#define CLIMARKMSG_H

// includes
#include "MarkMsg.h"

// forward declare
class Model;
class Commander;
class istream;

class CliMarkMsg : public MarkMsg {
public:
  CliMarkMsg(Type t, int c, string tx) : MarkMsg(t,c,tx) {};
  CliMarkMsg(istream &i) : MarkMsg(i) {};
  virtual void Execute(Model*);

  static Message* GenMsg(istream &i) {
    return new CliMarkMsg(i);
  }

private:
};

#endif // CLIMARKMSG_H
