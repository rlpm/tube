// Stonecutters CS351 S03 -*- C++ -*-
// $Id: SvrParamsMsg.h,v 1.1 2003/05/05 02:59:25 rlpm Exp $

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
