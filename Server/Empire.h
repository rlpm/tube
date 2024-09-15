// Stonecutters CS351 S03 -*- C++ -*-

#ifndef EMPIRE_H
#define EMPIRE_H

//class includes
#include <vector>
#include <list>
#include <sys/types.h>
#include "World.h"
#include "Order.h"

//forward declarations
class Active;
class Commander;
class Message;

//class declaration
class Empire
{
  friend class World;
 
public:
  //not really sure what all is needed here
  Empire(World*);
  ~Empire();
  // keep track of actives, tell world about them as well
  void AddActive(Active*);
  void RemoveActive(Active*);
  // Broadcast msg to all Commanders
  void Broadcast(Message &) const;
  void RequestAlly(size_t, bool); // used by Communique Message
  bool IsAllyOf(Empire *e) const;
  size_t GetId() const { return _id;};
  void RemoveCommander(Commander*);
  void AddCommander(Commander*);
  int NextSerial() {return _w->NextSerial();};
  void SendContactsMsg();
  World* GetWorld() const { return _w; };
  bool Do(int,Order); // tell a unit to do something
  void Tell(Coord,std::vector<Order>); // store standing orders
  bool CheckAlive() const; // if we have sufficient keepalive units to stay alive
private:
  std::list<Active*> _actives;
  std::list<Commander*> _cmdrs;
  std::vector<bool> _allies;
  World *_w;
  size_t _id;
};

#endif
