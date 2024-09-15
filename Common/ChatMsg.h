// Stonecutters CS351 S03 -*- C++ -*-

#ifndef CHATMSG_H
#define CHATMSG_H

// includes
#include <string>
#include "Message.h"

class ChatMsg : public Message {
public:
  ChatMsg(std::string tf, std::string tx)
    : Message(_keyword), _tofrom(tf), _text(tx) {};
  ChatMsg(std::istream &);
  ~ChatMsg(){};

  static std::string Keyword() { return _keyword; };
  virtual const std::string Innards() const;

  std::string GetToFrom() const { return _tofrom; };
  std::string GetText() const { return _text;};

private:
  static const std::string _keyword;
  std::string _tofrom;
  std::string _text;
};

#endif // CHATMSG_H
