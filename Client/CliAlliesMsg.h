// Stonecutters CS351 S03 -*- C++ -*-

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
  CliAlliesMsg(std::vector<int> i) : AlliesMsg(i) {};
  CliAlliesMsg(std::istream &i) : AlliesMsg(i) {};
  virtual void Execute(Model*);

  static Message* GenMsg(std::istream &i) {
    return new CliAlliesMsg(i);
  }

private:
};

#endif // CLIALLIESMSG_H
