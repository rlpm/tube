// Stonecutters CS351 S03 -*- C++ -*-

#include "CliAlliesMsg.h"
#include "Control.h"

static bool reg=Message::Register(CliAlliesMsg::Keyword(),CliAlliesMsg::GenMsg);

void CliAlliesMsg::Execute(Model *m) {
  Control *c = dynamic_cast<Control*>(m);
  assert(c);
  c->SetAllies(GetVec());
}
