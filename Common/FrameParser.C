// Stonecutters CS351 S03 -*- C++ -*-

#include <iostream>
#include <sstream>
#include <algorithm>   // for find()
#include <stdlib.h>    // for atoi
#include "FrameParser.h"
#include "Message.h"
#include "Exception.h"

FrameParser::FrameParser() : _state(HEADER), _flen(0) {}

FrameParser::~FrameParser() {}

void FrameParser::Reset(bool clearbuf) {
  if (clearbuf) // need to clear the input buffer as well
    _in = "";
  _state = HEADER;
  _flen = 0;
  _msg = "";
}

Message* FrameParser::GetMsg() {
  size_t pos;
  if (_state==HEADER) {
    pos = _in.find(":");           // Hunt for : (header delimiter)
    if (pos==string::npos)
      return NULL;                 // not enough data yet

    string count(_in,0,pos);       // get integer
    _in.erase(0,pos+1);            // Get rid of header

    for (unsigned int i=0;i<count.size();i++) {
      if (count[i] > '9' || count[i] < '0') {
        // bad header format, reset and return NULL
        Reset();
        throw EXCEPTION("Bad Header");
      }
    }

    _flen = atoi(count.c_str());
    if (_flen < 0 || _flen > 999999) {
      // error in header length
      Reset();
      throw EXCEPTION("Bad Length");
    }

    _state = DATA;                  // successfully read header bytes
  }
  if (_state==DATA) {               // try to read message
    if (_in.size() < _flen)
      return NULL;                  // not enough data

    string msg(_in,0,_flen);        // the payload
    _in.erase(0,_flen);             // get rid of excess
    _msg = msg;                     // remember it for next state

    _state = FOOTER1;               // done reading data
  }
  if (_state == FOOTER1) {
    if (!_in.size()) return NULL;   // not enough data

    if (_in[0] == '\r')
      _in.erase(static_cast<unsigned int>(0),1); // flush optional \r

    _state = FOOTER2;
  }
  if (_state == FOOTER2) {
    if (!_in.size()) return NULL;   // not enough data
    char c = _in[0];

    if (c == '\n') {
      _in.erase(static_cast<unsigned int>(0),1); // flush trailing \n
    } else {
      // incorrect frame!!!!
      Reset();
      throw EXCEPTION("No footer");
    }
    _state = DONE;                 // back to reading header
  }
  if (_state == DONE) {
    istringstream tmp(_msg);
    Message* msg = Message::GenMsg(tmp);
    Reset();
    return msg;
  }
  throw EXCEPTION("Bad State");
  return NULL;
}

string FrameParser::GenFrame(const string &in) {
  ostringstream buf;
  buf << GenString(in);
  buf << "\n";
  return buf.str();
}

string FrameParser::GenString(const string &in) {
  ostringstream buf;
  buf << in.size();
  buf << ":";
  buf << in;
  return buf.str();
}

string FrameParser::GrabKW(istream &in) {
  string out;
  char c;
  for (int i=0;i<2;i++) {
    if (!in.get(c))
      throw EXCEPTION("Input stream not long enough for keyword");
    out += c;
  }

  // make sure two chars followed by space
  if (!in.get(c) || !isspace(c)) throw EXCEPTION("Keyword not followed by space");

  SkipSpace(in);

  return out;
}

string FrameParser::GrabString(istream &in) {
  string out;
  char c;
  string len;

  // get the length chars
  while(in.get(c)) {
    if (c==':') break;
    // die if not a num
    if (c < '0' || c > '9')
      throw EXCEPTION("String length not a number");
    len += c;
  }

  if (c!=':') throw EXCEPTION("String delimiter : not found");

  // read the rest of the chars
  for (int i=atoi(len.c_str())-1;i>=0;i--) {
    if (!in.get(c)) throw EXCEPTION("String data not long enough");
    out += c;
  }

  SkipSpace(in);

  return out;
}

int FrameParser::GrabInt(istream &in) {
  int out;
  char c;
  string it;
  
  // get the chars
  while(in.get(c)) {
    if (isspace(c)) break;
    if ((c < '0' || c > '9') && (c != '-'))
      throw EXCEPTION("Int Bad Format");
    it += c;
  }

  // ignore additional trailing whitespace
  SkipSpace(in);

  out = atoi(it.c_str());

  return out;
}

void FrameParser::SkipSpace(istream &in) {
  char c = ' ';
  while(isspace(c))
    if (!in.get(c)) return;
  in.unget();
}

