// Stonecutters CS351 S03 -*- C++ -*-
// $Id: ContactsMsg.C,v 1.4 2003/05/12 19:31:12 rlpm Exp $

#include <sstream>
#include <iostream>
#include <stdlib.h>
#include "ContactsMsg.h"
#include "FrameParser.h"
#include "Exception.h"

const string ContactsMsg::_keyword("CO");

ContactsMsg::ContactsMsg(istream &in)
  : Message(_keyword) {
  int i = FrameParser::GrabInt(in);
  for (;i!=0;i--) {
    Contact c(in);
    _c.push_back(c);
  }
  i = FrameParser::GrabInt(in);
  for (;i!=0;i--) {
    Terrain t(in);
    _t.push_back(t);
  }
  i = FrameParser::GrabInt(in);
  for (;i!=0;i--) {
    Active a(in);
    _a.push_back(a);
  }
}

const string ContactsMsg::Innards() const {
  ostringstream buf;

  buf << _c.size();
  for (unsigned int i = 0; i<_c.size(); i++)
    buf << " " << _c[i];

  buf << " " << _t.size();
  for (unsigned int i = 0; i<_t.size(); i++)
    buf << " " << _t[i];

  buf << " " << _a.size();
  for (unsigned int i = 0; i<_a.size(); i++)
    buf << " " << _a[i];

  return buf.str();
}

string ContactsMsg::Contact::ToString() const {
  ostringstream buf;
  buf << _c << " ";
  switch (_type) {
#define XX(a) case Order::a: buf << #a; break;
#include "UnitTypes"
#undef XX
  default: assert(0); break;
  }

  buf << ' ' << _e;
  
  return buf.str();
}


string ContactsMsg::Terrain::ToString() const {
  ostringstream buf;
  buf << _c << " ";
  switch (_type) {
#define XX(a) case Terrain::a: buf << #a; break;
#include "TerrainTypes"
#undef XX
  default: assert(0); break;
  }
  
  return buf.str();
}


string ContactsMsg::Active::ToString() const {
  ostringstream buf;
  buf << _c << " " << _id << " " << _hits << " " << _o;
  return buf.str();
}

istream& operator>>(istream &in, ContactsMsg::Contact &con) {
  in >> con._c;

  FrameParser::SkipSpace(in);

  con._type = Order::__UT_END__;
  string u = FrameParser::GrabKW(in);
#define XX(a) if (u == #a) con._type = Order::a;
#include "UnitTypes"
#undef XX
  
  if (con._type == Order::__UT_END__)
    throw EXCEPTION("Invalid UnitType");

  con._e = FrameParser::GrabInt(in);

  return in;
}

istream& operator>>(istream &in, ContactsMsg::Terrain &t) {
  in >> t._c;

  FrameParser::SkipSpace(in);

  t._type = ContactsMsg::Terrain::__TR_END__;
  string u = FrameParser::GrabKW(in);
#define XX(a) if (u == #a) t._type = ContactsMsg::Terrain::a;
#include "TerrainTypes"
#undef XX
  
  if (t._type == ContactsMsg::Terrain::__TR_END__)
    throw EXCEPTION("Invalid TerrainType");

  return in;
}

istream& operator>>(istream &in, ContactsMsg::Active &a) {
  in >> a._c;

  a._id = FrameParser::GrabInt(in);
  a._hits = FrameParser::GrabInt(in);

  in >> a._o;

  return in;
}

bool ContactsMsg::Contact::operator== (const ContactsMsg::Contact &c) const {
  return (_c == c._c && _type == c._type && _e == c._e);
}
