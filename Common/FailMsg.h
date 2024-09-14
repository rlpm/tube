// Stonecutters CS351 S03 -*- C++ -*-

#ifndef FAILMSG_H
#define FAILMSG_H

// includes
#include <string>
#include "Message.h"

class FailMsg : public Message {
public:
  FailMsg(string t) : Message(_keyword), _text(t) {};
  FailMsg(istream &);
  ~FailMsg(){};

  static string Keyword() { return _keyword; };
  virtual const string Innards() const;

  string GetText() const { return _text;};

private:
  static const string _keyword;
  string _text;
};

#endif // FAILMSG_H
