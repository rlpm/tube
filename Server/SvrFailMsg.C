// Stonecutters CS351 S03 -*- C++ -*-

#include <cassert>
#include <string>
#include <sstream>

#include "SvrFailMsg.h"
#include "Commander.h"
#include "Exception.h"

static bool reg = Message::Register(FailMsg::Keyword(),SvrFailMsg::GenMsg);

void SvrFailMsg::Execute(Model *m) {
  Commander *c = dynamic_cast<Commander *>(m);
  assert(c);

  ostringstream tmp;
  tmp << "FAIL: Cmdr:" << c->GetId() << " " << GetText();
  throw EXCEPTION(tmp.str());
}
