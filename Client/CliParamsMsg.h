// Stonecutters CS351 S03 -*- C++ -*-
// $Id: CliParamsMsg.h,v 1.1 2003/05/05 22:53:27 rlpm Exp $

#ifndef CLIPARAMSMSG_H
#define CLIPARAMSMSG_H

// includes
#include "ParamsMsg.h"

// forward declare
class Model;
class istream;

class CliParamsMsg : public ParamsMsg {
public:
  CliParamsMsg(int w, int h, int e, int s) : ParamsMsg(w,h,e,s) {};
  CliParamsMsg(istream &i) : ParamsMsg(i) {};
  virtual void Execute(Model*);

  static Message* GenMsg(istream &i) {
    return new CliParamsMsg(i);
  }

private:
};

#endif // CLIPARAMSMSG_H
