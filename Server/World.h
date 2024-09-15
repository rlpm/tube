// Stonecutters CS351 S03 -*- C++ -*-

#ifndef WORLD_H
#define WORLD_H

// includes
#include <vector>
#include <list>
#include "Network.h"
#include "Countdown.h"
#include "Coord.h"
#include "Order.h"

//forward declarations
class Active;
class Commander;
class Empire;
class Grid;
class Message;
class City;
class SvrCqMsg;

//world class declaration
class World
{
public:

  enum Period {
    ONCEINIT = -1,
    GAMEINIT,
    GAMEPLAY,
    GAMEFIN,
    ONCEFIN
  };

  enum Phase {
    BEFORECOMMAND = -1,
    COMMAND = 0,
    GRACE = -2,
    DIPLOMACY = 1,
    UPDATE = 2,
    OUTCOME = 3
  };
    
  // build a World with certain parameters
  World(Coord size, int maxc, int speed, int wait, int port, int turns, bool pg,
	int grace, bool gm);
  ~World();

  // accept connections and echo stuff back to clients until death
  void Run();

  // remove a commander from the list
  void RemoveCommander(Commander *c);
  void ReassignCommander(Commander *, Empire*);

  // keep track of empires
  void AddEmpire(Empire*);
  void RemoveEmpire(Empire*);

  // keep track of actives
  void AddActive(Active*);
  void RemoveActive(Active*);
  void ShuffleActives(); // shuffle them for next update phase

  // Broadcast an event to all Commanders
  void Broadcast(Message &);

  // Check to make sure ID is not already in use by another Cmdr
  bool IdOK(std::string);

  // get a cmdr by name
  Commander* GetCommanderById(std::string);

  // If not in certain periods phases, or hellod status, send god chat msg
  bool CheckGamePlay(Commander *) const;
  bool CheckGracePhase(Commander *) const;
  bool CheckHellod(Commander *) const;

  // Process a mark turn mesage from a Commander
  void ProcessTurnMessage(Commander*,int,bool);

  // Remember a CQ message for this turn, for each empire
  void StoreCq(SvrCqMsg *,size_t);

  // get the next available serial number
  int NextSerial() { return _next_serial++; };

  // set standing orders for a location
  void Tell(Empire*,Coord,std::vector<Order>);

private:

  // build a random grid
  void BuildGrid();

  // build a city in a location with at least one walkable and one floatable
  void BuildCity(Empire*);

  // (try to) move on in game play
  void UpdatePeriod();
  void UpdatePhase();

  // Send Phase and Turn Info
  void SendPhase();
  void SendTurn();

  void PrintGrid();

  // Shhh!
  void GodMode(Commander *c);

  Grid* _grid;
  std::vector<Empire*> _empires;
  std::list<Commander*> _cmdrs;
  Network _net;
  int _current_turn;
  Period _period;
  Phase _phase;
  Countdown _blastoff;
  size_t _neededcmdrs;
  size_t _maxcmdrs;
  size_t _gamespeed;
  size_t _commandgrace;
  size_t _waitforcmdrs; // how long to stay in GAMEINIT
  int _maxturns;     // how many turns before forced end
  std::vector<SvrCqMsg*> _cqs; // all the CQs for this turn
  int _next_serial;
  Coord _size;
  std::list<Active*> _actives;
  std::vector<Active*> _up_actives;
  bool _printgrid; // whether or not to print the map each turn
  bool _gm; // whether or not god mode is available
};

#endif
