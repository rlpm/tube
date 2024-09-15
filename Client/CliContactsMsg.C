// Stonecutters CS351 S03 -*- C++ -*-

#include <cassert>
#include "CliContactsMsg.h"
#include "Control.h"

static bool reg=Message::Register(CliContactsMsg::Keyword(),CliContactsMsg::GenMsg);

void CliContactsMsg::Execute(Model *m) {
  Control *c = dynamic_cast<Control*>(m);
  assert(c);
  c->PlaceObjects(GetContacts(),GetTerrains(),GetActives());
}
