// Stonecutters CS351 S03 -*- C++ -*-
// $Id: Active.h,v 1.20 2003/05/13 22:35:54 jckopriv Exp $

#ifndef ACTIVE_H
#define ACTIVE_H

//include files
#include <string>
#include "Order.h"
#include "ContactsMsg.h"

// forward declarations
class Empire;
class Static;

class Active{
  friend class World;
  friend class Empire;
public:
  Active(Empire*,Order);
  virtual ~Active();

  // pure virtual methods based here in Active
  virtual void Update() = 0;
  virtual bool GetHitBy(Active*) = 0;
  virtual Coord GetLoc() = 0;
  virtual Static* GetHolder() = 0;
  virtual int Hits() const = 0;

  virtual bool IsAttackable(Active*) const;
  virtual bool KeepAlive() const { return false; };

  Order& GetOrder() { return _o; };
  void SetOrder(Order);
  bool GetStandingOrders();
  Empire* GetEmpire() const { return _e;};
  int GetId() const {return _id;};

  // helper methods for sending Contacts Message
  ContactsMsg::Active GetActive();
  ContactsMsg::Contact GetContact();

  // For testing/debugging
  virtual char GridTestChar() const { return '!'; };

private:
  Empire* _e;
  Order _o;
  int _id;
  int _w_loc;
};
#endif
