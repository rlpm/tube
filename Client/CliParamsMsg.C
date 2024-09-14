// Stonecutters CS351 S03 -*- C++ -*-
// $Id: CliParamsMsg.C,v 1.4 2003/05/13 22:54:59 rlpm Exp $

#include "CliParamsMsg.h"
#include "Control.h"
#include "Exception.h"

static bool reg=Message::Register(CliParamsMsg::Keyword(),CliParamsMsg::GenMsg);

void CliParamsMsg::Execute(Model *m) {
  Control *c = dynamic_cast<Control *>(m);
  assert(c);
  c->SetGridSize(GetWidth(), GetHeight());
  c->SetEmpires(GetEmpires());
  c->SetSpeed(GetSpeed());
}
