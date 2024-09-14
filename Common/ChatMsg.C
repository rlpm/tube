// Stonecutters CS351 S03 -*- C++ -*-
// $Id: ChatMsg.C,v 1.3 2003/05/02 07:19:03 rlpm Exp $

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
