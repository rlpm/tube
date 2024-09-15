// Stonecutters CS351 S03 -*- C++ -*-

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>   // for find()
#include <time.h>
#include <stdlib.h>
#include <list>

#include "World.h"
#include "Network.h"
#include "Connection.h"
#include "Commander.h"
#include "SvrChatMsg.h"
#include "SvrFailMsg.h"
#include "SvrMarkMsg.h"
#include "SvrParamsMsg.h"
#include "SvrCqMsg.h"
#include "SvrAlliesMsg.h"
#include "SvrEmpireMsg.h"
#include "SvrContactsMsg.h"
#include "Empire.h"
#include "Exception.h"
#include "Land.h"
#include "Water.h"
#include "Mountain.h"
#include "City.h"


World::World(Coord size, int maxc, int speed, int wait, int port, int turns,
	     bool pg, int grace, bool gm)
  :_grid(NULL), _net(port), _current_turn(1), _period(ONCEINIT),
   _phase(COMMAND), _blastoff(0), _neededcmdrs(2),
   _maxcmdrs(maxc), _gamespeed(speed),
   _commandgrace(grace), _waitforcmdrs(wait), _maxturns(turns),
   _next_serial(0), _size(size), _printgrid(pg), _gm(gm)
{
  // above, we set the phase to COMMAND, so chat msgs can be sent during GAMEINIT

  // Make the network class build instances of Commander, not
  // instances of base class Connection
  _net.Register(Commander::BuildCmdr);

  // seed the PRNG
  srandom(time(NULL));

  // print host and port info
  std::cout << "Server " << _net.Host() << " listening on port " << _net.Port() << std::endl;

}

World::~World()
{
  for (size_t i=0;i<_empires.size();i++) {
    if (_empires[i]) {
      _empires[i]->_cmdrs.clear();
      delete _empires[i];
    }
  }
  for (std::list<Commander*>::iterator i = _cmdrs.begin(); i!=_cmdrs.end(); i++) {
    (*i)->_empire = NULL;
  }
  if(_grid)
    delete _grid;
}

