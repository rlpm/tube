// Stonecutters CS351 S03 -*- C++ -*-
// $Id: TellMsg.C,v 1.1 2003/05/08 23:52:41 rlpm Exp $

#include <sstream>
#include <iostream>
#include <stdlib.h>
#include "TellMsg.h"
#include "FrameParser.h"
#include "Exception.h"

const string TellMsg::_keyword("TL");

TellMsg::TellMsg(istream &in)
  : Message(_keyword), _c(in) {
  int i = FrameParser::GrabInt(in);
  for (;i!=0;i--) {
    Order o(in);
    _os.push_back(o);
  }
}

const string TellMsg::Innards() const {
  ostringstream buf;

  buf << _c << ' ' << _os.size();
  for (unsigned int i = 0; i < _os.size(); i++)
    buf << ' ' << _os[i];

  return buf.str();
}
