// Stonecutters CS351 S03 -*- C++ -*-

#include <sstream>
#include <time.h>

#include "CliConn.h"
#include "Connection.h"
#include "FrameParser.h" // for the Frame Parser
#include "Message.h"     // for the Messages
#include "Control.h"     // where to send Messages
#include "Exception.h"
#include "CliFailMsg.h"

// create a client-side connection
CliConn::CliConn(Control *f, std::string host, int port)
  : Connection(host,port), _control(f) {}

CliConn::~CliConn() {
  _control->RemoveConn();
}

void CliConn::Run() {
  struct timespec wait = {0,100}; // wait a bit so client doesn't hose processor
  nanosleep(&wait,NULL);
  try {
    try {
      Output(); // output first in case input deletes us
      Input();
    } catch (Exception e) {
      throw;
    } catch (...) {
      throw EXCEPTION("Unknown Error!!!");
    }
  } catch (Exception e) {
    _control->FailMsg(e.ToString());
    CliFailMsg ob(e.ToString());
    Notify(ob);
    delete this;
  }
}

void CliConn::Process(const std::string & b) // Called with new input in b
{
  Message *msg;
  _fp.AddData(b);

  while ((msg = _fp.GetMsg())) {
    _control->Process(msg);
    delete msg;
  }
}

void CliConn::Notify(const Message &b) {
  Connection::Send(b.ToFrame());
}
