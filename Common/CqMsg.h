// Stonecutters CS351 S03 -*- C++ -*-

#ifndef CQMSG_H
#define CQMSG_H

// includes
#include <string>
#include "Message.h"

class CqMsg : public Message {
public:
  CqMsg(int tf, bool p, string tx)
    : Message(_keyword), _tofrom(tf), _peace(p), _text(tx) {};
  CqMsg(istream &);
  ~CqMsg(){};

  static string Keyword() { return _keyword; };
  virtual const string Innards() const;

  int GetToFrom() const { return _tofrom; };
  bool GetPeace() const { return _peace; };
  string GetText() const { return _text;};

private:
  static const string _keyword;
  int _tofrom;
  bool _peace;
  string _text;
};

#endif // CQMSG_H
