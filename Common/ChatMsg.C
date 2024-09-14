// Stonecutters CS351 S03 -*- C++ -*-

#include <iostream>
#include <sstream>
#include "ChatMsg.h"
#include "FrameParser.h"

const string ChatMsg::_keyword("CH");

ChatMsg::ChatMsg(istream &in)
  : Message(_keyword), _tofrom(FrameParser::GrabString(in)),
    _text(FrameParser::GrabString(in)) {}

const string ChatMsg::Innards() const {
  ostringstream buf;
  buf << FrameParser::GenString(_tofrom) << " "
      << FrameParser::GenString(_text);

  return buf.str();
}
