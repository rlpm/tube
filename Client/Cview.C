// Stonecutters CS351 S03 -*- C++ -*-
#include "Cview.h"
#include <iostream>
#include <string>
#include <sstream>
#include "Grid.h"
#include "Coord.h"
#include "Curse.h"
#include "Terrain.h"
#include "GridAble.h"
#include "Control.h"
#include "FrameParser.h"

Cview::Cview(Control* c):
  _control(c),
  _screen(Curse::Instance()),
  _grid(NULL),
  _grid_width(0),
  _grid_height(0),
  _curs_x(0),
  _curs_y(0),
  _focus(true),
  _fog(32),
  _orderee(NULL),
  _turn(0),
  _empires(0),
  _emp(0),
  _stdu(Order::__UT_END__),
  _input_state(NAME),
  _other_state(START)
{
  _screen->Activate();
  Resize(true);
}

Cview::~Cview(){
  _screen->Terminate();
  if (_orderee) delete _orderee;
}

void Cview::SetGrid(Grid* g){
  _grid=g;

  GridWindowSize();

  _grid_topleft = Coord(0,0);

  Resize(true);
  _screen->Redraw();
}

void Cview::GridWindowSize() {
  //set visible grid width
  if(!_grid) {
    _grid_width = 0;
    _display_width = 0;
  } else {
    if (_screen_width >= _grid->GetSize().GetX()+_display_width_min + 1){
      _grid_width = _grid->GetSize().GetX();
      _display_width = _screen_width - _grid_width - 1;
    } else {
      if(_screen_width < _display_width_min + 1) {
	_display_width = _screen_width;
	_grid_width = 0;
      } else {
	_display_width = _display_width_min;
	_grid_width = _screen_width - _display_width - 1;
      }
    }
  }
  //set visible grid height
  if (!_grid) {
    _message_height = _screen_height - 1;
    _grid_height = 0;
  } else if (_screen_height >= 1 + _message_height_min + _grid->GetSize().GetY()) {
    _grid_height = _grid->GetSize().GetY();
    _message_height = _screen_height - _grid_height - 1;
  } else {
    if(_screen_height < _message_height_min + 1) {
      _message_height = _screen_height - 1;
      _grid_height = 0;
    } else {
      _message_height = _message_height_min;
      _grid_height = _screen_height - _message_height - 1;
    }
  }
}

void Cview::DrawDisplay(){
  if(_screen->IsActive() && _grid) {
    vector<string> stuff;

    // the turn number
    ostringstream turn;
    turn << "Turn: " << _turn;
    stuff.push_back(turn.str());
    turn.seekp(0);
    turn << "Empire: " << _emp;
    stuff.push_back(turn.str());

    // the location on the grid
    ostringstream location;
    Coord loc(GetCenter());
    location << "X:" << loc.GetX() << " Y:" << loc.GetY();
    stuff.push_back(location.str());

    // display the stuff
    _curs_y = 0;
    GetInfo(stuff);
    for (size_t i = 0; i < stuff.size() && _curs_y < _grid_height;i++,_curs_y++) {
      _curs_x = _screen_width - _display_width;
      _screen->GoTo(_curs_x,_curs_y);
      string tmp = stuff[i];
      if (tmp.size() > _display_width) {
	tmp.resize(_display_width - 1);
	tmp += ">";
      }
      _screen->PutString(tmp.c_str());
      _curs_x += tmp.size();
      for(;_curs_x<_screen_width;_curs_x++)
	_screen->PutCharAt(_curs_x, _curs_y, 32);
    }
    for(;_curs_y < _grid_height;_curs_y++)
      for(_curs_x = _screen_width - _display_width;
	  _curs_x<_screen_width;_curs_x++)
	_screen->PutCharAt(_curs_x, _curs_y, 32);
  }
}

void Cview::DrawMessages() {
  if(_screen->IsActive()){
    size_t x = 0;
    size_t y = _grid_height;

    // ignore enough messages at top of list
    list<string>::iterator i = _messages.begin();
    size_t j = 0;
    while(_messages.size()-j>_message_height) {
      i++;
      j++;
    }

    // print the most recent messages
    for(;i!= _messages.end();i++) {
      string op(*i);
      if(op.size()>_screen_width) {
	op.resize(_screen_width-1);
	op += ">";
      }
      _screen->GoTo(x,y);
      _screen->PutString(op.c_str());
      x += op.size();
      for(;x<_screen_width;x++)
	_screen->PutCharAt(x, y, 32);
      x=0;
      y++;
    }

    // erase anything below last message
    for(;y<_screen_height-1;y++) {
      for(x=0;x<_screen_width;x++) {
	_screen->PutCharAt(x, y, 32);
      }
    }
  }
}