// build random grid, no cities
void World::BuildGrid() {

  /////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////
  // default values                                      //
  // DO NOT CHANGE UNLESS YOU KNOW WHAT YOU ARE DOING!!! //
  float mincontmass = .1;                                //
  float minlandmass = .3;                                //
  float maxlandmass = .7;                                //
  /////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////

  // create empty grid
  _grid = new Grid(_size);

  // determine area of grid
  int area = _size.GetX() * _size.GetY();

  // determine minimum and maximum land mass
  int minarea = static_cast<int>(area * minlandmass);
  int maxarea = static_cast<int>(area * maxlandmass);
  int mincontsize = static_cast<int>(area * mincontmass);

  // randomize the amount of dry land we want
  int dryland = minarea + (random() % (1 + maxarea - minarea));
  int wantdryland = dryland;

  // LET THERE BE LAND!

  // new output string and chat msg for output to cout, clients
  SvrChatMsg ob("","foo!");
  std::string gen("Generating random map continents:");

  _blastoff = Countdown(2);
  Countdown longtime(10);
  Countdown reallylongtime(60);
  while (dryland > 0) {
    // random start location
    Coord start(random()%_size.GetX(),random()%_size.GetY());

    // If there's something already there, pick another spot
    if (_grid->Get(start)) {
      continue;
    }

    // place a mountain there
    _grid->Put(new Mountain,start);
    dryland--;

    // go in a random cardinal direction
    Grid::Direction dir = static_cast<Grid::Direction>(random()%4);
    Coord ptr = _grid->CoordAtDir(start,dir);

    // if nothing there, make land
    if (!_grid->Get(ptr)) {
      _grid->Put(new Land,ptr);
      dryland--;
    } else {
      continue;
    }

    // if enough dryland, quit
    if (dryland <= 0) break;

    // randomize size of steps for thi continent
    int steps = mincontsize + (random() % (1 + dryland));
    for (;steps;steps--) {

      // send update to client and cout
      if (_blastoff) {
	std::ostringstream tmp;
	tmp << gen << ' ' << ((wantdryland - dryland) * 100 / wantdryland) << '%';
	if (longtime) {
	  tmp << " This is taking forever. Why such a big map?";
	  longtime = Countdown(60);
	}
	ob = SvrChatMsg("",tmp.str());
	Broadcast(ob);
	_net.Output();
	std::cout << tmp.str() << std::endl;
	_blastoff = Countdown(2);
      }

      // start with a random cardinal direction
      dir = static_cast<Grid::Direction>(random()%4);

      // if it fails the checks below, iterate randomly over all four dirs
      int addend = 1 | (random()%4);

      int q;
      for (q = 0; q < 4 ; q++) {

	// set the actual direction we're going to look
	dir = static_cast<Grid::Direction>((dir + addend) % 4);

	// look at that spot
	Coord look = _grid->CoordAtDir(ptr,dir);
	GridAble *glook = _grid->Get(look);

	// if there is nothing there, see how many neighbors are something
	if (!glook) {
	  int neighbors = 0;
	  Neighborhood n = _grid->GetNeighborhood(look);
	  for (int j = 0; j != 8; j++) {
	    if (n[j]) neighbors++;
	  }

	  // if there are at least 2 somethings in the neighborhood, make land
	  if (neighbors > 1) {
	    _grid->Put(new Land,look);
	    dryland--;
	    ptr = look;
	    break;
	  }
	} else {
	  if (dynamic_cast<Mountain*>(glook)) {
	    GridAble *gptr = _grid->Get(ptr);
	    if (!dynamic_cast<Mountain*>(gptr)) {
	      // if ran into a mountain, HEAVE EARTH UPWARDS!
	      delete gptr;
	      _grid->Put(new Mountain,ptr);
	    }
	  }
	  ptr = look;
	  break;
	}
      }
      if (q == 4) {
	break;
      }
    }
  }

  std::string tmp(gen + " 100%");
  if (reallylongtime) tmp += " It's about friggin' time!";
  ob = SvrChatMsg("",tmp);
  Broadcast(ob);
  _net.Output();
  std::cout << tmp << std::endl;

  gen =  "Filling remaining map with water:";
  _blastoff = Countdown(2);
  longtime = Countdown(10);
  reallylongtime = Countdown(60);

  // torrential rain! (fill the rest with water)
  for (int i = 0; i != _size.GetX(); i++) {
    for (int j = 0; j != _size.GetY(); j++) {
      // send update to client and cout
      if (_blastoff) {
	std::ostringstream tmp;
	tmp << gen << ' ' << (((i * _size.GetY()) + j) * 100 / area) << '%';
	if (longtime) {
	  tmp << " Torrential downpour, eh?";
	  longtime = Countdown(60);
	}
	SvrChatMsg ob("",tmp.str());
	Broadcast(ob);
	_net.Output();
	std::cout << tmp.str() << std::endl;
	_blastoff = Countdown(2);
      }

      Coord c(i,j);

      if (_grid->Get(c)) {
	dryland++;
	continue;
      }

      // how many lands or mtns around?
      int neighbors = 0;
      Neighborhood n = _grid->GetNeighborhood(c);
      for (int j = 0; j != 8; j++) {
	if (n[j] && !dynamic_cast<Water*>(n[j])) {
	  neighbors++;
	}
      }

      // if it surrounded by lands and mtns, then fill it with land
      // (no little lakes)
      if (neighbors == 8) {
	_grid->Put(new Land,c);
	dryland++;
      } else {
	_grid->Put(new Water,c);
      }
    }
  }

  tmp = gen + " 100%";
  if (reallylongtime) tmp += "Alright, NOAH, I hope your game is fun!";
  ob = SvrChatMsg("",tmp);
  Broadcast(ob);
  _net.Output();
  std::cout << tmp << std::endl;
}

