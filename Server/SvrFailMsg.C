// Stonecutters CS351 S03 -*- C++ -*-
// $Id: SvrFailMsg.C,v 1.3 2003/05/08 21:31:41 rlpm Exp $

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