void Cview::ResetInput(bool focus) {
  _focus = focus;
  _output.resize(0);
  _output1.resize(0);
  _output2.resize(0);
  _label.resize(0);
  _other_state = START;
}

void Cview::DrawInput() {
  if(_screen->IsActive()){
    _curs_y = _screen_height - 1;
    _curs_x = 0;
    string tmp(_output);

    if (_label.size()) {
      PrintInputLabel(_label.c_str(), _curs_x, _curs_y);
      if (tmp.size() + _label.size() > _screen_width)
	if (_screen_width <= _label.size())
	  tmp.resize(0);
	else
	  tmp.resize(_screen_width - _label.size());
      _screen->PutString(tmp.c_str());
      _curs_x += tmp.size();
    }
    for(size_t x = _curs_x;x < _screen_width; x++){
      _screen->PutCharAt(x, _curs_y, 32);
    }
  }
}

void Cview::Focus() {
  //set cursor location
  if (_focus) {
    _curs_x = _label.size() + _output.size();
    _curs_y = _screen_height - 1;
  } else {
    if (_grid && _grid_width && _grid_height) {
      _curs_x = _grid_width/2;
      _curs_y = _grid_height/2;
    } else {
      _curs_x = _screen_width - 1;
      _curs_y = _screen_height - 1;
    }
  }
  _screen->GoTo(_curs_x, _curs_y);
  _screen->Refresh();
}

void Cview::Resize(bool override){
  if(_screen->IsActive()){
    if(_screen->Resize() || override){
      _screen_width = _screen->GetScreenWidth();
      _screen_height = _screen->GetScreenHeight();

      // recenter on resize
      Coord center;
      if (_grid) {
	center = GetCenter();
      }

      GridWindowSize();

      if (_grid) {
	CenterOn(center);
      }

      // Do the actual drawing
      DrawGrid();
      DrawMessages();
      DrawInput();
    }
  }
}

//Display the grid
void Cview::DrawGrid(){
  if(_grid){
    if(_screen->IsActive()){
      DrawDisplay();
      GridAble* able;
      Terrain* terrain;
      for(size_t y=0;y<_grid_height;y++){
	for(size_t x=0;x<_grid_width;x++){
	  Coord c(_grid_topleft.GetX()+x,_grid_topleft.GetY()+y);
	  able = _grid->Get(c);
	  if(able == NULL){                   
	    _screen->PutCharAt(x,y,_fog);
	  }else{
	    terrain = dynamic_cast<Terrain*>(able);
	    assert(terrain);
	    terrain->Output(_screen,Coord(x,y));
	  }
	}
      }
      size_t x = _grid_width;
      for (size_t y = 0; y<_grid_height;y++)
	_screen->PutCharAt(x,y,32);
    }
  } else {
    for (size_t x = 0; x<_grid_width; x++) {
      for (size_t y = 0; y<_grid_height; y++) {
	_screen->PutCharAt(x, y, 32);
      }
    }
  }
}

void Cview::PrintServerMsg(string in){
  _messages.push_back(in);
  if(_messages.size()>10000) _messages.pop_front();
  DrawMessages();
}