// find a place at random, if it has walkable and floatable nearby, build it,
// they will come. :)
void World::BuildCity(Empire *e) {
  Coord size = _grid->GetSize();
  while(1) {
    Coord at(random()%size.GetX(),random()%size.GetY());
    GridAble *g(_grid->Get(at));
    if (dynamic_cast<City*>(g)) continue; // don't delete old cities
    Neighborhood n(g->GetNeighborhood());
    bool floatable = false, walkable = false;
    int i;
    for (i = 0; i < 8; i++) {
      Static *s(dynamic_cast<Static*>(n[i]));
      assert(s);
      if (dynamic_cast<Water*>(s)) {
	floatable = true;
      } else if (dynamic_cast<Land*>(s)) {
	walkable = true;
      }
      if (floatable && walkable)
	break;
    }
    if (i == 8) continue;
    _grid->Clear(g);
    delete g;
    _grid->Put(new City(e),at);
    break;
  }
}

void World::Run() {
  while (_period != ONCEFIN) {
    UpdatePeriod();
    Connection *c;
    // keep accpeting new connections until there are no more to accept
    while ((c = _net.Accept())) {
      Commander *cmdr = dynamic_cast<Commander*>(c);
      assert(cmdr);
      if (_period != GAMEINIT) {
	Exception e = EXCEPTION("No longer accepting connections");
	cmdr->Notify(SvrFailMsg(e.ToString()));
	cmdr->Output();
	delete cmdr;
      } else if (_cmdrs.size() < _maxcmdrs) {
	_cmdrs.push_back(cmdr);
	cmdr->_world = this;
      } else {
	Exception e = EXCEPTION("Too many connections. Try again later");
	cmdr->Notify(SvrFailMsg(e.ToString()));
	cmdr->Output();
	delete cmdr;
      }
    }

    if (_gamespeed) {
      // only read from clients if in GAMEINIT period, or
      // GAMEPLAY period COMMAND PHASE    
      if (_period == GAMEINIT ||
	  (_period == GAMEPLAY && (_phase == COMMAND || _phase == GRACE)))
	_net.Input();

      _net.Output();
    }
  }
}

void World::RemoveCommander(Commander *c) {
  std::list<Commander*>::iterator i = find(_cmdrs.begin(),_cmdrs.end(),c);
  assert(i!=_cmdrs.end());
  _cmdrs.erase(i);
}

void World::AddEmpire(Empire *e)
{
  _empires.push_back(e);
  e->_id = _empires.size()-1;
}

void World::RemoveEmpire(Empire *e)
{
  for (size_t i = 0; i<_empires.size(); i++) {
    if (_empires[i] == e) {
      _empires[i] = NULL;
    }
  }
}

void World::Broadcast(Message &m) {
  for (std::list<Commander*>::iterator i = _cmdrs.begin(); i != _cmdrs.end(); i++)
    (*i)->Notify(m);
}

bool World::IdOK(std::string n) {
  for (std::list<Commander*>::iterator i = _cmdrs.begin(); i != _cmdrs.end(); i++)
    if ((*i)->_id == n)
      return false;
  return true;
}

Commander* World::GetCommanderById(std::string n) {
  for (std::list<Commander*>::iterator i = _cmdrs.begin(); i != _cmdrs.end(); i++)
    if ((*i)->_id == n)
      return *i;
  return NULL;
}

bool World::CheckGamePlay(Commander *c) const {
  if (_period != GAMEPLAY) {
    std::ostringstream tmp;
    tmp << "Message ignored. Not yet accepting GAME PLAY messages!!!";
    c->BadMessage(tmp.str());
    return false;
  }
  return true;
}

bool World::CheckGracePhase(Commander *c) const {
  if (_phase == GRACE) {
    std::ostringstream tmp;
    if (!c->_iscurrent) {
      tmp << "Message ignored. You must send MK TN soon!!!";
      c->BadMessage(tmp.str());
    } else { //easter egg message
      tmp << "Message ignored due to slow Commander. Rode short bus to school.";
      SvrChatMsg ob("",tmp.str());
      c->Notify(ob);
    }
    return false;
  }
  return true;
}

