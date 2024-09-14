// Stonecutters CS351 S03 -*- C++ -*-
// $Id: Control.h,v 1.20 2003/05/13 22:54:59 rlpm Exp $

#ifndef CONTROL_H
#define CONTROL_H
#include <vector>
#include <string>
#include "Coord.h"
#include "Model.h"
#include "ContactsMsg.h"
#include "Order.h"

class Grid;
class GridAble;
class Active;
class Contact;
class CliConn;
class Cview;

class Control : public Model {
public:
  Control(string, int);
  ~Control();

  bool Run();

  void RemoveConn() {_sock = NULL;};
  void GotHello(string);
  void FailMsg(string);
  void ChatIn(string,string);
  void SendChat(string, string);
  void SetPeriod(int, string);
  void SetPhase(int, string);
  void SetTurn(int, string);
  void SetGridSize(int, int);
  void SetEmpires(int);
  void SetSpeed(int);
  void SetAllies(vector<int>);
  void SendHello(string);
  bool CheckHello() { return _hellod; };
  void PlaceObjects(vector<ContactsMsg::Contact>,
		    vector<ContactsMsg::Terrain>,
		    vector<ContactsMsg::Active>);
  void SendOrder(int,Order);
  void SendCq(int,int,string);
  void GodMode() { _godmode = true; };
  Coord FirstActive() { return _first_active; };
  void HandleEmpireMsg(int);
  void HandleCqText(string);
  bool IsAlly(int);
  void SendStandingOrders(Coord&,vector<Order>&);

private:
  Grid* _grid;
  Cview* _display;
  CliConn* _sock;
  int _turn;
  int _speed;
  int _empires;
  vector<int> _allies;
  vector<Coord> _mobiles;
  Coord _first_active;
  bool _hellod;
  bool _dead;
  string _donemsg;

  enum Period{
    INITIAL = 0,
    PLAY,
    FINAL
  };

  enum Phase{
    COMMAND =0,
    DIPLOMACY,
    UPDATE,
    OUTCOME
  };
  Period _period;
  Phase _phase;

  bool _godmode;
  
};

#endif
