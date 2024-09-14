// Stonecutters CS351 S03 -*- C++ -*-
// $Id: CliTellMsg.h,v 1.1 2003/05/09 04:53:17 rlpm Exp $

#ifndef CLITELLMSG_H
#define CLITELLMSG_H

// includes
#include <vector>
#include "TellMsg.h"
#include "Coord.h"
#include "Order.h"

// forward declare
class Model;
class istream;

class CliTellMsg : public TellMsg {
public:
  CliTellMsg(Coord c, vector<Order> o) : TellMsg(c,o) {};
  CliTellMsg(istream &i) : TellMsg(i) {};
  virtual void Execute(Model*);

  static Message* GenMsg(istream &i) {
    return new CliTellMsg(i);
  }

private:
};

#endif // CLITELLMSG_H
