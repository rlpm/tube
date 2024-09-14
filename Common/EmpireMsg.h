// Stonecutters CS351 S03 -*- C++ -*-
// $Id: EmpireMsg.h,v 1.1 2003/05/07 22:26:02 rlpm Exp $

#ifndef EMPIREMSG_H
#define EMPIREMSG_H

// includes
#include <string>
#include "Message.h"

class EmpireMsg : public Message {
public:

  EmpireMsg(int e)
    : Message(_keyword), _e(e) {};
  EmpireMsg(istream &);
  ~EmpireMsg(){};

  static string Keyword() { return _keyword; };
  virtual const string Innards() const;

  int GetEmpire() const { return _e; };

private:
  static const string _keyword;
  int _e;
};

#endif // EMPIREMSG_H
