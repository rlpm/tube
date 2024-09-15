// Stonecutters CS351 S03 -*- C++ -*-

#include <iostream>
#include <sstream>
#include <string>
#include <cassert>

#include "Message.h"
#include "FrameParser.h"
#include "Exception.h"

Message::MessageMap Message::_map;

bool Message::Register(std::string kw, Message*(*fn)(std::istream&)) {
  _map[kw] = fn;
  return true;
}   

Message* Message::GenMsg(std::istream &in) {
  std::string kw(FrameParser::GrabKW(in));
  MessageMap::iterator i = _map.find(kw);
  if (i == _map.end()) {
    std::ostringstream tmp;
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

const std::string Message::ToString() const {
  std::ostringstream buf;
  buf << _keyword << " " << Innards();
  return buf.str();
}

const std::string Message::ToFrame() const {
  return FrameParser::GenFrame(ToString());
}
