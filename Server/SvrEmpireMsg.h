// Stonecutters CS351 S03 -*- C++ -*-

#ifndef SVREMPIREMSG_H
#define SVREMPIREMSG_H

// includes
#include "EmpireMsg.h"

// forward declare
class Model;
class istream;

class SvrEmpireMsg : public EmpireMsg {
public:
  SvrEmpireMsg(int e) : EmpireMsg(e) {};
  SvrEmpireMsg(istream &i) : EmpireMsg(i) {};
  virtual void Execute(Model*);

  static Message* GenMsg(istream &i) {
    return new SvrEmpireMsg(i);
  }

private:
};

#endif // SVREMPIREMSG_H
