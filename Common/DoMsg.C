// Stonecutters CS351 S03 -*- C++ -*-

#include <sstream>
#include <iostream>
#include <stdlib.h>
#include "DoMsg.h"
#include "FrameParser.h"
#include "Exception.h"

DoMsg::DoMsg(std::istream &in)
  : Message(Keyword()), _i(FrameParser::GrabInt(in)), _o(in) {}

const std::string DoMsg::Innards() const {
  std::ostringstream buf;

  buf << _i << ' ' << _o;
  return buf.str();
}