bool World::CheckHellod(Commander *c) const {
  if (!c->_hellod) {
    std::ostringstream tmp; //easter egg message
    tmp << "Get off the short bus and send hello message already!!!";
    c->BadMessage(tmp.str());
    return false;
  }
  return true;
}

void World::ProcessTurnMessage(Commander *c, int which, bool gm=false) {
  if (which == _current_turn) {
    c->_iscurrent = true;
    if (gm && _gm)
      GodMode(c);
  } else {
    throw EXCEPTION("Bad turn number, maybe you rode the short bus?");
  }
}

//send the entire grid down to the client
void World::GodMode(Commander *cmdr) {
  std::vector<ContactsMsg::Contact> c;
  std::vector<ContactsMsg::Terrain> t;
  std::vector<ContactsMsg::Active> a;
  for (int x = 0; x != _grid->GetSize().GetX(); x++) {
    for (int y = 0; y != _grid->GetSize().GetY(); y++) {
      GridAble *g = _grid->Get(Coord(x,y));
      Static *s = dynamic_cast<Static*>(g);
      assert(s);
      Active *act = s->GetVisible();
      if (!act) {
	bool notseen;
	ContactsMsg::Terrain tmp = s->GetTerrain(cmdr->GetEmpire(),notseen);
	t.push_back(tmp);
      }
    }
  }

  SvrContactsMsg ob(c,t,a);
  cmdr->Notify(ob);
}

