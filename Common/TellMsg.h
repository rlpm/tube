// Stonecutters CS351 S03 -*- C++ -*-

#ifndef TELLMSG_H
#define TELLMSG_H

// includes
#include <vector>
#include "Message.h"
#include "Order.h"

class TellMsg : public Message {
public:

  TellMsg(Coord c, std::vector<Order> os) : Message(Keyword()), _c(c), _os(os) {};
  TellMsg(std::istream &);
  ~TellMsg(){};

  static std::string Keyword() { return "TL"; };
  virtual const std::string Innards() const;

  Coord GetCoord() const { return _c; };
  std::vector<Order> GetOrders() const { return _os; };

private:
  Coord _c;
  std::vector<Order> _os;
};

#endif // TELLMSG_H
