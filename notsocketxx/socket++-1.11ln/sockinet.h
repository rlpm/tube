#ifndef SOCKINET_H
#define SOCKINET_H

#include <string>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

class sockerr {
public:
  sockerr(int e, std::string s) : _e(e), _s(s) {}
  int serrno() const { return _e; }
  const char* errstr() const { return _s.c_str(); }
private:
  int _e;
  std::string _s;
};

class sockbuf {
public:
  enum type {
    sock_stream = SOCK_STREAM
  };
};

struct sockinetaddr {
  sockinetaddr() {
    memset((void*)&_sin,0,sizeof(_sin));
    _sin.sin_family = AF_INET;
    _sin.sin_port = 0;
    _sin.sin_addr.s_addr = INADDR_ANY;
  }
  sockinetaddr(long unsigned int addr, int port) {
    memset((void*)&_sin,0,sizeof(_sin));
    _sin.sin_family = AF_INET;
    _sin.sin_port = htons(port);
    _sin.sin_addr.s_addr = htonl(addr);
  }
  // only supports dotted-decimal, not DNS resolution, for simplicity
  sockinetaddr(const std::string host, int port) {
    memset((void*)&_sin,0,sizeof(_sin));
    int ret = inet_pton(AF_INET, host.c_str(), &_sin);
    if (ret) throw ret;
    _sin.sin_family = SOCK_STREAM;
    _sin.sin_port = htons(port);
  }
  std::string gethostname() const { return inet_ntoa(_sin.sin_addr); }
  int getport() const { return ntohs(_sin.sin_port); }

  struct sockaddr_in _sin;
};

struct sockdesc {
  sockdesc(int fd) : _fd(fd) {}
  ~sockdesc() { if (_fd != -1) close(_fd); }
  int _fd;
};

class sockinetbuf {
public:
  sockinetbuf(sockbuf::type t) : _sock(-1) {}
  sockinetbuf(sockdesc d) : _sock(d) {}

  std::string localhost() const {
    struct sockaddr_in sin;
    socklen_t len = sizeof(sin);
    if (0 != ::getsockname(_sock._fd, (struct sockaddr*)&sin, &len)) {
      throw sockerr(errno, ::strerror(errno));
    }
    return inet_ntoa(sin.sin_addr);
  }
  int localport() const {
    struct sockaddr_in sin;
    socklen_t len = sizeof(sin);
    if (0 != ::getsockname(_sock._fd, (struct sockaddr*)&sin, &len)) {
      throw sockerr(errno, ::strerror(errno));
    }
    return ntohs(sin.sin_port);
  }
  void recvtimeout(int t) {}
  void sendtimeout(int t) {}
  void bind(sockinetaddr a) {
    _sock._fd = ::socket(PF_INET, SOCK_STREAM, 0);
    if (_sock._fd == -1) {
      throw sockerr(errno, std::string("socket: ") + strerror(errno));
    }
    if (0 != ::bind(_sock._fd, (struct sockaddr*)&a._sin, sizeof(a._sin))) {
      throw sockerr(errno, std::string("bind: ") + strerror(errno));
    }
  }
  sockdesc accept(sockinetaddr& a) { return sockdesc(-1); }
  void listen() {}
  void connect(sockinetaddr a) {}
  int is_readready(int, int) { return 0; }
  int read(char* buf, const int bufsize) { return ::read(_sock._fd, buf, bufsize); }
  int write(const char* buf, const int bufsize) { return ::write(_sock._fd, buf, bufsize); }
private:
  sockdesc _sock;
};

class iosockinet {
public:
  iosockinet(sockbuf::type t=sockbuf::sock_stream) : _s(new sockinetbuf(t)) {}
  iosockinet(const sockdesc d) : _s(new sockinetbuf(d)) {}
  ~iosockinet() { delete _s; }
  sockinetbuf* operator-> () { return _s; }
private:
  sockinetbuf* _s;
};

#endif
