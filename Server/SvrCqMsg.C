// Stonecutters CS351 S03 -*- C++ -*-
// $Id: SvrCqMsg.C,v 1.4 2003/05/13 22:35:17 madanie Exp $

#include <cassert>
#include <string>

#include "SvrCqMsg.h"
#include "Commander.h"
#include "Empire.h"

static bool reg = Message::Register(CqMsg::Keyword(),SvrCqMsg::GenMsg);

void SvrCqMsg::Execute(Model *m) {
  Commander *c = dynamic_cast<Commander *>(m);
  assert(c);

  // check that everything's kosher
  if (!c->GetWorld()->CheckHellod(c)) return;
  if (!c->GetWorld()->CheckGamePlay(c)) return;
  if (!c->GetWorld()->CheckGracePhase(c)) return;

  // do actual stuff
  SvrCqMsg *hold = new SvrCqMsg(*this);

  c->GetWorld()->StoreCq(hold,c->GetEmpire()->GetId());

}
