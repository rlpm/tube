// Stonecutters CS351 S03 -*- C++ -*-
// $Id: AlliesMsg.C,v 1.1 2003/05/05 20:31:01 rlpm Exp $

#include <sstream>
#include "AlliesMsg.h"
#include "FrameParser.h"

const string AlliesMsg::_keyword("AL");

AlliesMsg::AlliesMsg(istream &in)
  : Message(_keyword) {
  int i = FrameParser::GrabInt(in);
  for (;i!=0;i--)
    _i.push_back(FrameParser::GrabInt(in));
}

const string AlliesMsg::Innards() const {
  ostringstream buf;
  buf << _i.size();
  for (unsigned int i = 0; i<_i.size(); i++)
    buf << " " << _i[i];

  return buf.str();
}
