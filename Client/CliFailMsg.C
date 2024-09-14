// Stonecutters CS351 S03 -*- C++ -*-
// $Id: CliFailMsg.C,v 1.4 2003/05/11 06:17:59 rlpm Exp $

#include "CliFailMsg.h"
#include "Control.h"

static bool reg = Message::Register(FailMsg::Keyword(),CliFailMsg::GenMsg);

void CliFailMsg::Execute(Model *m) {
  Control *c = dynamic_cast<Control *>(m);
  assert(c);
  c->FailMsg(GetText());
}
