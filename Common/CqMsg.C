// Stonecutters CS351 S03 -*- C++ -*-

#include <sstream>
#include "CqMsg.h"
#include "FrameParser.h"
#include "Exception.h"

CqMsg::CqMsg(std::istream &in)
  : Message(Keyword()), _tofrom(FrameParser::GrabInt(in)) {
  int tmp = FrameParser::GrabInt(in);
  if (tmp != 0 && tmp != 1)
    throw EXCEPTION("Invalid peace value");
  _peace = tmp;
  _text = FrameParser::GrabString(in);
}

const std::string CqMsg::Innards() const {
  std::ostringstream buf;
  buf << _tofrom << " ";
  if (_peace) buf << "1";
  else buf << "0";
  buf << " " << FrameParser::GenString(_text);

  return buf.str();
}
