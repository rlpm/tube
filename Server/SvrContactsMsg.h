// Stonecutters CS351 S03 -*- C++ -*-
// $Id: SvrContactsMsg.h,v 1.1 2003/05/06 00:58:24 rlpm Exp $

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
  SvrContactsMsg(vector<ContactsMsg::Contact>c, vector<ContactsMsg::Terrain>t,
		 vector<ContactsMsg::Active>a) : ContactsMsg(c,t,a) {};
  SvrContactsMsg(istream &i) : ContactsMsg(i) {};
  virtual void Execute(Model*);

  static Message* GenMsg(istream &i) {
    return new SvrContactsMsg(i);
  }

private:
};

#endif // SVRCONTACTSMSG_H
