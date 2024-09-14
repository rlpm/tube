// Stonecutters CS351 S03 -*- C++ -*-
// $Id: CliCqMsg.C,v 1.4 2003/05/12 07:49:38 rlpm Exp $

#include "CliCqMsg.h"
#include "Control.h"

static bool reg = Message::Register(CqMsg::Keyword(),CliCqMsg::GenMsg);

void CliCqMsg::Execute(Model *m) {
  Control *c = dynamic_cast<Control*>(m);
  assert(c);
  
  ostringstream buf;
  buf << "Empire " << GetToFrom() << " wishes ";
  if (!GetPeace()) buf << "NOT ";
  buf << "to ally";
  if (GetText().size())
    buf << ": " << GetText();
  else
    buf << '.';

  c->HandleCqText(buf.str());
}
