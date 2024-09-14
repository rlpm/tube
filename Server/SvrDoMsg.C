// Stonecutters CS351 S03 -*- C++ -*-

#include <sstream>
#include "SvrDoMsg.h"
#include "Commander.h"
#include "Empire.h"
#include "SvrChatMsg.h"

static bool reg=Message::Register(SvrDoMsg::Keyword(),SvrDoMsg::GenMsg);

void SvrDoMsg::Execute(Model *m) {
  Commander *c = dynamic_cast<Commander*>(m);
  assert(m);
  
  // check that everything's kosher
  if (!c->GetWorld()->CheckHellod(c)) return;
  if (!c->GetWorld()->CheckGamePlay(c)) return;
  if (!c->GetWorld()->CheckGracePhase(c)) return;

  // do actual stuff
  if (!c->GetEmpire()->Do(GetId(),GetOrder())) {
    ostringstream tmp;
    tmp << "You do not command Unit #" << GetId();
    SvrChatMsg ob("",tmp.str());
    c->Notify(ob);
  }
}
