// Stonecutters CS351 S03 -*- C++ -*-

#include <sstream>

#include "Commander.h"
#include "Connection.h"
#include "FrameParser.h" // for the Frame Parser
#include "Message.h"     // for the Messages
#include "World.h"
#include "Exception.h"
#include "SvrFailMsg.h"
#include "SvrChatMsg.h"
#include "Empire.h"

// create a server-side connection
Commander::Commander(Network *n, iosockinet *i,sockinetaddr p)
  : Connection(n,i,p), _world(NULL), _empire(NULL), _hellod(false),
    _iscurrent(false), _badmsgs(0) {
  std::ostringstream tmp;
  tmp << Port() << "@" << Host();
  _id = tmp.str();
}

Commander::~Commander(){
  if (_empire) {
    // notify Empire of Dying Commander
    _empire->RemoveCommander(this);
  }
  if (_world) {
    _world->RemoveCommander(this);
  }
}

Connection* Commander::BuildCmdr(Network *n, iosockinet *i,
                                      sockinetaddr p) {
    return new Commander(n,i,p);
}

void Commander::Process(const std::string & b) // Called with new input in b
{
  _fp.AddData(b);

  Message *msg = NULL;

  try {
    while ((msg = _fp.GetMsg())) {
      Process(msg);
      delete msg;
    }
  }
  catch (Exception e) {
    std::cerr << "Cmdr:" << _id << " " << e << std::endl;
    Notify(SvrFailMsg(e.ToString()));
    delete this;
  }
}

void Commander::Notify(const Message &b) {
  Connection::Send(b.ToFrame());
}

void Commander::SetId(std::string name) {
  if (name == _id) return;
  if (_world -> IdOK(name))
    _id = name;
  else
    throw EXCEPTION("Name already in use");
}

void Commander::ThrowIfNotHellod() {
  if (!CheckHello())
    throw EXCEPTION("Did not receive HI message");
}

void Commander::BadMessage(std::string what) {
  if (_badmsgs++ >= 10)
    throw EXCEPTION("Too many bad messages. Did you ride the short bus "
		    "to school today? Goodbye.");

  SvrChatMsg ob("",what);
  Notify(ob);
}
