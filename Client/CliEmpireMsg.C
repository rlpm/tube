// Stonecutters CS351 S03 -*- C++ -*-
// $Id: CliEmpireMsg.C,v 1.2 2003/05/12 07:49:38 rlpm Exp $

#include "CliEmpireMsg.h"
#include "Control.h"

static bool reg=Message::Register(CliEmpireMsg::Keyword(),CliEmpireMsg::GenMsg);

void CliEmpireMsg::Execute(Model *m) {
  Control *c = dynamic_cast<Control*>(m);
  assert(c);
  c->HandleEmpireMsg(GetEmpire());
}
