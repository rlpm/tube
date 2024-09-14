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
#include <errno.h>     // for ETIMEDOUT
#include <algorithm>   // for find()
#include <signal.h>    // for signal/SIGPIPE/SIG_IGN
#include <stdlib.h>    // for atoi
#include <cassert>     // for assert

#include "Network.h"
#include "Connection.h"

Network::Network(int portno)
  : _listener(sockbuf::sock_stream), _logit(true), _nc(NULL)
{
  for (int i = portno;i<portno + 10;i++) {
    try {
      sockinetaddr a(static_cast<long unsigned int>(INADDR_ANY), i); 
      _listener.bind(a);        // Make wildcard address w/port and go for it
      break;
    } catch (const sockerr & e) {
      cerr << "Can't bind port " << i << ": " << e.errstr() << endl;
    }
  }
  _listener.recvtimeout(0);     // Don't block on accept
  _listener.listen();           // Start listening for connection attempts
  signal(SIGPIPE,SIG_IGN);      // Ignore SIGPIPE so we don't crash on write
}

Network::~Network()
{
  for (Lcxn::iterator i = _us.begin(); i != _us.end(); ) {
    Lcxn::iterator j = i;   // Be careful because *i is about to die
    ++i;                    // So increment i now
    delete *j;              // Then let it go
  }
}

void Network::Register(Connection * (*c)(Network *n, iosockinet *,
                                         sockinetaddr)) {
  _nc = c;
}

Connection* Network::Accept()            // Go for (up to one) new connection
{
  if (!_listener.is_readready(0,1)) // Bail if nobody shows within a very short time
    return NULL;                         // (sets the Run loop idle rate)

  sockinetaddr peer;                     // A place to build incoming address
  iosockinet * i = new iosockinet(_listener.accept(peer)); // Accept it

  // make sure they registered the factory method
  assert (_nc);

  Connection *ret;
  ret = _nc(this,i,peer);
  return ret;
}

void Network::Input()           // Read from existing connections
{
  for (Lcxn::iterator i = _us.begin(); i != _us.end(); ) {
    Lcxn::iterator j = i;       // Be careful because *i might get deleted
    ++i;                        // So increment i now
    try {
      (*j)->Input();              // Then let the connection take a shot
    } catch (...) {
      cerr << "Unhandled exception in input from connection." << endl;
      delete *j;
    }
  }
}

void Network::Output()          // Write to existing connections
{
  for (Lcxn::iterator i = _us.begin(); i != _us.end(); ++i) {
    try {
      (*i)->Output();
    } catch (...) {
      cerr << "Unhandled exception in output connection." << endl;
      delete *i;
    }
  }
}

void Network::Broadcast(const string & b) 
{
  for (Lcxn::iterator i = _us.begin(); i != _us.end(); ++i)
    (*i)->Send(b);
  if (_logit) cout << b << flush; // If logging, also send to console
}

void Network::Add(Connection * c) {  _us.push_back(c);  }

void Network::Remove(Connection * c) 
{
  Lcxn::iterator i = find(_us.begin(),_us.end(),c);  // O(n) :(
  assert(i!=_us.end());         // Not found?  That would be a bug.
  _us.erase(i);                 // Lose him
}
