#ifndef SOCKINET_H
#define SOCKINET_H

#include <string>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>

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
    _sin.sin_family = AF_INET;
    _sin.sin_port = htons(port);
    int ret = inet_pton(AF_INET, host.c_str(), &_sin.sin_addr);
    if (ret == 0) throw sockerr(-1, std::string("failed to parse IP address ") + host);
    else if (ret == -1) throw sockerr(errno, std::string("inet_pton: ") + strerror(errno));
  }
  std::string gethostname() const { return inet_ntoa(_sin.sin_addr); }
  int getport() const { return ntohs(_sin.sin_port); }

  struct sockaddr_in _sin;
};

struct sockdesc {
  sockdesc(int fd) : _fd(fd) {}
  int _fd;
};

class sockinetbuf {
public:
  sockinetbuf(sockbuf::type t) : _sock(-1) {}
  sockinetbuf(sockdesc d) : _sock(d) {}
  ~sockinetbuf() { if (_sock._fd != -1) close(_sock._fd); }

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
  sockdesc accept(sockinetaddr& a) {
    socklen_t len = sizeof(a._sin);
    int fd = ::accept(_sock._fd, (struct sockaddr*)&a._sin, &len);
    if (-1 == fd) {
      throw sockerr(errno, std::string("accept: ") + strerror(errno));
    }
    return sockdesc(fd);
  }
  void listen() {
    if (0 != ::listen(_sock._fd, 1)) {
      throw sockerr(errno, std::string("listen: ") + strerror(errno));
    }
  }
  void connect(sockinetaddr a) {
    std::cout << "connecting to " << a.gethostname() << ":" << a.getport() << std::endl;
    _sock._fd = ::socket(PF_INET, SOCK_STREAM, 0);
    if (_sock._fd == -1) {
      throw sockerr(errno, std::string("socket: ") + strerror(errno));
    }
    if (0 != ::connect(_sock._fd, (struct sockaddr*)&a._sin, sizeof(a._sin))) {
      throw sockerr(errno, std::string("connect: ") + strerror(errno));
    }
  }
  int is_readready(int s, int u=0) {
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(_sock._fd, &fds);
    timeval tv = {s, u};
    int ret = ::select(_sock._fd+1, &fds, 0, 0, &tv);
    if (-1 == ret) {
      throw sockerr (errno, std::string("select: ") + strerror(errno));
    }
    return ret;
  }
  int read(char* buf, const int bufsize) {
    if (0 == is_readready(0)) {
      throw sockerr(ETIMEDOUT, "timeout");
    }
    return ::read(_sock._fd, buf, bufsize);
  }
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
