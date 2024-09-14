// Stonecutters CS351 S03 -*- C++ -*-

#include "CliDoMsg.h"
#include "Exception.h"

static bool reg=Message::Register(CliDoMsg::Keyword(),CliDoMsg::GenMsg);

void CliDoMsg::Execute(Model *m) {
  throw EXCEPTION("Client does not accept DO messages");
}
