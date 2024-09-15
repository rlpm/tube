// Stonecutters CS351 S03 -*- C++ -*-

#ifndef SVRCHATMSG_H
#define SVRCHATMSG_H

// includes
#include "ChatMsg.h"

// forward declare
class Model;
class Commander;
class istream;

class SvrChatMsg : public ChatMsg {
public:
  SvrChatMsg(std::string t, std::string x) : ChatMsg(t,x) {};
  SvrChatMsg(std::istream &i) : ChatMsg(i) {};
  virtual void Execute(Model*);

  static Message* GenMsg(std::istream &i) {
    return new SvrChatMsg(i);
  }
};

#endif // SVRCHATMSG_H
