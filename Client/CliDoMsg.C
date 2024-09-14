// Stonecutters CS351 S03 -*- C++ -*-
// $Id: CliDoMsg.C,v 1.2 2003/05/12 07:49:38 rlpm Exp $

#include "CliDoMsg.h"
#include "Exception.h"

static bool reg=Message::Register(CliDoMsg::Keyword(),CliDoMsg::GenMsg);

void CliDoMsg::Execute(Model *m) {
  throw EXCEPTION("Client does not accept DO messages");
}
