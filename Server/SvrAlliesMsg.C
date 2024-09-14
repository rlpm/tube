// Stonecutters CS351 S03 -*- C++ -*-
// $Id: SvrAlliesMsg.C,v 1.1 2003/05/05 20:31:01 rlpm Exp $

#include "SvrAlliesMsg.h"
#include "Exception.h"

static bool reg=Message::Register(SvrAlliesMsg::Keyword(),SvrAlliesMsg::GenMsg);

void SvrAlliesMsg::Execute(Model *m) {
  // Server should NEVER get Params Message
  throw EXCEPTION("Server does not accept Allies Messages");
}
