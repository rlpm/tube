// Stonecutters CS351 S03 -*- C++ -*-

#ifndef CLICONTACTSMSG_H
#define CLICONTACTSMSG_H

// includes
#include <vector>
#include "ContactsMsg.h"

// forward declare
class Model;
class istream;

class CliContactsMsg : public ContactsMsg {
public:
  CliContactsMsg(std::vector<Contact> c, std::vector<Terrain> t, std::vector<Active> a)
    : ContactsMsg(c,t,a) {};
  CliContactsMsg(std::istream &i) : ContactsMsg(i) {};
  virtual void Execute(Model*);

  static Message* GenMsg(std::istream &i) {
    return new CliContactsMsg(i);
  }

private:
};

#endif // CLICONTACTSMSG_H
