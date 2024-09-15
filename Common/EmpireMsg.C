// Stonecutters CS351 S03 -*- C++ -*-

#include <iostream>
#include <sstream>
#include "EmpireMsg.h"
#include "FrameParser.h"
#include "Exception.h"

const std::string EmpireMsg::_keyword("EM");

EmpireMsg::EmpireMsg(std::istream &in)
  : Message(_keyword), _e(FrameParser::GrabInt(in)) {}

const std::string EmpireMsg::Innards() const {
  std::ostringstream buf;  
  buf << _e;
  return buf.str();
}
