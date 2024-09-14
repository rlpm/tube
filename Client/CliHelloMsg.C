// Stonecutters CS351 S03 -*- C++ -*-
// $Id: CliHelloMsg.C,v 1.3 2003/05/09 04:53:17 rlpm Exp $

#include "CliHelloMsg.h"
#include "Control.h"

static bool reg=Message::Register(CliHelloMsg::Keyword(),CliHelloMsg::GenMsg);

void CliHelloMsg::Execute(Model *m) {
  Control *c = dynamic_cast<Control *>(m);
  assert(c);

  // process incoming through Control
  c->GotHello(GetId());
}
