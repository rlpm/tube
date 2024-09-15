// Stonecutters CS351 S03 -*- C++ -*-

#ifndef ALLIESMSG_H
#define ALLIESMSG_H

// includes
#include <vector>
#include "Message.h"

class AlliesMsg : public Message {
public:

  AlliesMsg(std::vector<int> i)
    : Message(_keyword), _i(i) {};
  AlliesMsg(std::istream &);
  ~AlliesMsg(){};

  static std::string Keyword() { return _keyword; };
  virtual const std::string Innards() const;

  std::vector<int> GetVec() const { return _i; };

private:
  static const std::string _keyword;

  std::vector<int> _i;
};

#endif // ALLIESMSG_H
