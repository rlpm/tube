// Stonecutters CS351 S03 -*- C++ -*-

#ifndef PARAMSMSG_H
#define PARAMSMSG_H

// includes
#include <string>
#include "Message.h"

class ParamsMsg : public Message {
public:

  ParamsMsg(int w, int h, int e, int s)
    : Message(_keyword), _width(w), _height(h), _empires(e), _speed(s) {};
  ParamsMsg(std::istream &);
  ~ParamsMsg(){};

  static std::string Keyword() { return _keyword; };
  virtual const std::string Innards() const;

  int GetWidth() const { return _width; };
  int GetHeight() const { return _height; };
  int GetEmpires() const { return _empires; };
  int GetSpeed() const { return _speed; };

private:
  static const std::string _keyword;
  int _width;
  int _height;
  int _empires;
  int _speed;
};

#endif // PARAMSMSG_H
