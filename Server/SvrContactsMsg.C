// Stonecutters CS351 S03 -*- C++ -*-
// $Id: SvrContactsMsg.C,v 1.1 2003/05/06 00:58:24 rlpm Exp $

#include "SvrContactsMsg.h"
#include "Exception.h"

static bool reg=Message::Register(SvrContactsMsg::Keyword(),SvrContactsMsg::GenMsg);

void SvrContactsMsg::Execute(Model *m) {
  // Server should NEVER get Params Message
  throw EXCEPTION("Server does not accept Contacts Messages");
}
