// Stonecutters CS351 S03 -*- C++ -*-

#ifndef CLIHELLOMSG_H
#define CLIHELLOMSG_H

// includes
#include "HelloMsg.h"

// forward declare
class Model;
class istream;

class CliHelloMsg : public HelloMsg {
public:
  CliHelloMsg(int v, Type t, std::string id, std::string vl) : HelloMsg(v,t,id,vl) {};
  CliHelloMsg(std::istream &i) : HelloMsg(i) {};
  virtual void Execute(Model*);

  static Message* GenMsg(std::istream &i) {
    return new CliHelloMsg(i);
  }

private:
};

#endif // CLIHELLOMSG_H
