// Stonecutters CS351 S03 -*- C++ -*-

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
