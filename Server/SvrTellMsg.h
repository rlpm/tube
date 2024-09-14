// Stonecutters CS351 S03 -*- C++ -*-
// $Id: SvrTellMsg.h,v 1.1 2003/05/08 23:52:41 rlpm Exp $

#ifndef SVRTELLMSG_H
#define SVRTELLMSG_H

// includes
#include "TellMsg.h"

// forward declare
class Model;
class istream;

class SvrTellMsg : public TellMsg {
public:
  SvrTellMsg(Coord c, vector<Order> os) : TellMsg(c,os) {};
  SvrTellMsg(istream &i) : TellMsg(i) {};
  virtual void Execute(Model*);

  static Message* GenMsg(istream &i) {
    return new SvrTellMsg(i);
  }

private:
};

#endif // SVRTELLMSG_H
