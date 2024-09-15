// Stonecutters CS351 S03 -*- C++ -*-

#include <iostream>
#include "Control.h"
#include <string>



int main(int argc, char ** argv)
{
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " host port" << std::endl;
    exit(1);
  }

  char * hostname = argv[1];
  int portnum = atoi(argv[2]);

  Control test(hostname, portnum);
  test.Run();
  return 0;
}
  
