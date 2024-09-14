// Stonecutters CS351 S03 -*- C++ -*-
// $Id: CliMarkMsg.C,v 1.4 2003/05/10 04:02:09 snowtrp Exp $

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
