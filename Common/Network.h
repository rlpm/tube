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

// A 'Network' represents the entire chat server.  We build one of
// these at program initialization time and don't tear it down until
// the program is exiting.  The Network manages listening for new
// Connections and performing all actions that iterate over the
// existing Connections (with a list of pointers in '_us' for that.)

#ifndef NETWORK_H
#define NETWORK_H

#include <list>
#include <string>
#include <sys/types.h>
#include "sockinet.h"

class Connection;

class Network {
public:
  Network(int portno);  // Initialize a network listener on a port
  ~Network();           // Clean up a network

  string Host() const { return _listener.localhost(); } // Server host name
  int Port() const { return _listener.localport(); }    // Server port
  int Count() const { return _us.size(); }        // User count

  // Register the function to get an instance of a class derivece from
  // Connection
  void Register(Connection * (*)(Network *n, iosockinet *, sockinetaddr));

  Connection* Accept() ;        // Check for new connections, accept one if so
  void Input() ;                // Check for input ready from each connection
  void Output() ;               // Ship available output to each connection

  void Broadcast(const string & msg) ; // Send to all connections

  void Add(Connection *) ;      // Add a Connection to _us
  void Remove(Connection *) ;   // Remove a Connection from _us

private:
  sockinetbuf _listener;        // Sockbuf for listening for new connections
  typedef list<Connection*> Lcxn; // Type for our user list
  Lcxn _us;                     // Master user list
  bool _logit;

  // A pointer to the actual function to get an instance of a class
  // derived from Connection
  Connection* (*_nc)(Network *n, iosockinet *, sockinetaddr);
};

#endif // NETWORK_H

