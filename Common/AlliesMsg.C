// Stonecutters CS351 S03 -*- C++ -*-

#include <sstream>
#include "AlliesMsg.h"
#include "FrameParser.h"

AlliesMsg::AlliesMsg(std::istream &in)
  : Message(Keyword()) {
  int i = FrameParser::GrabInt(in);
  for (;i!=0;i--)
    _i.push_back(FrameParser::GrabInt(in));
}

const std::string AlliesMsg::Innards() const {
  std::ostringstream buf;
  buf << _i.size();
  for (unsigned int i = 0; i<_i.size(); i++)
    buf << " " << _i[i];

  return buf.str();
}
