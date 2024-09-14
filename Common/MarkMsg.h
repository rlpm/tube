// Stonecutters CS351 S03 -*- C++ -*-

#ifndef MARKMSG_H
#define MARKMSG_H

// includes
#include <string>
#include "Message.h"

class MarkMsg : public Message {
public:
  enum Type {
#define XX(a) a,
#include "MarkTypes"
#undef XX
    __MK_END__
  };

  MarkMsg(Type t, int c, string tx)
    : Message(_keyword), _type(t), _code(c), _text(tx) {};
  MarkMsg(istream &);
  ~MarkMsg(){};

  static string Keyword() { return _keyword; };
  virtual const string Innards() const;

  Type GetType() const { return _type; };
  static Type GrabType(istream &);
  int GetCode() const { return _code; };
  string GetText() const { return _text; };

private:
  static const string _keyword;
  Type _type;
  int _code;
  string _text;
};

#endif // MARKMSG_H
