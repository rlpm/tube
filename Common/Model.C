// Stonecutters CS351 S03 -*- C++ -*-
// $Id: Model.C,v 1.1 2003/05/01 23:57:27 rlpm Exp $

#include "Model.h"

void Model::Process(Message*m) {
  m->Execute(this);
}
