// Stonecutters CS351 S03 -*- C++ -*-

#include <cassert>
#include "CliCqMsg.h"
#include "Control.h"

static bool reg = Message::Register(CqMsg::Keyword(),CliCqMsg::GenMsg);

void CliCqMsg::Execute(Model *m) {
  Control *c = dynamic_cast<Control*>(m);
  assert(c);
  
  std::ostringstream buf;
  buf << "Empire " << GetToFrom() << " wishes ";
  if (!GetPeace()) buf << "NOT ";
  buf << "to ally";
  if (GetText().size())
    buf << ": " << GetText();
  else
    buf << '.';

  c->HandleCqText(buf.str());
}
