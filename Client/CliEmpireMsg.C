// Stonecutters CS351 S03 -*- C++ -*-

#include <cassert>
#include "CliEmpireMsg.h"
#include "Control.h"

static bool reg=Message::Register(CliEmpireMsg::Keyword(),CliEmpireMsg::GenMsg);

void CliEmpireMsg::Execute(Model *m) {
  Control *c = dynamic_cast<Control*>(m);
  assert(c);
  c->HandleEmpireMsg(GetEmpire());
}
