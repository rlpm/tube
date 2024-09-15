// Stonecutters CS351 S03 -*- C++ -*-

#ifndef EMPIREMSG_H
#define EMPIREMSG_H

// includes
#include <string>
#include "Message.h"

class EmpireMsg : public Message {
public:

  EmpireMsg(int e)
    : Message(_keyword), _e(e) {};
  EmpireMsg(std::istream &);
  ~EmpireMsg(){};

  static std::string Keyword() { return _keyword; };
  virtual const std::string Innards() const;

  int GetEmpire() const { return _e; };

private:
  static const std::string _keyword;
  int _e;
};

#endif // EMPIREMSG_H
