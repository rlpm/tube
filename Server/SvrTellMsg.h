// Stonecutters CS351 S03 -*- C++ -*-

#ifndef SVRTELLMSG_H
#define SVRTELLMSG_H

// includes
#include "TellMsg.h"

// forward declare
class Model;

class SvrTellMsg : public TellMsg {
public:
  SvrTellMsg(Coord c, std::vector<Order> os) : TellMsg(c,os) {};
  SvrTellMsg(std::istream &i) : TellMsg(i) {};
  virtual void Execute(Model*);

  static Message* GenMsg(std::istream &i) {
    return new SvrTellMsg(i);
  }

private:
};

#endif // SVRTELLMSG_H
