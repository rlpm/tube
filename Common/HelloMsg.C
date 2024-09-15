// Stonecutters CS351 S03 -*- C++ -*-

#include <iostream>
#include <sstream>
#include "HelloMsg.h"
#include "FrameParser.h"
#include "Exception.h"

const std::string HelloMsg::_keyword("HI");

HelloMsg::HelloMsg(std::istream &in)
  : Message(_keyword), _version(FrameParser::GrabInt(in)),
    _type(GrabType(in)), _id(FrameParser::GrabString(in)),
    _validator(FrameParser::GrabString(in)) {}

HelloMsg::Type HelloMsg::GrabType(std::istream &in) {
  Type t=__HI_END__;
  std::string tt(FrameParser::GrabKW(in));
// Do a little Macro dance
#define XX(a) if (tt == #a) t = a;
#include "HelloTypes"
#undef XX

  if (t == __HI_END__)
    throw EXCEPTION("Hello Message bad type");
  
  return t;
}

const std::string HelloMsg::Innards() const {
  std::ostringstream buf;
  
  buf << _version << " ";

  std::string t;

#define XX(a) if (_type == a) t=#a;
#include "HelloTypes"
#undef XX

  buf << t << " " << FrameParser::GenString(_id) << " "
      << FrameParser::GenString(_validator);

  return buf.str();
}
