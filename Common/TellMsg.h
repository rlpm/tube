// Stonecutters CS351 S03 -*- C++ -*-

#ifndef TELLMSG_H
#define TELLMSG_H

// includes
#include <vector>
#include "Message.h"
#include "Order.h"

class ostream;
class istream;

class TellMsg : public Message {
public:

  TellMsg(Coord c, vector<Order> os) : Message(_keyword), _c(c), _os(os) {};
  TellMsg(istream &);
  ~TellMsg(){};

  static string Keyword() { return _keyword; };
  virtual const string Innards() const;

  Coord GetCoord() const { return _c; };
  vector<Order> GetOrders() const { return _os; };

private:
  static const string _keyword;

  Coord _c;
  vector<Order> _os;
};

#endif // TELLMSG_H
