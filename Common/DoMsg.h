// Stonecutters CS351 S03 -*- C++ -*-

#ifndef DOMSG_H
#define DOMSG_H

// includes
#include "Message.h"
#include "Order.h"

class DoMsg : public Message {
public:

  DoMsg(int i, Order o) : Message(Keyword()), _i(i), _o(o) {};
  DoMsg(std::istream &);
  ~DoMsg(){};

  static std::string Keyword() { return "DO"; };
  virtual const std::string Innards() const;

  int GetId() const { return _i; };
  Order GetOrder() const { return _o; };

private:
  int _i;
  Order _o;
};

#endif // DOMSG_H
