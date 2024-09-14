// Stonecutters CS351 S03 -*- C++ -*-

#include <cassert>
#include <string>

#include "SvrMarkMsg.h"
#include "Commander.h"
#include "World.h"
#include "Exception.h"

static bool reg=Message::Register(SvrMarkMsg::Keyword(),SvrMarkMsg::GenMsg);

void SvrMarkMsg::Execute(Model *m) {
  Commander *c = dynamic_cast<Commander *>(m);
  assert(c);

  // check that everything's kosher
  if (!c->GetWorld()->CheckHellod(c)) return;
  if (!c->GetWorld()->CheckGamePlay(c)) return;

  // check that it's the correct MK message
  if (GetType() != TN)
    throw EXCEPTION("Server only accepts MK TN");

  c->GetWorld()->ProcessTurnMessage(c,GetCode(),GetText()=="god mode");
}
