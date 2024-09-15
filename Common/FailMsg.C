// Stonecutters CS351 S03 -*- C++ -*-

#include <iostream>
#include <sstream>
#include "FailMsg.h"
#include "FrameParser.h"

FailMsg::FailMsg(std::istream &in)
  : Message(Keyword()), _text(FrameParser::GrabString(in)) {}

const std::string FailMsg::Innards() const {
  return FrameParser::GenString(_text);
}
