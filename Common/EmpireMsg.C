// Stonecutters CS351 S03 -*- C++ -*-

#include <iostream>
#include <sstream>
#include "EmpireMsg.h"
#include "FrameParser.h"
#include "Exception.h"

const string EmpireMsg::_keyword("EM");

EmpireMsg::EmpireMsg(istream &in)
  : Message(_keyword), _e(FrameParser::GrabInt(in)) {}

const string EmpireMsg::Innards() const {
  ostringstream buf;  
  buf << _e;
  return buf.str();
}
