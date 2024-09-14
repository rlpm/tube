// Stonecutters CS351 S03 -*- C++ -*-

#ifndef SVRALLIESMSG_H
#define SVRALLIESMSG_H

// includes
#include <vector>
#include "AlliesMsg.h"

// forward declare
class Model;
class istream;

class SvrAlliesMsg : public AlliesMsg {
public:
  SvrAlliesMsg(vector<int> i) : AlliesMsg(i) {};
  SvrAlliesMsg(istream &i) : AlliesMsg(i) {};
  virtual void Execute(Model*);

  static Message* GenMsg(istream &i) {
    return new SvrAlliesMsg(i);
  }

private:
};

#endif // SVRALLIESMSG_H
