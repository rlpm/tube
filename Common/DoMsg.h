// Stonecutters CS351 S03 -*- C++ -*-

#ifndef DOMSG_H
#define DOMSG_H

// includes
#include "Message.h"
#include "Order.h"

class ostream;
class istream;

class DoMsg : public Message {
public:

  DoMsg(int i, Order o) : Message(_keyword), _i(i), _o(o) {};
  DoMsg(istream &);
  ~DoMsg(){};

  static string Keyword() { return _keyword; };
  virtual const string Innards() const;

  int GetId() const { return _i; };
  Order GetOrder() const { return _o; };

private:
  static const string _keyword;

  int _i;
  Order _o;
};

#endif // DOMSG_H
