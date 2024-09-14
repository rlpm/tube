// Stonecutters CS351 S03 -*- C++ -*-
// $Id: HelloMsg.h,v 1.6 2003/05/11 18:50:10 rlpm Exp $

#ifndef HELLOMSG_H
#define HELLOMSG_H

// includes
#include <string>
#include "Message.h"

class HelloMsg : public Message {
public:
  enum Type {
#define XX(a) a,
#include "HelloTypes"
#undef XX
    __HI_END__
  };

  HelloMsg(int v, Type t, string id, string vl)
    : Message(_keyword),_version(v), _type(t), _id(id), _validator(vl) {};
  HelloMsg(istream &);
  ~HelloMsg(){};

  static string Keyword() { return _keyword; };
  virtual const string Innards() const;

  int GetVersion() const { return _version; };
  static int CurrentVersion() { return _current_version; };
  Type GetType() const { return _type; };
  static Type GrabType(istream &);
  string GetId() const { return _id; };
  string GetValidator() const { return _validator; };
  bool CheckVersion() { return (_version == _current_version); };

private:
  static const string _keyword;
  int _version;
  Type _type;
  string _id;
  string _validator;

  const static int _current_version = 2;
};

#endif // HELLOMSG_H
