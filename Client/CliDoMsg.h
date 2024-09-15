// Stonecutters CS351 S03 -*- C++ -*-

#ifndef CLIDOMSG_H
#define CLIDOMSG_H

// includes
#include "DoMsg.h"
#include "Order.h"

// forward declare
class Model;
class istream;

class CliDoMsg : public DoMsg {
public:
  CliDoMsg(int i, Order o) : DoMsg(i,o) {};
  CliDoMsg(std::istream &i) : DoMsg(i) {};
  virtual void Execute(Model*);

  static Message* GenMsg(std::istream &i) {
    return new CliDoMsg(i);
  }

private:
};

#endif // CLIDOMSG_H
