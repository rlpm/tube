// Stonecutters CS351 S03 -*- C++ -*-
// $Id: Model.h,v 1.1 2003/05/01 23:57:27 rlpm Exp $

#ifndef MODEL_H
#define MODEL_H

#include "Message.h"

class Model {
public:
  Model(){};
  virtual ~Model(){};

  void Process(Message*);

private:
};

#endif // MODEL_H
