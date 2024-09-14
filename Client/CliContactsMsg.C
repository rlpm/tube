// Stonecutters CS351 S03 -*- C++ -*-
// $Id: CliContactsMsg.C,v 1.2 2003/05/11 06:17:59 rlpm Exp $

#include "CliContactsMsg.h"
#include "Control.h"

static bool reg=Message::Register(CliContactsMsg::Keyword(),CliContactsMsg::GenMsg);

void CliContactsMsg::Execute(Model *m) {
  Control *c = dynamic_cast<Control*>(m);
  assert(c);
  c->PlaceObjects(GetContacts(),GetTerrains(),GetActives());
}
