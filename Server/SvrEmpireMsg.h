// Stonecutters CS351 S03 -*- C++ -*-

#ifndef SVREMPIREMSG_H
#define SVREMPIREMSG_H

// includes
#include "EmpireMsg.h"

// forward declare
class Model;

class SvrEmpireMsg : public EmpireMsg {
public:
  SvrEmpireMsg(int e) : EmpireMsg(e) {};
  SvrEmpireMsg(std::istream &i) : EmpireMsg(i) {};
  virtual void Execute(Model*);

  static Message* GenMsg(std::istream &i) {
    return new SvrEmpireMsg(i);
  }

private:
};

#endif // SVREMPIREMSG_H
