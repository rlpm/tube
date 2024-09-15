// Stonecutters CS351 S03 -*- C++ -*-

#include <iostream>
#include <sstream>
#include "MarkMsg.h"
#include "FrameParser.h"
#include "Exception.h"

MarkMsg::MarkMsg(std::istream &in)
  : Message(Keyword()),
    _type(GrabType(in)),
    _code(FrameParser::GrabInt(in)),
    _text(FrameParser::GrabString(in)) {}

MarkMsg::Type MarkMsg::GrabType(std::istream &in) {
  Type t=__MK_END__;
  std::string tt(FrameParser::GrabKW(in));
// Do a little Macro dance
#define XX(a) if (tt == #a) t = a;
#include "MarkTypes"
#undef XX

  if (t == __MK_END__)
    throw EXCEPTION("Mark Message bad type");
  
  return t;
}

const std::string MarkMsg::Innards() const {
  std::ostringstream buf;
  std::string t;

#define XX(a) if (_type == a) t=#a;
#include "MarkTypes"
#undef XX

  buf << t << " " << _code << " " << FrameParser::GenString(_text);

  return buf.str();
}
