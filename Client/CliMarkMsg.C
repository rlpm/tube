// Stonecutters CS351 S03 -*- C++ -*-

#include <cassert>
#include "CliMarkMsg.h"
#include "Control.h"

static bool reg=Message::Register(CliMarkMsg::Keyword(),CliMarkMsg::GenMsg);

void CliMarkMsg::Execute(Model *m) {
  Control *c = dynamic_cast<Control *>(m);
  assert(c);

  // process incoming through Control
  if (GetType() == MarkMsg::PD) {
    c->SetPeriod(GetCode(), GetText());
  }
  if(GetType() == MarkMsg::PH){
    c->SetPhase(GetCode(), GetText());
  }
  if(GetType() == MarkMsg::TN){
    c->SetTurn(GetCode(), GetText());
  }
}
