// Stonecutters CS351 S03 -*- C++ -*-
// $Id: CliEmpireMsg.h,v 1.1 2003/05/09 04:53:17 rlpm Exp $

#ifndef CLIEMPIREMSG_H
#define CLIEMPIREMSG_H

// includes
#include "EmpireMsg.h"

// forward declare
class Model;
class istream;

class CliEmpireMsg : public EmpireMsg {
public:
  CliEmpireMsg(int i) : EmpireMsg(i) {};
  CliEmpireMsg(istream &i) : EmpireMsg(i) {};
  virtual void Execute(Model*);

  static Message* GenMsg(istream &i) {
    return new CliEmpireMsg(i);
  }

private:
};

#endif // CLIEMPIREMSG_H
