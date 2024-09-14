// Stonecutters CS351 S03 -*- C++ -*-
// $Id: SvrTellMsg.C,v 1.1 2003/05/08 23:52:41 rlpm Exp $

#include "SvrTellMsg.h"
#include "Commander.h"
#include "Empire.h"

static bool reg=Message::Register(SvrTellMsg::Keyword(),SvrTellMsg::GenMsg);

void SvrTellMsg::Execute(Model *m) {
  Commander *c = dynamic_cast<Commander*>(m);
  assert(m);
  
  // check that everything's kosher
  if (!c->GetWorld()->CheckHellod(c)) return;
  if (!c->GetWorld()->CheckGamePlay(c)) return;
  if (!c->GetWorld()->CheckGracePhase(c)) return;

  // do actual stuff
  c->GetEmpire()->Tell(GetCoord(),GetOrders());
}
