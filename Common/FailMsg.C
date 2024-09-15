// Stonecutters CS351 S03 -*- C++ -*-

#include <iostream>
#include <sstream>
#include "FailMsg.h"
#include "FrameParser.h"

const std::string FailMsg::_keyword("FL");

FailMsg::FailMsg(std::istream &in)
  : Message(_keyword), _text(FrameParser::GrabString(in)) {}

const std::string FailMsg::Innards() const {
  return FrameParser::GenString(_text);
}
