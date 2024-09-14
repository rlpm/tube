// Stonecutters CS351 S03 -*- C++ -*-

#include "SvrEmpireMsg.h"
#include "Exception.h"

static bool reg=Message::Register(SvrEmpireMsg::Keyword(),SvrEmpireMsg::GenMsg);

void SvrEmpireMsg::Execute(Model *m) {
  // Server should NEVER get Empire Message
  delete this;
  throw EXCEPTION("Server does not accept Empire Messages");
}
