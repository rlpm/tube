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

// A 'Connection' represents the server's relationship with a single
// client, or a client's relationship with a server.  For the server,
// build one of these when we accept a new connection, and tear it
// down when the connection closes.  Separate connection for a client.

#ifndef CONNECTION_H
#define CONNECTION_H

// Includes
#include <list>
#include <string>
#include <sys/types.h>
#include "sockinet.h"

// forward declarations
class Network;

class Connection {
public:
  Connection(Network *n,iosockinet *i,sockinetaddr p) ; // Server ctor
  Connection(std::string host, int port) ;        // Client ctor
  virtual ~Connection() ;                    // dtor

  const std::string Host() const { return _peer.gethostname(); } // Far end name
  const int Port() const { return _peer.getport(); }        // and port #

  void Input() ;                  // Try to read on this connection
  void Output() ;                 // Try to write on this connection
  virtual void Send(const std::string & o) { _out += o; } // Queue more output
  virtual void Process(const std::string&)=0; // process data read in
                                       // (called by Input)

private:
  // define away shallow copies
  Connection(const Connection&);
  void operator=(const Connection&);

  std::string _in;       // Incomplete input we've read from guy
  std::string _out;      // Stuff pending to send to guy

  Network *_net;      // The Network we're in
  sockinetaddr _peer; // Where this connection goes
  iosockinet * _s;    // A guy we're connected to
                      // We make this a pointer rather than an object
                      // because socket++ doesn't provide a copy
                      // constructor and getting the constructor
                      // sequence right is awful
  bool _dying;
};

#endif // CONNECTION_H
