// A tiny -*- C++ -*- wrapper around the magnificent hideousity that is curses.[ch]
// Version 3.1 Wed Apr 16 03:36:20 2003 Ackley Refreshed for CS351 S03
// Version 3.0 Thu Nov 14 01:17:01 2002 Ackley Refreshed for CS351 F02

// Stonecutters CS351 S03

#ifndef CURSE_H
#define CURSE_H

// We're going for just a few things with this:
// (1) Only the most basic curses functionality -- initialize, cleanup,
//     erase, put a char here, and refresh, basically.  No explicit 
//     support for subwindows, pads, colors, etc.
// (2) The ability for applications to use curses-based stuff without ever
//     having to #include <curses.h>, which was clever in its time and
//     place, but now is an incredible screw, #defining as macros common
//     words like 'clear', typedeffing (g++) built-in's like 'bool', and
//     so forth.  So the scheme is that *only* Curse.C has to deal with
//     curses.h, and nobody else touches it.
// (3) A semi-clean way to handle programs that may or may not want to
//     use curses on any particular run.  In particular, the program
//     should still be able to make all its Curse calls whether or not
//     they actually do anything.
// (4) A semi-clean way to guarantee that we won't leave the terminal
//     in wedged state no matter how the program exits (short of segfault
//     or the like).

#include <stddef.h>		/* for size_t */



class Curse {
public:
  static Curse * Instance();    // Be a singleton
  bool Activate();		// Attempt to start up curses, return result
  bool Terminate();		// Shut down curses, return whether it was active
  bool IsActive() {return _running;} ;  // Returns true if curses currently active
  int GetScreenWidth() {return _running?_width:0;} ;
  int GetScreenHeight() {return _running?_height:0;} ;
  void Erase();			// Erase the new screen
  void Redraw();		// Redraw whole current screen as is
  void PutCharAt(int x,int y,unsigned short ch); // Put a char on the new screen
  // put a color char on the screen
  void PutColorCharAt(int x, int y, unsigned short ch, int which, int base);
  void GoTo(int x,int y);	// Move the cursor to x,y
  void Refresh();		// Make screen look like new screen
  int ReadChar();		// Return an input char or -1 if none available
  void Pause(size_t msecs=1000); // Sleep for msecs (default 1 second)
  unsigned short GetCharAt(int x,int y);  // Return char at x,y (w/attributes)
  bool Resize();               //If screen size changed set and return true
  void PutString(const char *str);
  bool HasColor() const { return _hascolor; };
private:
  Curse() ;                     // Build the Curse.  Leave it inactive to start
  ~Curse() ;                    // Terminate curses if was in use
  bool _running;		// if false, no curses activity performed
  int _height;			// screen max height
  int _width;			// screen max width
  bool _hascolor;               // Whether the screen supports color
} ;

#endif
