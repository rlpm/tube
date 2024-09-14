// Stonecutters CS351 S03 -*- C++ -*-
// $Id: Cview.h,v 1.11 2003/05/14 21:52:10 rlpm Exp $
#ifndef CVIEW_H
#define CVIEW_H
#include <string>
#include <vector>
#include "Coord.h"
#include <list>
#include <map>
#include "ContactsMsg.h"

class Curse;
class Grid;
class Control;

class Cview{
public:
  Cview(Control*);
  ~Cview();
  void Resize(bool=false);  //bool is used to force a resize no matter what!
  void SetGrid(Grid*);
  void Run();

  void DrawGrid();
  void DrawMessages();
  void DrawInput();
  void DrawDisplay();
  void PrintServerMsg(string);
  void CenterOn(Coord);
  void SetTurn(int i) { _turn = i; };
  void SetEmpire(int i) { _emp = i; };
  void SetEmpires(int i) { _empires = i; };

private:
  void Focus();
  void GridWindowSize();
  void GetStartupInput();
  bool IsActive();    //checks to see if screen is active
  void Chat();
  void Communique();
  void MakeOrder(Order::CmdType);
  void CancelOrder();
  string MapUnitToName(Order::UnitType);
  void OrderMore();
  void OrderWait();
  void StandingOrder();
  void PrintHelp();
  int GetText();
  void Backspace();
  void ClearInput();
  void PrintInputLabel(string, int, int);
  void GetInfo(vector<string>&);
  Coord GetCenter();
  void ResetInput(bool);
  void SetStandingOrderLabel();
  void MakeStandingOrder(Order::CmdType);

  Control * _control;

  Curse *  _screen;
  size_t _screen_width;
  size_t _screen_height;

  Grid* _grid;
  size_t _grid_width;
  size_t _grid_height;
  Coord _grid_topleft;

  size_t _curs_x;
  size_t _curs_y;

  size_t _bspc_min_x;
  size_t _bspc_min_y;

  list<string> _messages;

  size_t _message_height;
  size_t _display_width;

  string _label;
  string _output;
  string _output1;
  string _output2;
  bool _focus;

  unsigned char _fog;

  pair<int,Order> *_orderee;

  int _turn;
  int _empires;
  int _emp;

  // standing orders
  Coord _stdwhere;
  vector<Order> _stdorders;
  Order::UnitType _stdu;
  Order::CmdType _stdw;
  Coord _stdloc;
  
  enum InputState { NAME, WAIT, CHAT, COMMUNIQUE, ORDERWAIT,
		    STDORDER, ESCAPE, INPUT};
  enum OtherState { START, FIRST, SECOND, THIRD, FOURTH };
  InputState _input_state;
  OtherState _other_state;

  static const size_t _message_height_min = 15;
  static const size_t _display_width_min = 15;
};

#endif
