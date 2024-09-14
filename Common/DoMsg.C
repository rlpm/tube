// Stonecutters CS351 S03 -*- C++ -*-

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
