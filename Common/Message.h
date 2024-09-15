// Stonecutters CS351 S03 -*- C++ -*-

#ifndef MESSAGE_H
#define MESSAGE_H

// includes
#include <string>
#include <map>

// forward declare
class Model;

class Message {
public:
  // all msgs have keyword, so derived classes must pass it in
  Message(std::string kw) : _keyword(kw) {};
  virtual ~Message(){};

  // to register factory methods
  static bool Register(std::string kw, Message*(*)(std::istream&));

  // to call factory methods
  static Message* GenMsg(std::istream&);

  // to make a frame from the innards and keyword
  virtual const std::string Innards() const = 0;
  const std::string ToString() const;
  const std::string ToFrame() const;

  // to do the work
  virtual void Execute(Model*) = 0;

private:
  typedef std::map<std::string,Message*(*)(std::istream&)> MessageMap;
  static MessageMap* _map;

  std::string _keyword;
};

#endif // MESSAGE_H
