// Stonecutters CS351 S03 -*- C++ -*-

#include <cassert>
#include "CliFailMsg.h"
#include "Control.h"

static bool reg = Message::Register(FailMsg::Keyword(),CliFailMsg::GenMsg);

void CliFailMsg::Execute(Model *m) {
  Control *c = dynamic_cast<Control *>(m);
  assert(c);
  c->FailMsg(GetText());
}
