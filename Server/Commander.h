// Stonecutters CS351 S03 -*- C++ -*-

#ifndef COMMANDER_H
#define COMMANDER_H

// Includes
#include <cassert>
#include "sockinet.h"
#include "Connection.h"
#include "FrameParser.h"
#include "Model.h"

// Forward Declarations
class Network;
class Empire;
class World;
class Message;

class Commander : public Connection, public Model {
  friend class World;
  friend class Empire;
public:
  Commander(Network *n, iosockinet *i,sockinetaddr p);     // ctor
  virtual ~Commander() ;                                   // dtor

  // factory method
  static Connection* BuildCmdr(Network *n, iosockinet *i,sockinetaddr p);

  virtual void Process(const std::string&); // process data read in
                                       // (called by Connection::Input)
  void Notify(const Message&);         // format message and send

  // [rlpm] Polymorphism doesn't work across inheritance, so must
  // delegate to base class. Yuck.
  void Process(Message *m){Model::Process(m);};

  World* GetWorld() {return _world;};
  Empire* GetEmpire() {return _empire;};

  std::string GetId() {return _id;};
  void SetId(std::string);
  bool CheckHello() { return _hellod; };
  void GoodHello() { _hellod = true; };
  void ThrowIfNotHellod();
  bool CheckCurrent() { return _iscurrent; };
  void GoodCurrent() { _iscurrent = true; };
  void BadMessage(std::string);

private:
  // define away shallow copies
  Commander(const Commander&);
  void operator=(const Commander&);

  // don't let anyone call Send directly through a Commander*
  virtual void Send(const std::string &){assert(0);};

  FrameParser _fp;    // The FrameParser to parse input and format output
  World *_world;
  Empire *_empire;
  std::string _id;
  bool _hellod;    // whether initial HI msg rcvd or not
  bool _iscurrent;
  int _badmsgs;    // how many bad messages have been sent
};

#endif // COMMANDER_H

