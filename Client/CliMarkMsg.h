// Stonecutters CS351 S03 -*- C++ -*-

#ifndef CLIMARKMSG_H
#define CLIMARKMSG_H

// includes
#include "MarkMsg.h"

// forward declare
class Model;
class Commander;
class istream;

class CliMarkMsg : public MarkMsg {
public:
  CliMarkMsg(Type t, int c, std::string tx) : MarkMsg(t,c,tx) {};
  CliMarkMsg(std::istream &i) : MarkMsg(i) {};
  virtual void Execute(Model*);

  static Message* GenMsg(std::istream &i) {
    return new CliMarkMsg(i);
  }

private:
};

#endif // CLIMARKMSG_H
