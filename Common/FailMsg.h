// Stonecutters CS351 S03 -*- C++ -*-

#ifndef FAILMSG_H
#define FAILMSG_H

// includes
#include <string>
#include "Message.h"

class FailMsg : public Message {
public:
  FailMsg(std::string t) : Message(_keyword), _text(t) {};
  FailMsg(std::istream &);
  ~FailMsg(){};

  static std::string Keyword() { return _keyword; };
  virtual const std::string Innards() const;

  std::string GetText() const { return _text;};

private:
  static const std::string _keyword;
  std::string _text;
};

#endif // FAILMSG_H
