// Stonecutters CS351 S03 -*- C++ -*-
// $Id: SvrParamsMsg.C,v 1.1 2003/05/05 02:59:25 rlpm Exp $

#include "SvrParamsMsg.h"
#include "Exception.h"

static bool reg=Message::Register(SvrParamsMsg::Keyword(),SvrParamsMsg::GenMsg);

void SvrParamsMsg::Execute(Model *m) {
  // Server should NEVER get Params Message
  throw EXCEPTION("Server does not accept Parameters Messages");
}
