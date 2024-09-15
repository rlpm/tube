// Stonecutters CS351 S03 -*- C++ -*-

#include <cassert>
#include "CliHelloMsg.h"
#include "Control.h"

static bool reg=Message::Register(CliHelloMsg::Keyword(),CliHelloMsg::GenMsg);

void CliHelloMsg::Execute(Model *m) {
  Control *c = dynamic_cast<Control *>(m);
  assert(c);

  // process incoming through Control
  c->GotHello(GetId());
}
