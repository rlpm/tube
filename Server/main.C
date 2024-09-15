// Stonecutters CS351 S03 -*- C++ -*-

#include <iostream>
#include <string>
#include <sstream>
#include <cassert>
#include "World.h"

void usage() {
  std::string n("tubes");
  std::cerr << "Usage: " << n << " [options]" << std::endl
            << "Options:" << std::endl
            << " -p <port>      Port number on which to accept connections." << std::endl
            << "                If that port is not available, it will try to bind to " << std::endl
            << "                the next 9 numbers" << std::endl
            << "                default: 8000  min:1025  max:60999" << std::endl
            << " -s <gamespeed> Number of seconds for each COMMAND phase" << std::endl
            << "                default:1" << std::endl
            << " -m <maxcmdrs>  Maximum number of Commanders" << std::endl
            << "                default:10  max:25" << std::endl
            << " -w <waittime>  Number of seconds to wait for Commanders before" << std::endl
            << "                starting the game" << std::endl
            << "                default:30" << std::endl
            << " -t <maxturns>  Maximum number of turns before forced game end" << std::endl
            << "                (Not including turn #0" << std::endl
            << "                default:5000" << std::endl
            << " -x <cols>      Number of columns in torus" << std::endl
            << "                default:100" << std::endl
            << " -y <rows>      Number of rows in torus" << std::endl
            << "                default:50" << std::endl
            << " -g             Print Map and turn number at end of each turn" << std::endl
            << std::endl;
}

int main(int argc,char **argv)
{
  int maxc=10, speed=1, wait=30, port=8000, turns=5000, x=100, y=50, grace=10;
  bool pg=false, gm=false;

  enum { NONE, PORT, SPEED, MAXC, WAIT, TURNS, X, Y, GRACE } state = NONE;
  while (--argc && ++argv) {
    std::string param(*argv);
    std::istringstream iss(param);
    switch (state) {
    case NONE:
      if ( param == "-p") {
	state = PORT;
      } else if (param == "-s") {
	state = SPEED;
      } else if (param == "-m") {
	state = MAXC;
      } else if (param == "-t") {
	state = TURNS;
      } else if (param == "-w") {
	state = WAIT;
      } else if (param == "-x") {
	state = X;
      } else if (param == "-y") {
	state = Y;
      } else if (param == "-g") {
	pg = true;
      } else if (param == "-r") {
	state = GRACE; // :)
      } else if (param == "-G") {
	gm = true;
      } else {
	usage();
	exit(1);
      }
      break;
    case PORT:
      iss >> port;
      state = NONE;
      break;
    case SPEED:
      iss >> speed;
      state = NONE;
      break;
    case MAXC:
      iss >> maxc;
      state = NONE;
      break;
    case WAIT:
      iss >> wait;
      state = NONE;
      break;
    case X:
      iss >> x;
      state = NONE;
      break;
    case Y:
      iss >> y;
      state = NONE;
      break;
    case TURNS:
      iss >> turns;
      state = NONE;
    case GRACE:
      iss >> grace;
      state = NONE;
      break;
    default:
      assert(0);
      break;
    }
  }

  if (port<1025 || port>61000 || maxc<2 || maxc>25 || wait < 0 || speed < 1) {
    usage();
    exit(1);
  }

  World w(Coord(x,y),maxc,speed,wait,port,turns,pg,grace,gm);
  w.Run();
  return 0;
}
