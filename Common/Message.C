// Stonecutters CS351 S03 -*- C++ -*-
// $Id: Message.C,v 1.10 2003/05/10 20:37:46 rory Exp $

#include <iostream>
#include <sstream>
#include <string>
#include <cassert>

#include "Message.h"
#include "FrameParser.h"
#include "Exception.h"

Message::MessageMap Message::_map;

bool Message::Register(string kw, Message*(*fn)(istream&)) {
  _map[kw] = fn;
  return true;
}   

Message* Message::GenMsg(istream &in) {
  string kw(FrameParser::GrabKW(in));
  MessageMap::iterator i = _map.find(kw);
  if (i == _map.end()) {
    ostringstream tmp;
    tmp << "No such Message type: " << kw;
    throw EXCEPTION(tmp.str());
  }
  /*******************************************************/
  // if message gets dropped there are leaks... fix later
  Message *ret = (i->second)(in);
  char c;
  if (in.get(c))
    throw EXCEPTION("Extra bytes at end of Message");
  return ret;
}

const string Message::ToString() const {
  ostringstream buf;
  buf << _keyword << " " << Innards();
  return buf.str();
}

const string Message::ToFrame() const {
  return FrameParser::GenFrame(ToString());
}
