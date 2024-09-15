// Stonecutters CS351 S03 -*- C++ -*-

#ifndef CQMSG_H
#define CQMSG_H

// includes
#include <string>
#include "Message.h"

class CqMsg : public Message {
public:
  CqMsg(int tf, bool p, std::string tx)
    : Message(Keyword()), _tofrom(tf), _peace(p), _text(tx) {};
  CqMsg(std::istream &);
  ~CqMsg(){};

  static std::string Keyword() { return "CQ"; };
  virtual const std::string Innards() const;

  int GetToFrom() const { return _tofrom; };
  bool GetPeace() const { return _peace; };
  std::string GetText() const { return _text;};

private:
  int _tofrom;
  bool _peace;
  std::string _text;
};

#endif // CQMSG_H
