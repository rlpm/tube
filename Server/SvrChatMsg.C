// Stonecutters CS351 S03 -*- C++ -*-
// $Id: SvrChatMsg.C,v 1.10 2003/05/13 22:35:17 madanie Exp $

#include <cassert>
#include <string>

#include "SvrChatMsg.h"
#include "Commander.h"
#include "Empire.h"

static bool reg = Message::Register(ChatMsg::Keyword(),SvrChatMsg::GenMsg);

void SvrChatMsg::Execute(Model *m) {
  Commander *c = dynamic_cast<Commander *>(m);
  assert(c);

  // check that everything's kosher
  if (!c->GetWorld()->CheckHellod(c)) return;
  if (!c->GetWorld()->CheckGracePhase(c)) return;

  // do actual stuff
  SvrChatMsg outbound(c->GetId(),GetText());

  if (GetToFrom().size() == 0) { // broadcast
    if (c->GetEmpire()) { // game on!
      c->GetEmpire()->Broadcast(outbound);
    } else { // game init phase
      c->GetWorld()->Broadcast(outbound);
    }
  } else {
    Commander* to = c->GetWorld()->GetCommanderById(GetToFrom());

    if (to) // send to only one person
      to->Notify(outbound);
  }
}
