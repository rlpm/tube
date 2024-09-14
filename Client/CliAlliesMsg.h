// Stonecutters CS351 S03 -*- C++ -*-
// $Id: CliAlliesMsg.h,v 1.1 2003/05/05 22:53:26 rlpm Exp $

#ifndef CLIALLIESMSG_H
#define CLIALLIESMSG_H

// includes
#include <vector>
#include "AlliesMsg.h"

// forward declare
class Model;
class istream;

class CliAlliesMsg : public AlliesMsg {
public:
  CliAlliesMsg(vector<int> i) : AlliesMsg(i) {};
  CliAlliesMsg(istream &i) : AlliesMsg(i) {};
  virtual void Execute(Model*);

  static Message* GenMsg(istream &i) {
    return new CliAlliesMsg(i);
  }

private:
};

#endif // CLIALLIESMSG_H
