// Stonecutters CS351 S03 -*- C++ -*-

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

  HelloMsg(int v, Type t, std::string id, std::string vl)
    : Message(_keyword),_version(v), _type(t), _id(id), _validator(vl) {};
  HelloMsg(std::istream &);
  ~HelloMsg(){};

  static std::string Keyword() { return _keyword; };
  virtual const std::string Innards() const;

  int GetVersion() const { return _version; };
  static int CurrentVersion() { return _current_version; };
  Type GetType() const { return _type; };
  static Type GrabType(std::istream &);
  std::string GetId() const { return _id; };
  std::string GetValidator() const { return _validator; };
  bool CheckVersion() { return (_version == _current_version); };

private:
  static const std::string _keyword;
  int _version;
  Type _type;
  std::string _id;
  std::string _validator;

  const static int _current_version = 2;
};

#endif // HELLOMSG_H
