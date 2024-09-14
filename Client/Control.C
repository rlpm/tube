// Stonecutters CS351 S03 -*- C++ -*-
// $Id: Control.C,v 1.27 2003/05/14 23:17:59 rlpm Exp $

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include "Control.h"
#include "Grid.h"
#include "GridAble.h"
#include "Coord.h"
#include "Terrain.h"
#include "Curse.h"
#include <string>
#include "Cview.h"
#include "CliConn.h"
#include "CliHelloMsg.h"
#include "CliChatMsg.h"
#include "CliMarkMsg.h"
#include "CliDoMsg.h"
#include "CliTellMsg.h"
#include "CliCqMsg.h"
#include "ContactsMsg.h"
#include "Exception.h"

Control::Control(string server, int port):_grid(0), _hellod(false),
					  _dead(false), _godmode(false)
{
  string username;
  try {
    _sock = new CliConn(this,server, port);
  } catch (...) {
    cerr << "Could not connect to " << server << " " << port << endl;
    exit(1);
  }
  _display = new Cview(this);
  _display->PrintServerMsg("Welcome to Stonecutters TUBE Client v0.1!");
}

Control::~Control(){
  delete _display;
  if(_grid) delete _grid;
  if(_sock) delete _sock;
  if (_period != 2) {
    string extra("Server closed connection");
    if (_donemsg.size())
      _donemsg = extra + ": " + _donemsg;
    else
      _donemsg = extra;
  }
  cout << _donemsg << endl;
}

bool Control::Run(){
  while(_sock && !_dead){
    _display->Run();
    _sock->Run();
  }
  return 1;
}

void Control::GotHello(string input){
  _hellod = true;
  _display->PrintServerMsg(string("Handshake completed to server: ") + input);
  _display->PrintServerMsg("Press <enter> to send a chat message, h for help");
}

void Control::SendChat(string to, string message){
  CliChatMsg msg(to, message);
  _sock->Notify(msg);
}

void Control::SetPeriod(int period, string text){
  if(period == 0){
    _period = INITIAL;
  }
  if(period == 1){
    _period = PLAY;
  }
  if(period == 2){
    _period = FINAL;
  }
  if (text.size())
    _display->PrintServerMsg(string("Period message from server: ") + text);
}

void Control::SetPhase(int phase, string text){
  if(phase == 0){
    _phase = COMMAND;
  }
  if(phase == 1){
    _phase = DIPLOMACY;
  }
  if(phase == 2){
    _phase = UPDATE;
  }
  if(phase == 3){
    _phase = OUTCOME;
  }
  if (text.size())
    _display->PrintServerMsg(string("Phase message from server: ") + text);
}

void Control::SetTurn(int turn, string text){
  _turn = turn;
  if (text.size())
    _display->PrintServerMsg(string("Turn message from server: ") + text);
  string gm;
  if (_godmode) {
    gm = "god mode";
    _godmode = false;
  }
  CliMarkMsg ob(MarkMsg::TN,turn,gm);
  _sock->Notify(ob);
  _display->SetTurn(turn);
}

void Control::SetGridSize(int width, int height){
  if(!_grid){
    _grid = new Grid(Coord(width,height));
    _display->SetGrid(_grid);
  }
}

void Control::SetEmpires(int empire){
  _empires = empire;
  _display->SetEmpires(_empires);
}

void Control::SetSpeed(int speed){
  _speed = speed;
}

void Control::SetAllies(vector<int> allies) {
  if (_allies != allies) {
    _allies = allies;
    ostringstream buf;
    if (!_allies.size()) {
      buf << "You now have no allies!";
    } else {
      buf << "You are now allied with Empire";
      if (_allies.size() > 1)
	buf << 's';
      buf << ':';
      for(size_t i=0;i<_allies.size();i++)
	buf << ' ' << _allies[i];
    }
    _display->PrintServerMsg(buf.str());
  }
}

void Control::ChatIn(string tf, string text) {
  if (!tf.size())
    tf = "Chat message from server";
  _display->PrintServerMsg(tf + ": " + text);
}

void Control::FailMsg(string in) {
  _donemsg = in;
  _dead = true;
}

void Control::SendHello(string name) {
  CliHelloMsg ob(HelloMsg::CurrentVersion(),HelloMsg::HM,name,"");
  _sock->Notify(ob);
}

