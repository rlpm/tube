// Stonecutters CS351 S03 -*- C++ -*-
// $Id: CliTellMsg.C,v 1.2 2003/05/12 07:49:38 rlpm Exp $

#include "CliTellMsg.h"
#include "Exception.h"

static bool reg=Message::Register(CliTellMsg::Keyword(),CliTellMsg::GenMsg);

void CliTellMsg::Execute(Model *m) {
  throw EXCEPTION("Client does not accept TELL messages");
}
