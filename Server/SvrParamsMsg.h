// Stonecutters CS351 S03 -*- C++ -*-

#ifndef SVRPARAMSMSG_H
#define SVRPARAMSMSG_H

// includes
#include "ParamsMsg.h"

// forward declare
class Model;
class istream;

class SvrParamsMsg : public ParamsMsg {
public:
  SvrParamsMsg(int w, int h, int e, int s) : ParamsMsg(w,h,e,s) {};
  SvrParamsMsg(istream &i) : ParamsMsg(i) {};
  virtual void Execute(Model*);

  static Message* GenMsg(istream &i) {
    return new SvrParamsMsg(i);
  }

private:
};

#endif // SVRPARAMSMSG_H
