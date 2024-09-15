#ifndef SOCKINET_H
#define SOCKINET_H

#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>

class sockinetaddr {
public:
  sockinetaddr() {}
  sockinetaddr(long unsigned int addr, int port) {}
  sockinetaddr(const std::string host, int port) {}
  std::string gethostname() const { return "remotehost"; }
  int getport() const { return 54321; }
};

class sockinetbuf {
public:
  sockinetbuf(int type) {}
  std::string localhost() const { return "localhost"; }
  int localport() const { return 12345; }
  void recvtimeout(int t) {}
  void sendtimeout(int t) {}
  void bind(sockinetaddr a) {}
  int accept(sockinetaddr a) { return 0; }
  void listen() {}
  void connect(sockinetaddr a) {}
  int is_readready(int, int) { return 1; }
  int read(char* buf, const int bufsize) { return 0; }
  int write(const char* buf, const int bufsize) { return 0; }
};

class iosockinet {
public:
  iosockinet() {}
  iosockinet(int) {}
  sockinetbuf* operator-> () { return NULL; }
};

class sockerr {
public:
  int serrno() const { return 0; }
  const char* errstr() const { return "error"; }
};

class sockbuf {
public:
  enum type {
    sock_stream = SOCK_STREAM
  };
};

#endif
