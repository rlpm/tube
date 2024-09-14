// This is Curse.C - a wimpy -*- C++ -*- wrapper around (n)curses
// Version 3.1 Wed Apr 16 03:36:20 2003 Ackley Refreshed for CS351 S03
// Version 3.0 Thu Nov 14 01:17:01 2002 Ackley Refreshed for CS351 F02

// Stonecutters CS351 S03
// $Id: Curse.C,v 1.10 2003/05/15 02:35:27 rlpm Exp $

#include <sys/types.h>		/* For select */
#include <sys/time.h>		/* For struct timeval */
#include <unistd.h>		/* For select */
#include "Curse.h"

// Only include curses.h down here so we don't pollute
// all of the Curse.h users' namespaces with
// all of curses.h's hideous macros and such
#include <curses.h>

// There's only one terminal screen per process,
// So let's make it a singleton.  
Curse * Curse::Instance()
{
  static Curse ptr;
  return &ptr;
}

// Private ctor.  Just start up not in 
// graphings '_running' mode
Curse::Curse() : _hascolor(false)
{
  _running = false;
}

// Turn off graphics if we manage to die
Curse::~Curse()
{
  Terminate();
}

// Clear the screen
void Curse::Erase()
{
  if (_running) erase();
}

// Redraw the real screen as it last was
// (NOTE: This is NOT what you want to 
// get NEW stuff shown on the screen -- for
// that you want Curse::Refresh.)
void Curse::Redraw()
{
  if (_running) redrawwin(curscr);
}

// Make the real screen look like the drawn screen
void Curse::Refresh()
{
  if (_running) refresh();
}

// PutCharAt takes an unsigned short even though
// it's expected to be just a char, because you
// can control other attributes of the display 
// (like reverse video and such) using the extra 
// bits)
void Curse::PutCharAt(int x,int y,unsigned short ch)
{
  if (_running) mvaddch(y,x,ch);
}

void Curse::PutColorCharAt(int x,int y,unsigned short ch, int which, int base=0)
{
  if (_running) mvaddch(y,x,ch | COLOR_PAIR(which + (2 * base)));
}

// GetCharAt returns an unsigned short for the same reason
unsigned short Curse::GetCharAt(int x, int y)
{
  return _running?mvinch(y,x):0;
}

// Move the cursor to the given position, on 
// the next Refresh()
void Curse::GoTo(int x,int y)
{
  if (_running) move(y,x);
}

// Return -1 if no chars available to be read from the
// keyboard, or the next char read.
int Curse::ReadChar()
{
  if (!_running) return -1;

  int ret = getch();
  if (ret==ERR) return -1;
  return ret;
}

// Do nothing for 'msecs' milliseconds
void Curse::Pause(size_t msecs)
{
  if (!_running) return;
  if (msecs == 0) return;
  struct timeval timeout;
  timeout.tv_sec = msecs/1000;
  timeout.tv_usec = (msecs%1000)*1000;
  select(0,0,0,0,&timeout);
}

// Attempt to start up graphics.
// Return false if it didn't work
bool Curse::Activate()
{
  if (_running) refresh();
  else {
    SCREEN * s = newterm((char *) 0,stdout,stdin);
    if (s) {			// It worked
      set_term(s);		// so tell curses to use it
      _width = COLS;		// and set up crap
      _height = LINES;
      cbreak();
      noecho();
      nodelay(stdscr,1);
      //color stuff
      _hascolor = has_colors();
      start_color();
      init_pair(1, COLOR_BLACK, COLOR_MAGENTA);
      init_pair(2, COLOR_BLACK, COLOR_GREEN);
      init_pair(3, COLOR_BLACK, COLOR_BLUE);
      init_pair(4, COLOR_WHITE, COLOR_GREEN);
      init_pair(5, COLOR_WHITE, COLOR_BLUE);
      init_pair(6, COLOR_RED, COLOR_GREEN);
      init_pair(7, COLOR_RED, COLOR_BLUE);
      //end color stuff
      //      keypad(stdscr, TRUE);      //initialize special key codes
      _running = true;
    }
  }
  return _running;
}

// Shutdown graphics mode.  If you
// can arrange it, it's nice to call this
// before exiting your programs.
bool Curse::Terminate()
{
  bool was = _running;
  if (_running) {
    noraw();
    echo();
    endwin();
    _running = false;
  }
  return was;
}


bool Curse::Resize(){
  if(_running){
    int change_y;
    int change_x;
    getmaxyx(stdscr, change_y, change_x);

    if(change_x != _width || change_y != _height){
      _width = change_x;
      _height = change_y;
      return 1;
    }
    return 0;
  }
  return 0;
}

void Curse::PutString(const char *str){
  if(_running) waddstr(stdscr, str);
}
