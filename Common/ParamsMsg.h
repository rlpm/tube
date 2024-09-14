// Stonecutters CS351 S03 -*- C++ -*-
// $Id: ParamsMsg.h,v 1.1 2003/05/05 02:59:25 rlpm Exp $

#ifndef PARAMSMSG_H
#define PARAMSMSG_H

// includes
#include <string>
#include "Message.h"

class ParamsMsg : public Message {
public:

  ParamsMsg(int w, int h, int e, int s)
    : Message(_keyword), _width(w), _height(h), _empires(e), _speed(s) {};
  ParamsMsg(istream &);
  ~ParamsMsg(){};

  static string Keyword() { return _keyword; };
  virtual const string Innards() const;

  int GetWidth() const { return _width; };
  int GetHeight() const { return _height; };
  int GetEmpires() const { return _empires; };
  int GetSpeed() const { return _speed; };

private:
  static const string _keyword;
  int _width;
  int _height;
  int _empires;
  int _speed;
};

#endif // PARAMSMSG_H