void Cview::Run(){
  unsigned short ch;
  int c;
  ch =0;
  Resize();
  bool again = true;
  while (again) {
    again = false;
    switch (_input_state){
    case NAME:
      GetStartupInput();
      if (_other_state == START)
	_input_state = WAIT;
      break;
    case WAIT:
      if (_control->CheckHello())
	_input_state = INPUT;
      break;
    case CHAT:
      Chat();
      if(_other_state == START)
	_input_state = INPUT;
      break;
    case COMMUNIQUE:
      Communique();
      if(_other_state == START)
	_input_state = INPUT;
      break;
    case ORDERWAIT:
      OrderWait();
      if(_other_state == START)
	_input_state = INPUT;
      break;
    case STDORDER:
      StandingOrder();
      if(_other_state == START)
	_input_state = INPUT;
      break;
    case ESCAPE:  //escape
      c = _screen->ReadChar();
      if(c != -1){
	switch (c){
	case 91:  // [ left bracket
	  c = _screen->ReadChar();
	  if (c != -1 && _grid){
	    switch (c){
	    case 65:  //up
	    case 'w':
	      _grid_topleft.SetY(_grid_topleft.GetY()-1);
	      break;
	    case 66:  //down
	    case 's':
	      _grid_topleft.SetY(_grid_topleft.GetY()+1);
	      break;
	    case 67:  //right
	    case 'd':
	      _grid_topleft.SetX(_grid_topleft.GetX()+1);
	      break;
	    case 68:  //left
	    case 'a':
	      _grid_topleft.SetX(_grid_topleft.GetX()-1);
	      break;
	    default:
	      break;
	    }
	    _input_state = INPUT;
	    if (_grid)
	      _grid->Normalize(_grid_topleft);
	    DrawGrid();
	    break;
	  default:
	    _input_state = INPUT;
	    break;
	  }
	}
      } else {
	CancelOrder();
	_input_state = INPUT;
      }
      break;
    case INPUT:
      c = _screen->ReadChar();
      if(c != -1){
	ch = short(c);
      }else{
	ch =0;
      }
      switch(ch){
      case 'h':
      case 'H':
	PrintHelp();
	DrawMessages();
	break;
      case 10: // enter key
	_input_state = CHAT;
	break;
      case 'q':
      case 'Q':
	_input_state = COMMUNIQUE;
	break;
      case 'x':
      case 'X':
	MakeOrder(Order::XP);
	break;
      case 'm':
      case 'M':
	MakeOrder(Order::MA);
	break;
      case 'f':
      case 'F':
	MakeOrder(Order::DF);
	break;
      case 'w':
      case 'W':
	MakeOrder(Order::WT);
	break;
      case 's':
      case 'S':
	MakeOrder(Order::SL);
	break;
      case 'a':
      case 'A':
	MakeOrder(Order::BA);
	break;
      case 'd':
      case 'D':
	MakeOrder(Order::BD);
	break;
      case 'r':
      case 'R':
	MakeOrder(Order::BC);
	break;
      case 'e':
      case 'E':
	MakeOrder(Order::BE);
	break;
      case 'g':
      case 'G':
	MakeOrder(Order::GR);
	break;
      case 't':
      case 'T':
	_input_state = STDORDER;
	break;
      case 'j':
      case 'J':
	CenterOn(_control->FirstActive());
	DrawGrid();
	break;
      case ' ':
	OrderMore();
	break;
      case 12: // ^L redraw screen
	Resize(true);
	break;
      case 7: // ^G GOD MODE!!!
	_control->GodMode();
	break;
      case 27:
	_input_state = ESCAPE;
	again = true;
	break;
      default:
	_input_state = INPUT;
      }
      break;
    }
  }
  Focus();
  return;
}

int Cview::GetText(){     //currently only used for chat
  int c;
  int ret = 0;
  unsigned short ch;
  c = _screen->ReadChar();
  if(c == -1) return 0;
  ch = c;
  switch (ch){
  case 10:         //return
    ret = 1;
    break;
  case 27:        //escape
    c = _screen->ReadChar();
    while(c!=-1) c = _screen->ReadChar(); //get rid of any extra stuff
    ret = -1;
    break;
  case 127:        //backspace
    Backspace();
    break;
  case 12: // ^L
    Resize(true);
    break;
  default:        //add text to string
    if (isprint(ch)) {
      _output += char(ch);
      if (_curs_x == _screen_width - 1) {
	_screen->PutCharAt(_curs_x, _curs_y, '>');
      } else {
	_screen->PutCharAt(_curs_x, _curs_y, ch);
	_curs_x++;
      }
    }
    break;
  }
  return ret;
}


void Cview::PrintInputLabel(string text, int x, int y){ 
  _bspc_min_x = text.length() + x;
  _bspc_min_y = y;
  _curs_x = x;
  _curs_y = y;
  _screen->GoTo(_curs_x, _curs_y);
  _screen->PutString(text.c_str());
  _curs_x = text.length()+x;
  _screen->GoTo(_curs_x, _curs_y);
}

