// Stonecutters CS351 S03 -*- C++ -*-

// This code is based on ChatO by Dave Ackley
// Original Copyright notice and GPL disclaimer:

// Copyright (C) 1996-2003 Dave Ackley.
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; either version 2 of the
// License, or (at your option) any later version.
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software Foundation, 
// Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

#include <iostream>
#include <sstream>
#include <errno.h>     // for ETIMEDOUT
#include <algorithm>   // for find()
#include <signal.h>    // for signal/SIGPIPE/SIG_IGN
#include <stdlib.h>    // for atoi

#include "Network.h"
#include "Connection.h"
#include "FrameParser.h" // for the Frame Parser
#include "Message.h"   // for the Messages
#include "Exception.h"

// create a server-side connection
Connection::Connection(Network *n,iosockinet *i,sockinetaddr p) 
  : _net(n), _peer(p), _s(i), _dying(false)
{
  _net->Add(this);                 // add to _us
  (*_s)->recvtimeout(0);        // Don't block on input from this guy
  (*_s)->sendtimeout(0);        // Don't block on output to this guy
}

// create a client-side connection
Connection::Connection(string hostname, int port)
  : _net(NULL), _peer(hostname.c_str(),port), _dying(false)
{
  _s = new iosockinet;          // Create the new socket
  try {
    (*_s)->connect(_peer);
  }
  catch (sockerr & e) {
    delete _s;
    throw;
  }

  (*_s)->recvtimeout(0);        // Don't block on input from this guy
  (*_s)->sendtimeout(0);        // Don't block on output to this guy
}

Connection::~Connection()
{
  _dying = true;
  if (_s)
    (*_s)->sendtimeout(5);      // Be willing to wait 5 sec to send stuff..
  Output();                     // Take a final output shot
  if (_s)
    delete _s;                  // toss the iosockinet
  if (_net) {
    _net->Remove(this);         // then remove from network if any
  }
  int i;
  i = 0;
}

void Connection::Input()
{
  const int bufsize=1024;
  char buf[bufsize];            // Get buffer
  int rval;
  try { rval = (*_s)->read(buf,bufsize); } // Try the read
  catch (const sockerr & e) {   // ETIMEDOUT just means no input..
    if (e.serrno() != ETIMEDOUT) {
      throw EXCEPTION("Unhandled sockerr exception");
    }
    return;                     // Done if nothing to read
  }
  if (rval==0) {                // Return of 0 means connection closed
    delete this;                // Goodbye us
    return;                     // Done.
  } 
  if (rval>0) Process(string(buf,rval)); // Handle input (being 8BC)
}

void Connection::Output()
{
  int count = _out.size();  // Check pending output count
  if (count==0) return;         // Nothing to do..

  int wrote = 0;                // Assume we won't be able to write anything

  try {          
    wrote = (*_s)->write(_out.data(),count); // write can throw sockerr or int
  }
  catch (const sockerr & e) {   // Something got blown; let's look into it
    if (e.serrno() == ETIMEDOUT) { // Client isn't reading fast enough...
      cout << "Warning: Slow client!  Pending output = " << count << endl; 
    } else {                    // Some definite error here..  Just kill him..
      if (!_dying)
	delete this;            // Buh bye
      return;
    }
  }
  catch (int partial) {wrote = partial;}  // Remember how much got out

  if (wrote==count) _out = "";  // If we sent it all, just flush it, else
  else _out.erase(0,wrote);     // Chop out just what we shipped
}

