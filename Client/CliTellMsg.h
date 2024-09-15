// Stonecutters CS351 S03 -*- C++ -*-

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
  CliTellMsg(Coord c, std::vector<Order> o) : TellMsg(c,o) {};
  CliTellMsg(std::istream &i) : TellMsg(i) {};
  virtual void Execute(Model*);

  static Message* GenMsg(std::istream &i) {
    return new CliTellMsg(i);
  }

private:
};

#endif // CLITELLMSG_H