void Cview::Chat(){
  int ch;
  switch(_other_state){
  case START:
    ResetInput(true);
    _label = "To: ";
    _other_state = FIRST;
    break;
  case FIRST:
    ch = GetText();
    if(ch == 1){
      _output1 = _output;
      _output.resize(0);
      _label = "Message: ";
      _other_state = SECOND;
    }else if (ch == -1){
      ResetInput(false);
    }
    break;
  case SECOND:
    ch = GetText();
    if(ch != 0){
      if(ch == 1){
	_control->SendChat(_output1, _output);
      }
      ResetInput(false);
    }
    break;
  case THIRD:
    assert(0);
    break;
  case FOURTH:
    assert(0);
    break;
  }
  DrawInput();
  return;
}

void Cview::PrintHelp(){
  _messages.push_back("Use the Arrow keys to move around the map.");
  _messages.push_back("Hotkeys: <Enter>Chat [H]elp communi[Q]ue [J]ump e[X]plore");
  _messages.push_back("[M]arch de[F]end [W]ait [S]ail bld[A]rmy bld[D]estroyer");
  _messages.push_back("bldc[R]uiser bld[E]mperor [G]row s[T]andingorder");
}

void Cview::GetStartupInput(){
  int c;
  switch (_other_state) {
  case START:
    ResetInput(true);
    _label = "Enter Username: ";
    _other_state = FIRST;
    break;
  case FIRST:
    c = GetText();
    if(c == 1){
      _control->SendHello(_output);
      ResetInput(false);
    }
    break;
  case SECOND:
    assert(0);
    break;
  case THIRD:
    assert(0);
    break;
  case FOURTH:
    assert(0);
    break;
  }
  DrawInput();
}

void Cview::Communique(){
  if (!_grid) return;
  int c;
  switch (_other_state) {
  case START:
    ResetInput(true);
    _label = "Empire #: ";
    _other_state = FIRST;
    break;
  case FIRST:
    c = GetText();
    if (c == -1) {
      ResetInput(false);
    } else if (c == 1){
      istringstream buf(_output);
      try {
	FrameParser::GrabInt(buf);
      } catch (...) {
	PrintServerMsg("Invalid Integer");
	_output.resize(0);
	break;
      }
      _output1 = _output;
      _output.resize(0);
      _label = "Peace: ";
      _other_state = SECOND;
      break;
    }
    break;
  case SECOND:
    c = GetText();
    if (c == -1) {
      ResetInput(false);
    } else if(c == 1) {
      istringstream buf(_output);
      try {
	FrameParser::GrabInt(buf);
      } catch (...) {
	PrintServerMsg("Invalid Integer");
	_output.resize(0);
	break;
      }
      _output2 = _output;
      _output.resize(0);
      _label = "Message: ";
      _other_state = THIRD;
      break;
    }
    break;
  case THIRD:
    c = GetText();
    if (c != 0) {
      if(c == 1){
	istringstream buf(_output1);
	int e = FrameParser::GrabInt(buf);
	istringstream buf2(_output2);
	int p = FrameParser::GrabInt(buf2);
	_control->SendCq(e,p,_output);
      }
      ResetInput(false);
    }
    break;
  case FOURTH:
    assert(0);
    break;
  }
  DrawInput();
}

void Cview::Backspace(){
  if(_curs_x <= _bspc_min_x && _curs_y > _bspc_min_y){  //check for beginning of input area
    if(_curs_x!= 0){  //not on original text label line go to 0
      _curs_x--;
      _screen->PutCharAt(_curs_x,_curs_y,32);
      _output.erase(_output.size()-1, 1);
      _screen->GoTo(_curs_x,_curs_y);
    }else{
      _curs_x= _screen_width;
      _curs_y--;
      _screen->GoTo(_curs_x, _curs_y);
    }
  }else if(_curs_x == _bspc_min_x && _curs_y == _bspc_min_y){  //check for beginning of input
    //    _curs_x=_curs_x;
    //_screen->GoTo(_curs_x,_curs_y);
  }else{
    _curs_x--;
    _screen->PutCharAt(_curs_x,_curs_y,32);
    _output.erase(_output.size()-1, 1);
    _screen->GoTo(_curs_x,_curs_y);
  }
}

