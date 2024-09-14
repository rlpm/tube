// Stonecutters CS351 S03 -*- C++ -*-
// $Id: FailMsg.C,v 1.1 2003/05/03 00:34:27 rlpm Exp $

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
