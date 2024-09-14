// Stonecutters CS351 S03 -*- C++ -*-

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