string Cview::MapUnitToName(Order::UnitType t) {
  switch (t) {
  case Order::CT: return "City";
  case Order::AR: return "Army";
  case Order::DE: return "Destroyer";
  case Order::CR: return "Cruiser";
  case Order::EM: return "Emperor";
  default: return "UNKNOWN!!!";
  }
}

void Cview::GetInfo(vector<string>&ret) {
  Coord c(GetCenter());
  GridAble *g = _grid->Get(c);
  if (!g) return;
  Terrain *t = dynamic_cast<Terrain*>(g);
  assert(t);
  ostringstream buf;
  if (t->_a.size()) {
    if (t->_a.size()>1) {
      buf << "Total: " << t->_a.size();
      ret.push_back(buf.str());
      buf.seekp(0);
    }  
    for (list<ContactsMsg::Active>::iterator i = t->_a.begin();
	 i != t->_a.end();
	 i++) {
      Order o = (*i).GetOrder();
      buf << MapUnitToName(o.GetUnit());
      buf << ' ' << (*i).GetId();
      ret.push_back(buf.str());
      buf.seekp(0);
      buf << "Hits: " << (*i).GetHits();
      ret.push_back(buf.str());
      buf.seekp(0);
      buf << "Order: ";
      switch (o.GetCmd()) {
#define XX(a) case Order::a: buf << #a; break;
#include "CommandTypes"
#undef XX
      default: buf << "??"; break;
      }
      ret.push_back(buf.str());
      buf.seekp(0);
      if (Order::NeedsCoord(o.GetCmd())) {
	buf << "Dest: " << o.GetCoord();
	ret.push_back(buf.str());
	buf.seekp(0);
      }

      if (o.GetUnit()!=Order::AR) {
	if (o.GetUnit()==Order::CT) {
	  buf << "Work: ";
	} else {
	  buf << "Wait: ";
	}
	buf << o.GetCt();
	ret.push_back(buf.str());
	buf.seekp(0);
      }
    }
  } else if (t->_c.size()) {
    ostringstream buf;
    int e = (*(t->_c.begin())).GetEmp();
    buf << MapUnitToName((*(t->_c.begin())).GetType());
    ret.push_back(buf.str());
    buf.seekp(0);
    buf << "Empire: ";
    if (e > _empires) buf << '?';
    else buf << e;
    ret.push_back(buf.str());
    if (_control->IsAlly(e)) {
      ret.push_back("Ally");
    }
  }
}

void Cview::CenterOn(Coord c) {
  if (!_grid) return;
  _grid_topleft = Coord(c.GetX() - (_grid_width / 2),
			c.GetY() - (_grid_height / 2));
  _grid->Normalize(_grid_topleft);
}

Coord Cview::GetCenter() {
  Coord c(_grid_topleft.GetX() + (_grid_width / 2),
	  _grid_topleft.GetY() + (_grid_height / 2));
  _grid->Normalize(c);
  return c;
}

void Cview::CancelOrder() {
  if (_orderee) {
    ostringstream buf;
    buf << "Order aborted for "
	<< MapUnitToName(_orderee->second.GetUnit())
	<< ' ' << _orderee->first;
    PrintServerMsg(buf.str());
    delete _orderee;
    _orderee = NULL;
    ResetInput(false);
    DrawInput();
  }
}

void Cview::MakeOrder(Order::CmdType w) {
  if (!_grid) return;

  Coord where(GetCenter());
  GridAble *gable = _grid->Get(Coord(where));
  if (!gable) {
    ostringstream buf;
    buf << "The fog of war prevents you from issuing an order @ " << where;
    PrintServerMsg(buf.str());
  } else {
    Terrain *t = dynamic_cast<Terrain*>(gable);
    assert (t);
    if (!t->_a.size()) {
      ostringstream buf;
      buf << "You do not command a unit @ " << where;
      PrintServerMsg(buf.str());
    } else {

      // must iterate through all units in this spot to see if order is
      // valid
      ContactsMsg::Active *valid = NULL;
      for (list<ContactsMsg::Active>::iterator i = t->_a.begin();
	   i != t->_a.end();
	   i++) {
	if (Order::ValidCommand((*i).GetOrder().GetUnit(),w)) {
	  valid = &(*i);
	  break;
	}
      }
      if (!valid) {
	ostringstream buf;
	buf << "Invalid command for any units at that location";
	PrintServerMsg(buf.str());
      } else if (!Order::NeedsCoord(w) && 
		 !Order::NeedsWait(valid->GetOrder().GetUnit())) {
	_control->SendOrder(valid->GetId(),
			    Order(valid->GetOrder().GetUnit(),
				  w,Coord(0,0),0));
      } else {
	if (_orderee) delete _orderee;
	_orderee = new pair<int,Order>(valid->GetId(),
				       Order(valid->GetOrder().GetUnit(),
					     w,Coord(0,0),0));
	if (Order::NeedsCoord(w)) {
	  ResetInput(false);
	  _label = "Order needs a to location - go there and press spacebar";
	  DrawInput();
	} else {
	  _input_state = ORDERWAIT;
	  _other_state = START;
	}
      }
    }
  }
}

