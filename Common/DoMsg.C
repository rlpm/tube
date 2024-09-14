// Stonecutters CS351 S03 -*- C++ -*-
// $Id: DoMsg.C,v 1.1 2003/05/07 22:58:56 rlpm Exp $

#include <sstream>
#include <iostream>
#include <stdlib.h>
#include "DoMsg.h"
#include "FrameParser.h"
#include "Exception.h"

const string DoMsg::_keyword("DO");

DoMsg::DoMsg(istream &in)
  : Message(_keyword), _i(FrameParser::GrabInt(in)), _o(in) {}

const string DoMsg::Innards() const {
  ostringstream buf;

  buf << _i << ' ' << _o;
  return buf.str();
}
