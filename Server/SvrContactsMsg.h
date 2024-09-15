// Stonecutters CS351 S03 -*- C++ -*-

#ifndef SVRCONTACTSMSG_H
#define SVRCONTACTSMSG_H

// includes
#include <vector>
#include "ContactsMsg.h"

// forward declare
class Model;
class istream;

class SvrContactsMsg : public ContactsMsg {
public:
  SvrContactsMsg(std::vector<ContactsMsg::Contact>c, std::vector<ContactsMsg::Terrain>t,
		 std::vector<ContactsMsg::Active>a) : ContactsMsg(c,t,a) {};
  SvrContactsMsg(std::istream &i) : ContactsMsg(i) {};
  virtual void Execute(Model*);

  static Message* GenMsg(std::istream &i) {
    return new SvrContactsMsg(i);
  }

private:
};

#endif // SVRCONTACTSMSG_H