void Cview::SetStandingOrderLabel() {
  _focus = false; // default to no cursor in input unless we need it

  if (_other_state == START) {
    _label.resize(0);
    return;
  }

  ostringstream buf;
  buf << "Standing Orders (" << _stdorders.size() << "): ";
  if (_other_state > FIRST) {
    buf << MapUnitToName(_stdu) << ' ';
  }
  if (_other_state > SECOND) {
    switch (_stdw) {
#define XX(a) case Order::a: buf << #a << ' '; break;
#include "CommandTypes"
#undef XX
    default: buf << "?? "; break;
    }
  }
  if (_other_state == THIRD) {
    buf << "?Coord?";
  }
  if (_other_state > THIRD && Order::NeedsCoord(_stdw)) {
    buf << _stdloc << ' ';
  }
  if (_other_state == FOURTH) {
    buf << "Wait: ";
    _focus = true;
  }
  _label = buf.str();
}

void Cview::StandingOrder() {
  if (!_grid) return;
  int ch;
  switch(_other_state){
  case START:
    ResetInput(false);
    _stdorders.clear();
    _stdu = Order::__UT_END__;
    _stdwhere = GetCenter();
    _other_state = FIRST;
    break;
  case FIRST:
    _stdu = Order::__UT_END__;
    _focus = false;
    ch = _screen->ReadChar();
    switch (ch) {
    case 27: // escape
      ch = _screen->ReadChar();
      if (ch == -1) {
	ResetInput(false);
	_stdorders.clear();
	_other_state = START;
      } else {
	// ignore other escapes
	while(_screen->ReadChar()!=-1); // get rid of escaped chars
      }
      break;
    case 10: // enter
      ResetInput(false);
      _control->SendStandingOrders(_stdwhere,_stdorders);
      _stdorders.clear();
      break;
    case 'a':
    case 'A':
      _stdu = Order::AR;
      break;
    case 'c':
    case 'C':
      _stdu = Order::CT;
      break;
    case 'd':
    case 'D':
      _stdu = Order::DE;
      break;
    case 'r':
    case 'R':
      _stdu = Order::CR;
      break;
    case 'e':
    case 'E':
      _stdu = Order::EM;
      break;
    }
    if (_other_state != START && _stdu != Order::__UT_END__) {
      _other_state = SECOND;
    }
    break;
  case SECOND:
    ch = _screen->ReadChar();
    switch (ch) {
    case 27: // escape
      ch = _screen->ReadChar();
      if (ch == -1) {
	_other_state = FIRST;
      } else {
	// ignore other escapes
	while(_screen->ReadChar()!=-1); // get rid of escaped chars
      }
      break;
    case 'x':
    case 'X':
      MakeStandingOrder(Order::XP);
      break;
    case 'm':
    case 'M':
      MakeStandingOrder(Order::MA);
      break;
    case 'f':
    case 'F':
      MakeStandingOrder(Order::DF);
      break;
    case 'w':
    case 'W':
      MakeStandingOrder(Order::WT);
      break;
    case 's':
    case 'S':
      MakeStandingOrder(Order::SL);
      break;
    case 'a':
    case 'A':
      MakeStandingOrder(Order::BA);
      break;
    case 'd':
    case 'D':
      MakeStandingOrder(Order::BD);
      break;
    case 'r':
    case 'R':
      MakeStandingOrder(Order::BC);
      break;
    case 'e':
    case 'E':
      MakeStandingOrder(Order::BE);
      break;
    case 'g':
    case 'G':
      MakeStandingOrder(Order::GR);
      break;
    }
    break;
  case THIRD:
    ch = _screen->ReadChar();
    switch (ch) {
    case 27:
      ch = _screen->ReadChar();
      if (ch == -1) {
	// escape
	_other_state = SECOND;
	break;
      } else if ( ch != 91 ) { // 91 = '['
	// ignore other escape sequences
	while (_screen->ReadChar() != -1);
	break;
      }
      ch = _screen->ReadChar();
      switch (ch){
      case 65:  //up
      case 'w':
	_grid_topleft.SetY(_grid_topleft.GetY()-1);
	break;
      case 66:  //down
      case 's':
	_grid_topleft.SetY(_grid_topleft.GetY()+1);
	break;
      case 67:  //right
      case 'd':
	_grid_topleft.SetX(_grid_topleft.GetX()+1);
	break;
      case 68:  //left
      case 'a':
	_grid_topleft.SetX(_grid_topleft.GetX()-1);
	break;
      default:
	break;
      }
      _grid->Normalize(_grid_topleft);
      DrawGrid();
      break;
    case ' ':
      if (!Order::NeedsWait(_stdu)) {
	_stdorders.push_back(Order(_stdu,_stdw,GetCenter(),0));
	_other_state = FIRST;
      } else {
	_stdloc = GetCenter();
	_other_state = FOURTH;
      }
      CenterOn(_stdwhere);
      DrawGrid();
      break;
    default:
      break;
    }
    break;
  case FOURTH:
    ch = GetText();
    if (ch != 0) {
      if(ch == 1) {
	// default to 0 for wait time
	int i = 0;
	if (_output.size()) {
	  istringstream buf(_output);
	  try {
	    i = FrameParser::GrabInt(buf);
	  } catch (...) {
	    PrintServerMsg("Invalid Integer");
	    _output.resize(0);
	    break;
	  }
	}
	_stdorders.push_back(Order(_stdu,_stdw,_stdloc,i));
      }
      _output.resize(0);
      _other_state = ch==1?FIRST:Order::NeedsCoord(_stdw)?THIRD:SECOND;
      break;
    }
  }
  SetStandingOrderLabel();
  DrawInput();
}

