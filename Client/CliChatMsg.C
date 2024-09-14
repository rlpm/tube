// Stonecutters CS351 S03 -*- C++ -*-

#include "CliChatMsg.h"
#include "Control.h"
#include "Exception.h"

static bool reg = Message::Register(ChatMsg::Keyword(),CliChatMsg::GenMsg);

void CliChatMsg::Execute(Model *m) {
   Control *c = dynamic_cast<Control *>(m);
  assert(c);

  c->ChatIn(GetToFrom(),GetText());
}
