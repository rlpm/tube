// Stonecutters CS351 S03 -*- C++ -*-
// $Id: SvrHelloMsg.C,v 1.9 2003/05/08 21:31:41 rlpm Exp $

#include <cassert>
#include <string>

#include "SvrHelloMsg.h"
#include "SvrMarkMsg.h"
#include "Commander.h"
#include "World.h"
#include "Exception.h"

const char* SvrHelloMsg::_svrid = "Stonecutters TUBE Server v0.1";

static bool reg=Message::Register(SvrHelloMsg::Keyword(),SvrHelloMsg::GenMsg);

void SvrHelloMsg::Execute(Model *m) {
  Commander *c = dynamic_cast<Commander *>(m);
  assert(c);

  // sanity checks
  if (c->CheckHello()) {
    c->BadMessage("Already received HI message");
    return;
  }

  if (!CheckVersion())
    throw EXCEPTION("Bad version number");

  Type t = GetType();
  if (t == SV)
    throw EXCEPTION("Cannot connect server to server!!!");

  string name = GetId();
  if (!name.size())
    throw EXCEPTION("Id must contain at least one character");
  if (name.size() > 15)
    name.erase(15,name.size()-1);
  for (unsigned int i = 0;i<name.size();i++) {
    if (!isprint(name[i])) {
      throw EXCEPTION("Invalid (non-printable) character in Id");
    }
  }

  if (!c->GetWorld()->IdOK(name)) {
    throw EXCEPTION("Id already in use");
  }

  c->SetId(name);
  c->GoodHello();

  SvrHelloMsg out1(GetVersion(),SV,_svrid,"");
  c->Notify(out1);

  SvrMarkMsg out2(MarkMsg::PD,0,"");
  c->Notify(out2);
}
