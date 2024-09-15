// Stonecutters CS351 S03 -*- C++ -*-

#ifndef CLICONN_H
#define CLICONN_H

// Includes
#include <cassert>
#include "sockinet.h"
#include "Connection.h"
#include "FrameParser.h"

// Forward Declarations
class Control;
class Message;

class CliConn : public Connection {
public:
  CliConn(Control *, std::string, int); // ctor
  virtual ~CliConn() ;         // dtor

  void Run(); // waits, then calls input and output
  virtual void Process(const std::string&); // process data read in
                                       // (called by Connection::Input)

  void Notify(const Message&);         // format message and send

private:
  // define away shallow copies
  CliConn(const CliConn&);
  void operator=(const CliConn&);

  // don't let anyone call Send directly through a CliConn*
  virtual void Send(const std::string &){assert(0);};

  FrameParser _fp;    // The FrameParser to parse input and format output
  Control *_control;
};

#endif // CLICONN_H

