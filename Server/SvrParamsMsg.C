// Stonecutters CS351 S03 -*- C++ -*-

#include "SvrParamsMsg.h"
#include "Exception.h"

static bool reg=Message::Register(SvrParamsMsg::Keyword(),SvrParamsMsg::GenMsg);

void SvrParamsMsg::Execute(Model *m) {
  // Server should NEVER get Params Message
  throw EXCEPTION("Server does not accept Parameters Messages");
}
