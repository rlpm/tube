// Stonecutters CS351 S03 -*- C++ -*-

#include <iostream>
#include <sstream>
#include "ParamsMsg.h"
#include "FrameParser.h"
#include "Exception.h"

const std::string ParamsMsg::_keyword("PM");

ParamsMsg::ParamsMsg(std::istream &in)
  : Message(_keyword), _width(FrameParser::GrabInt(in)),
    _height(FrameParser::GrabInt(in)),
    _empires(FrameParser::GrabInt(in)),
    _speed(FrameParser::GrabInt(in)) {}

const std::string ParamsMsg::Innards() const {
  std::ostringstream buf;  
  buf << _width << " " << _height << " " << _empires << " " << _speed;
  return buf.str();
}
