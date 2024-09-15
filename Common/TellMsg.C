// Stonecutters CS351 S03 -*- C++ -*-

#include <sstream>
#include <iostream>
#include <stdlib.h>
#include "TellMsg.h"
#include "FrameParser.h"
#include "Exception.h"

TellMsg::TellMsg(std::istream &in)
  : Message(Keyword()), _c(in) {
  int i = FrameParser::GrabInt(in);
  for (;i!=0;i--) {
    Order o(in);
    _os.push_back(o);
  }
}

const std::string TellMsg::Innards() const {
  std::ostringstream buf;

  buf << _c << ' ' << _os.size();
  for (unsigned int i = 0; i < _os.size(); i++)
    buf << ' ' << _os[i];

  return buf.str();
}
