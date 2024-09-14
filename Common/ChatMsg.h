// Stonecutters CS351 S03 -*- C++ -*-

#ifndef CHATMSG_H
#define CHATMSG_H

// includes
#include <string>
#include "Message.h"

class ChatMsg : public Message {
public:
  ChatMsg(string tf, string tx)
    : Message(_keyword), _tofrom(tf), _text(tx) {};
  ChatMsg(istream &);
  ~ChatMsg(){};

  static string Keyword() { return _keyword; };
  virtual const string Innards() const;

  string GetToFrom() const { return _tofrom; };
  string GetText() const { return _text;};

private:
  static const string _keyword;
  string _tofrom;
  string _text;
};

#endif // CHATMSG_H