void Cview::MakeStandingOrder(Order::CmdType w) {
  if (!Order::ValidCommand(_stdu,w)) {
    PrintServerMsg("Invalid command for that unit");
    return;
  }
  if (!Order::NeedsCoord(w) && 
      !Order::NeedsWait(_stdu)) {
    _stdorders.push_back(Order(_stdu,w,Coord(0,0),0));
    _other_state = FIRST;
  } else {
    _stdw = w;
    _other_state = Order::NeedsCoord(w)?THIRD:FOURTH;
  }
}

void Cview::OrderMore() {
  if (_orderee) {
    ResetInput(false);
    DrawInput();

    Order o(_orderee->second);
    _orderee->second = Order(o.GetUnit(),o.GetCmd(),GetCenter(),0);
			      
    if (Order::NeedsWait(o.GetUnit())) {
      _input_state = ORDERWAIT;
    } else {
      _control->SendOrder(_orderee->first,_orderee->second);
      delete _orderee;
      _orderee = NULL;
    }
  }
}

void Cview::OrderWait() {
  int ch;
  switch(_other_state){
  case START:
    ResetInput(true);
    _label = "Wait: ";
    _other_state = FIRST;
    break;
  case FIRST:
    ch = GetText();
    if(ch != 0){
      if(ch == 1){
	// default to 0 for wait time
	int i = 0;
	if (_output.size()) {
	  istringstream buf(_output);
	  try {
	    i = FrameParser::GrabInt(buf);
	  } catch (...) {
	    PrintServerMsg("Invalid Integer");
	    _output.resize(0);
	    break;
	  }
	}
	Order o = _orderee->second;
	_control->SendOrder(_orderee->first,Order(o.GetUnit(),
						  o.GetCmd(),
						  o.GetCoord(),
						  i));
	delete _orderee;
	_orderee = NULL;
      } else {
	CancelOrder();
      }
      ResetInput(false);
    }
    break;
  case SECOND:
    assert(0);
    break;
  case THIRD:
    assert(0);
    break;
  case FOURTH:
    assert(0);
    break;
  }
  DrawInput();
  return;
}
