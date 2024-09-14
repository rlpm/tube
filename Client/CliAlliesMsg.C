// Stonecutters CS351 S03 -*- C++ -*-
// $Id: CliAlliesMsg.C,v 1.3 2003/05/10 18:54:59 snowtrp Exp $

#include "CliAlliesMsg.h"
#include "Control.h"

static bool reg=Message::Register(CliAlliesMsg::Keyword(),CliAlliesMsg::GenMsg);

void CliAlliesMsg::Execute(Model *m) {
  Control *c = dynamic_cast<Control*>(m);
  assert(c);
  c->SetAllies(GetVec());
}