//update all the actives on the grid
void World::UpdatePeriod() {
  if (_period == ONCEINIT) {
    _period = GAMEINIT;
    _blastoff = Countdown(_waitforcmdrs);
    // don't send the MK PD message until clients connect
  } else if (_period == GAMEINIT) {
    size_t cmdrs = 0;
    for (std::list<Commander*>::iterator i = _cmdrs.begin();
         i != _cmdrs.end() ; i++) {
      if ((*i)->CheckHello()) cmdrs++;
    }

    bool nextperiod = false;

    if (cmdrs == _maxcmdrs) {
      nextperiod = true;
    } else if (_blastoff) {
      if (cmdrs < _neededcmdrs) { // Time's up
	SvrChatMsg ob("","Not enough Commanders to play the game!!!");
	Broadcast(ob);
	_period = GAMEFIN; // end of (non-played) game
      } else {
	nextperiod = true;
      }
    }
    
    if (nextperiod) {
      // build the grid
      BuildGrid();

      // send some output to clients
      std::string tmp = "Building cities and Empires...";
      SvrChatMsg ob("",tmp);
      Broadcast(ob);
      _net.Output();
      std::cout << tmp << std::endl;

      // assign extra cities to dummy Empire #0
      // if no needed extra cities, that empire is not created
      size_t i=0;
      size_t emptycities = _cmdrs.size() * (1 + (random() % 3));
      if (emptycities) {
	new Empire(this);

	for (size_t i = 0; i < emptycities;i++) {
	  BuildCity(_empires[0]);
	}
      } else {
	_empires.push_back(NULL);
      }

      // assign each commander to an Empire, and give them a city
      for (std::list<Commander*>::iterator j = _cmdrs.begin();
	   j != _cmdrs.end(); j++,i++) {
	Empire *e = new Empire(this);
	BuildCity(e);
	e->AddCommander(*j);

      }

      // setup CQ msg store, allies, and seen into various vectors
      for (i=0;i!=_empires.size();i++) {
	// cq store
	_cqs.push_back(NULL);

	// allies
	if (_empires[i]) {
	  for (size_t j=0;j!=_empires.size();j++) {
	    _empires[i]->_allies.push_back(false);
	  }

	  if (i) {
	    // send output message
	    std::ostringstream tmp;
	    tmp << "Commander of Empire #" << i << ": "
		<< (*(_empires[i]->_cmdrs.begin()))->GetId();
	    SvrChatMsg ob("",tmp.str());
	    Broadcast(ob);
	    _net.Output();
	    std::cout << tmp.str() << std::endl;
	  }
	}

	// seen
	Coord c = _grid->GetSize();
	for (int x = 0; x != c.GetX(); x++) {
	  for (int y = 0; y != c.GetY(); y++) {
	    GridAble *g = _grid->Get(Coord(x,y));
	    Static *s = dynamic_cast<Static*>(g);
	    assert(s);
	    s->_seen.push_back(false);
	  }
	}  
      }

      // setup the standing orders vector for each terrain
      Coord size = _grid->GetSize();
      std::vector<Order> no;
      for (int x = 0; x < size.GetX(); x++) {
	for (int y = 0; y < size.GetY(); y++) {
	  GridAble *gable = _grid->Get(Coord(x,y));
	  Static *s = dynamic_cast<Static*>(gable);
	  assert(s);
	  for(size_t i = 0;i<_empires.size();i++) {
	    s->_orders.push_back(no);
	  }
	}
      }

      // send the params message
      // make sure to subtract one for the dummy empire
      SvrParamsMsg obp(size.GetX(),size.GetY(),_empires.size()-1,_gamespeed);
      Broadcast(obp);

      // Send the initial allegiance message
      for (size_t i = 0; i < _empires.size(); i++) {
	if (_empires[i]) {
	  SvrEmpireMsg ob(_empires[i]->GetId());
	  _empires[i]->Broadcast(ob);
	}
      }

      _period = GAMEPLAY;
      _phase = BEFORECOMMAND;

      // send MK PD msg to all clients
      SvrMarkMsg ob2(MarkMsg::PD,_period,"");
      Broadcast(ob2);
    }
  } else if (_period == GAMEPLAY) {
    // speed up the game if all commanders disconnected
    if (!_cmdrs.size())
      _gamespeed = 0;    // frobworldify

    // check for dead empires
    int goodemps = 0;
    for (std::vector<Empire*>::iterator i = _empires.begin();
         i < _empires.end() ; i++) {
      if (*i) goodemps++;
    }

    if (goodemps <= 1) {
      if (!goodemps) {
	SvrChatMsg ob("","Somehow all the Empires are dead!");
	Broadcast(ob);
      }
      _period = GAMEFIN;
    } else { // GAME ON!
      UpdatePhase();
    }
  } else if (_period == GAMEFIN) {
    std::vector<int> winners;
    for (size_t i = 0;i < _empires.size(); i++) {
      if (_empires[i]) {
	winners.push_back(i);
      }
    }

    std::ostringstream gameover;
    gameover << "GAME OVER! Turn: " << _current_turn << " Winner";
    if (winners.size() > 1)
      gameover << "s";
    gameover << ":";
    if (!winners.size()) {
      gameover << " Nobody!!!";
    } else {
      for (size_t i=0;i<winners.size();i++) {
	gameover << " Empire #" << winners[i];
      }
    }

    std::cout << gameover.str() << std::endl;

    SvrChatMsg obc("",gameover.str());
    Broadcast(obc);

    SvrMarkMsg ob(MarkMsg::PD,_period,gameover.str());
    Broadcast(ob);

    _period = ONCEFIN;
  } else {
    assert(0);
  }
}

