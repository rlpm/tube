#ifndef SOCKINET_H
#define SOCKINET_H

#include <string>

class sockinetaddr {
public:
  sockinetaddr(const std::string host, int port) {}
  std::string gethostname() const { return "remotehost"; }
  int getport() const { return 54321; }
};

class sockinetbuf {
public:
  std::string localhost() const { return "localhost"; }
  int localport() const { return 12345; }
  void recvtimeout(int t) {}
  void sendtimeout(int t) {}
  void connect(sockinetaddr a) {}
  int read(char* buf, const int bufsize) { return 0; }
  int write(const char* buf, const int bufsize) { return 0; }
};

class iosockinet {
public:
  sockinetbuf* operator-> () { return NULL; }
};

class sockerr {
public:
  int serrno() const { return 0; }
};

#endif
