// Stonecutters CS351 S03 -*- C++ -*-

#include "Model.h"

void Model::Process(Message*m) {
  m->Execute(this);
}
