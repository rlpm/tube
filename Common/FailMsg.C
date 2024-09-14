// Stonecutters CS351 S03 -*- C++ -*-

#include <iostream>
#include <sstream>
#include "FailMsg.h"
#include "FrameParser.h"

const string FailMsg::_keyword("FL");

FailMsg::FailMsg(istream &in)
  : Message(_keyword), _text(FrameParser::GrabString(in)) {}

const string FailMsg::Innards() const {
  return FrameParser::GenString(_text);
}
