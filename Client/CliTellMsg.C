// Stonecutters CS351 S03 -*- C++ -*-

#include "CliTellMsg.h"
#include "Exception.h"

static bool reg=Message::Register(CliTellMsg::Keyword(),CliTellMsg::GenMsg);

void CliTellMsg::Execute(Model *m) {
  throw EXCEPTION("Client does not accept TELL messages");
}