void World::UpdatePhase() {
  if (_phase == BEFORECOMMAND) {
    // if specified on command line, dump grid
    PrintGrid();

    // reset Commanders' grace period flag
    for (std::list<Commander*>::iterator i = _cmdrs.begin() ;
	 i != _cmdrs.end(); i++ ) {
      (*i)->_iscurrent = false;
    }

    // command phase is _gamespeed seconds long
    _blastoff = Countdown(_gamespeed);
    _phase = COMMAND;
    SendTurn();
    SendPhase();
  } else if (_phase == COMMAND) {
    if (_blastoff || !_cmdrs.size()) {
      _blastoff = Countdown(_commandgrace);
      _phase = GRACE;
    }
  } else if (_phase == GRACE) {
    // check for cmdrs who haven't sent MK TN
    std::list<Commander*> badcmdrs;
    for (std::list<Commander*>::iterator i = _cmdrs.begin();
         i != _cmdrs.end() ; i++) {
      if (!((*i)->CheckCurrent()))
	badcmdrs.push_back(*i);
    }

    bool nextphase = false;
    if (badcmdrs.size()) { // still have commanders left to send MK TN
      if (_blastoff) { // kill them all!!!
	for(std::list<Commander*>::iterator i = badcmdrs.begin();
         i != badcmdrs.end() ; ) {
	  std::list<Commander*>::iterator j(i);
	  i++;
	  delete (*j);
	}
	nextphase = true;
      }
    } else { // we can proceed
      nextphase = true;
    }
    
    if (nextphase) {
      _phase = DIPLOMACY;
      SendPhase();
    }

  } else if (_phase == DIPLOMACY) {
    // do diplomacy stuff
    for (size_t i=0;i!=_cqs.size();i++) {
      if (_cqs[i]) {
	if (_empires[i]) {
	  _empires[i]->RequestAlly(_cqs[i]->GetToFrom(),_cqs[i]->GetPeace());
	  if (_empires[_cqs[i]->GetToFrom()]) {
	    SvrCqMsg ob(i,_cqs[i]->GetPeace(),_cqs[i]->GetText());
	    _empires[_cqs[i]->GetToFrom()]->Broadcast(ob);
	  }
	}
	delete _cqs[i];
	_cqs[i] = NULL;
      }
    }

    //send ally msgs
    for (size_t i=0;i!=_empires.size();i++) {
      std::vector<int> tmp;
      Empire *me = _empires[i];
      if (!me) continue;  // if this empire dead, ignore it

      // push each allied empire number into the vector
      for (size_t j=0;j!=_empires.size();j++) {
	if (j == i) continue; //ignore braindamaged own alliance
	if (!_empires[j]) continue; // don't segfault
	if (_empires[i]->IsAllyOf(_empires[j]))
	  tmp.push_back(static_cast<int>(j));
      }
      SvrAlliesMsg ob(tmp);
      me->Broadcast(ob);
    }

    // go to next phase
    _phase = UPDATE;
    SendPhase();
  } else if (_phase == UPDATE) {
    // do update stuff
    ShuffleActives();
    for (size_t i = 1; i < _up_actives.size(); i++) {
      if (_up_actives[i]) {
	_up_actives[i]->Update();
      }

    }
    _up_actives.clear();

    for (size_t i = 0; i!= _empires.size(); i++) {
      if (_empires[i])
	_empires[i]->SendContactsMsg();
    }

    // go to next phase
    _phase = OUTCOME;
    SendPhase();
  } else if (_phase == OUTCOME) {
    // Check for empires that should die
    for (size_t i = 0; i < _empires.size(); i++) {
      if (_empires[i] && !_empires[i]->CheckAlive()) {
	std::ostringstream buf;
	buf << "Empire #" << i << " has fallen!";
	SvrChatMsg ob("",buf.str());
	Broadcast(ob);
	delete _empires[i];
      }
    }

    // go to next turn
    _phase = BEFORECOMMAND;
    // end the game if we get to maxturns
    if (_current_turn == _maxturns) {
      _period = GAMEFIN;
    } else {
      _current_turn++; // increment the turn counter
    }
  } else {
    assert(0);
  }
}

void World::SendPhase() {
  SvrMarkMsg ob(MarkMsg::PH,_phase,"");
  Broadcast(ob);
}

void World::SendTurn() {
  SvrMarkMsg ob(MarkMsg::TN,_current_turn,"");
  Broadcast(ob);
}