void Control::PlaceObjects(vector<ContactsMsg::Contact> contacts,
			   vector<ContactsMsg::Terrain> terrains,
			   vector<ContactsMsg::Active> actives) {
  // keep track of old cities just in case they get taken over
  list<Coord> oldcities;

  for (size_t i = 0; i < _mobiles.size(); i++) {
    GridAble *g = _grid->Get(_mobiles[i]);
    Terrain *t = dynamic_cast<Terrain*>(g);
    assert(t);
    if (t->_c.size() && (*(t->_c.begin())).GetType() != Order::CT) {
      t->_c.clear();
    }
    if (t->_a.size()) {
      if ((*(t->_a.begin())).GetOrder().GetUnit() == Order::CT) {
	oldcities.push_back((*(t->_a.begin())).GetCoord());
      }
      t->_a.clear();
    }
  }
  _mobiles.resize(0);

  for (vector<ContactsMsg::Contact>::iterator i = contacts.begin();
       i != contacts.end(); i++) {
    GridAble *g = _grid->Get((*i).GetCoord());
    Terrain *t;
    if (g) {
      t = dynamic_cast<Terrain*>(g);
      assert(t);

      // get rid of other enemy units, since, like Highlander, there can be only one!!!
      t->_c.clear();
      t->_c.push_back(*i);

      // make sure to remove it from oldcities list
      Coord c = (*(t->_c.begin())).GetCoord();
      list<Coord>::iterator j=find(oldcities.begin(),oldcities.end(),c);
      if (j != oldcities.end()) {
	oldcities.erase(j);
      }

    } else {
      t = new Terrain(this,*i);
      _grid->Put(t,(*i).GetCoord());
    }
    _mobiles.push_back((*i).GetCoord());
  }

  for (vector<ContactsMsg::Terrain>::iterator i = terrains.begin();
       i != terrains.end(); i++) {
    GridAble *g = _grid->Get((*i).GetCoord());
    Terrain *t;
    if (g) {
      t = dynamic_cast<Terrain*>(g);
      assert(t);
      if (t->_t.GetType() != (*i).GetType())
	throw EXCEPTION("Got different terrain than what was already sent!!!");
    } else {
      t = new Terrain(this,*i);
      _grid->Put(t,(*i).GetCoord());
    }
  }

  // so we can jump to the first active guy
  if (actives.size()) _first_active = (*(actives.begin())).GetCoord();

  for (vector<ContactsMsg::Active>::iterator i = actives.begin();
       i != actives.end(); i++) {
    GridAble *g = _grid->Get((*i).GetCoord());
    Terrain *t;
    if (g) {
      t = dynamic_cast<Terrain*>(g);
      assert(t);

      // clear any enemy in that spot (overtaken city)
      if (t->_c.size())
	t->_c.clear();

      // make sure we display boats, not armies
      if ((*i).GetOrder().GetUnit() == Order::AR) {
	t->_a.push_back(*i);
      } else {
	t->_a.push_front(*i);
      }

      // make sure to remove our cities from oldcities list
      Coord c = (*(t->_a.begin())).GetCoord();
      list<Coord>::iterator j=find(oldcities.begin(),oldcities.end(),c);
      if (j != oldcities.end()) {
	oldcities.erase(j);
      }
    } else {
      t = new Terrain(this,*i);
      _grid->Put(t,(*i).GetCoord());
    }
    _mobiles.push_back((*i).GetCoord());
  }

  if (_turn <= 1 && actives.size()) {
    Coord c(actives[0].GetCoord());
    _display->CenterOn(c);
  }

  for(list<Coord>::iterator i=oldcities.begin();i!=oldcities.end();i++) {
    GridAble *g = _grid->Get(*i);
    assert(g);
    Terrain *t = dynamic_cast<Terrain*>(g);
    assert(t);
    t->_c.push_back(ContactsMsg::Contact(*i,Order::CT,_empires+1));
  }

  _display->DrawGrid();
}

void Control::SendOrder(int i, Order o) {
  CliDoMsg ob(i,o);
  _sock->Notify(ob);
}

void Control::SendCq(int e, int p, string m) {
  CliCqMsg ob(e,p,m);
  _sock->Notify(ob);
}

void Control::HandleEmpireMsg(int i) {
  ostringstream buf;
  buf << "You now command Empire #" << i;
  _display->PrintServerMsg(buf.str());
  _display->SetEmpire(i);
}

void Control::HandleCqText(string s) {
  _display->PrintServerMsg(s);
}

bool Control::IsAlly(int e) {
  for (size_t i = 0; i!=_allies.size(); i++) {
    if (_allies[i] == e)
      return true;
  }
  return false;
}

void Control::SendStandingOrders(Coord &c, vector<Order>&o) {
  CliTellMsg ob(c,o);
  _sock->Notify(ob);
}
