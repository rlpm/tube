// Stonecutters CS351 S03 -*- C++ -*-

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
  Control(std::string, int);
  ~Control();

  bool Run();

  void RemoveConn() {_sock = NULL;};
  void GotHello(std::string);
  void FailMsg(std::string);
  void ChatIn(std::string,std::string);
  void SendChat(std::string, std::string);
  void SetPeriod(int, std::string);
  void SetPhase(int, std::string);
  void SetTurn(int, std::string);
  void SetGridSize(int, int);
  void SetEmpires(int);
  void SetSpeed(int);
  void SetAllies(std::vector<int>);
  void SendHello(std::string);
  bool CheckHello() { return _hellod; };
  void PlaceObjects(std::vector<ContactsMsg::Contact>,
		    std::vector<ContactsMsg::Terrain>,
		    std::vector<ContactsMsg::Active>);
  void SendOrder(int,Order);
  void SendCq(int,int,std::string);
  void GodMode() { _godmode = true; };
  Coord FirstActive() { return _first_active; };
  void HandleEmpireMsg(int);
  void HandleCqText(std::string);
  bool IsAlly(int);
  void SendStandingOrders(Coord&,std::vector<Order>&);

private:
  Grid* _grid;
  Cview* _display;
  CliConn* _sock;
  int _turn;
  int _speed;
  int _empires;
  std::vector<int> _allies;
  std::vector<Coord> _mobiles;
  Coord _first_active;
  bool _hellod;
  bool _dead;
  std::string _donemsg;

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
