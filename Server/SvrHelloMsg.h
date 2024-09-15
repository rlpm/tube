// Stonecutters CS351 S03 -*- C++ -*-

#ifndef SVRHELLOMSG_H
#define SVRHELLOMSG_H

// includes
#include "HelloMsg.h"

// forward declare
class Model;
class Commander;

class SvrHelloMsg : public HelloMsg {
public:
  SvrHelloMsg(int v, Type t, std::string id, std::string vl) : HelloMsg(v,t,id,vl) {};
  SvrHelloMsg(std::istream &i) : HelloMsg(i) {};
  virtual void Execute(Model*);

  static Message* GenMsg(std::istream &i) {
    return new SvrHelloMsg(i);
  }

private:
  static const char *_svrid;
};

#endif // SVRHELLOMSG_H
