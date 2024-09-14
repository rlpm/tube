// Stonecutters CS351 S03 -*- C++ -*-

#include "SvrContactsMsg.h"
#include "Exception.h"

static bool reg=Message::Register(SvrContactsMsg::Keyword(),SvrContactsMsg::GenMsg);

void SvrContactsMsg::Execute(Model *m) {
  // Server should NEVER get Params Message
  throw EXCEPTION("Server does not accept Contacts Messages");
}
