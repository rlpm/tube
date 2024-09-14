// Stonecutters CS351 S03 -*- C++ -*-

#ifndef MESSAGE_H
#define MESSAGE_H

// includes
#include <string>
#include <map>

// forward declare
class istream;
class Model;

class Message {
public:
  // all msgs have keyword, so derived classes must pass it in
  Message(string kw) : _keyword(kw) {};
  virtual ~Message(){};

  // to register factory methods
  static bool Register(string kw, Message*(*)(istream&));

  // to call factory methods
  static Message* GenMsg(istream&);

  // to make a frame from the innards and keyword
  virtual const string Innards() const = 0;
  const string ToString() const;
  const string ToFrame() const;

  // to do the work
  virtual void Execute(Model*) = 0;

private:
  typedef map<string,Message*(*)(istream&)> MessageMap;

  // [rlpm] NOTE: 
  // Let's hope the memory manager is up by now
  static MessageMap _map;

  string _keyword;
};

#endif // MESSAGE_H
