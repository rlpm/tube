// Stonecutters CS351 S03 -*- C++ -*-

#ifndef ALLIESMSG_H
#define ALLIESMSG_H

// includes
#include <vector>
#include "Message.h"

class AlliesMsg : public Message {
public:

  AlliesMsg(vector<int> i)
    : Message(_keyword), _i(i) {};
  AlliesMsg(istream &);
  ~AlliesMsg(){};

  static string Keyword() { return _keyword; };
  virtual const string Innards() const;

  vector<int> GetVec() const { return _i; };

private:
  static const string _keyword;

  vector<int> _i;
};

#endif // ALLIESMSG_H
