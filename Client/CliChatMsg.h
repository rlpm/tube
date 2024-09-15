// Stonecutters CS351 S03 -*- C++ -*-

#ifndef CLICHATMSG_H
#define CLICHATMSG_H

// includes
#include "ChatMsg.h"
#include <string>
// forward declare
class Model;
class Commander;
class istream;

class CliChatMsg : public ChatMsg {
public:
  CliChatMsg(std::string t, std::string x) : ChatMsg(t,x) {};
  CliChatMsg(std::istream &i) : ChatMsg(i) {};
  ~CliChatMsg(){};
  virtual void Execute(Model*);

  static Message* GenMsg(std::istream &i) {
    return new CliChatMsg(i);
  }
};

#endif // CLICHATMSG_H