void World::StoreCq(SvrCqMsg *m, size_t e) {
  if (e > _empires.size()-1)
    throw EXCEPTION("Invalid empire number in communique");

  if (_cqs[e])
    delete _cqs[e];

  _cqs[e] = m;
}

void World::AddActive(Active* a)
{
  _actives.push_back(a);
}

void World::RemoveActive(Active* a)
{
  std::list<Active*>::iterator i = find(_actives.begin(),_actives.end(),a);
  assert (i!=_actives.end());
  _actives.erase(i);
  if (_up_actives.size() && a->_w_loc) {
    _up_actives[a->_w_loc] = NULL;
  }
}

void World::ShuffleActives() {
  // need a special case to handle newly created objects, as they might
  // get attacked - let that be _up_actives[0]
  _up_actives.resize(_actives.size()+1);
  _up_actives[0] = NULL;

  size_t j = 0;
  for (std::list<Active*>::iterator i = _actives.begin(); i!=_actives.end(); i++) {
    _up_actives[j+1] = *i;
    j++;
  }
  // randomly swap all actives into a new vector
  for(j=1;j<_up_actives.size();j++) {
    size_t r = 1 + (random() % _actives.size());
    Active *t = _up_actives[j];
    _up_actives[j] = _up_actives[r];
    _up_actives[r] = t;
    _up_actives[j]->_w_loc = j;
    _up_actives[r]->_w_loc = r;
  }
}

// specify with -g on the command line, dumps entire grid
void World::PrintGrid() {
  if (!_printgrid)  {
    std::cout << "\rTurn: " << _current_turn << '\r' << std::flush;
    return;
  }
  system("clear");
  Coord c(_grid->GetSize());
  for (int y = 0; y<c.GetY();y++) {
    for (int x = 0;x<c.GetX();x++) {
      GridAble *g = _grid->Get(Coord(x,y));
      if (!g) {
	std::cout << ' ';
      } else {
	Static *s = dynamic_cast<Static*>(g);
	assert(s);
	Active *a = s->GetVisible();
	if (!a)
	  std::cout << s->GridTestChar();
	else 
	  std::cout << a->GridTestChar();
      }
    }
    std::cout << '\n';
  }
}

// if a commander's empire is destroyed and he has allies, then assign him to an ally
void World::ReassignCommander(Commander *c, Empire *old) {
  std::vector<Empire*> allies;
  for (size_t i = 0; i < _empires.size(); i++) {
    if (_empires[i] && _empires[i] != old && old->IsAllyOf(_empires[i])) {
      allies.push_back(_empires[i]);
    }
  }
  if (allies.size()) {
    size_t r;
    if (allies.size()==1) r = 0;
    else r = random() % allies.size(); // if multiple allies then pick one randomly
    Empire *newemp = allies[r];
    newemp->AddCommander(c);
    SvrEmpireMsg ob(newemp->GetId());
    c->Notify(ob);

    SvrChatMsg ob2("",c->GetId() + " joined this Empire");
    newemp->Broadcast(ob2);

    // send down seen terrain
    Coord size = _grid->GetSize();
    std::vector<ContactsMsg::Contact> con;
    std::vector<ContactsMsg::Terrain> ter;
    std::vector<ContactsMsg::Active> act;
    for (int x = 0; x < size.GetX(); x++) {
      for (int y = 0; y < size.GetY(); y++) {
	GridAble *gable = _grid->Get(Coord(x,y));
	Static *s = dynamic_cast<Static*>(gable);
	assert(s);
	if (s->_seen[newemp->GetId()]) {
	  bool unused;
	  ter.push_back(s->GetTerrain(newemp,unused));
	}
      }
    }
    SvrContactsMsg ob3(con,ter,act);
    c->Notify(ob3);
  } else {
    c->_empire = NULL;
    delete c; // kill it
  }
}

void World::Tell(Empire *e, Coord c, std::vector<Order> o) {
  GridAble *g = _grid->Get(c);
  Static *s = dynamic_cast<Static*>(g);
  assert(s);
  s->_orders[e->GetId()] = o;
}
