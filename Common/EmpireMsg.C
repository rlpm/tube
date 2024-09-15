// Stonecutters CS351 S03 -*- C++ -*-

#include <iostream>
#include <sstream>
#include "EmpireMsg.h"
#include "FrameParser.h"
#include "Exception.h"

EmpireMsg::EmpireMsg(std::istream &in)
  : Message(Keyword()), _e(FrameParser::GrabInt(in)) {}

const std::string EmpireMsg::Innards() const {
  std::ostringstream buf;  
  buf << _e;
  return buf.str();
}
