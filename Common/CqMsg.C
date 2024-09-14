// Stonecutters CS351 S03 -*- C++ -*-
// $Id: CqMsg.C,v 1.1 2003/05/05 12:04:37 rlpm Exp $

#include <sstream>
#include "CqMsg.h"
#include "FrameParser.h"
#include "Exception.h"

const string CqMsg::_keyword("CQ");

CqMsg::CqMsg(istream &in)
  : Message(_keyword), _tofrom(FrameParser::GrabInt(in)) {
  int tmp = FrameParser::GrabInt(in);
  if (tmp != 0 && tmp != 1)
    throw EXCEPTION("Invalid peace value");
  _peace = tmp;
  _text = FrameParser::GrabString(in);
}

const string CqMsg::Innards() const {
  ostringstream buf;
  buf << _tofrom << " ";
  if (_peace) buf << "1";
  else buf << "0";
  buf << " " << FrameParser::GenString(_text);

  return buf.str();
}
