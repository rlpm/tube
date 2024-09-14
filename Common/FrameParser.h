// Stonecutters CS351 S03 -*- C++ -*-
// $Id: FrameParser.h,v 1.8 2003/05/11 18:50:10 rlpm Exp $

#ifndef FRAMEPARSER_H
#define FRAMEPARSER_H

#include <string>
#include <sys/types.h>

// A 'Frame' represents data sent across the network.
// The Header is an ascii decimal integer [0,999999] followed by ':'
// The Data is the number of bytes specfied in the header
// The Footer is an optional '\r' followed by '\n'

class Message; // forward declare what can come out of a FrameParser
class ostream;

class FrameParser {
public:
  FrameParser();                 // Only ctor..
  ~FrameParser();                // free data

  void AddData(const string &b) {_in += b;};  // Add more data
  Message* GetMsg();              // Return a Message Object if done

  static string GenFrame(const string &); // Generate a frame string
  static string GenString(const string &); // Generate a message string

  static string GrabKW(istream &);     // get 2 chars off stream
  static string GrabString(istream &); // Get tubestring
  static int GrabInt(istream &);       // Get tubeint
  static void SkipSpace(istream &);    // skip isspace chars
  
private:

  void Reset(bool clearbuf=false);   // Reset parser

  string _in;  // the buffer for data passed in

  // a state enum for what we're reading 
  enum __state {
    HEADER,
    DATA,
    FOOTER1, // since \r is optional
    FOOTER2,
    DONE
  };

  __state _state;    // reading the header, data, footer, or we're
                     // done
  size_t _flen;      // the pending input frame length
  string _msg;       // the text of the pending message
};

#endif // FRAMEPARSER_H
