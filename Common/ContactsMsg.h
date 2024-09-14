// Stonecutters CS351 S03 -*- C++ -*-

#ifndef CONTACTSMSG_H
#define CONTACTSMSG_H

// includes
#include <vector>
#include "Message.h"
#include "Order.h"
#include "Coord.h"

class ostream;
class istream;

class ContactsMsg : public Message {
public:

  class Contact {
  public:
    Contact(Coord c, Order::UnitType t, int e):_c(c),_type(t),_e(e){};
    Contact(istream &in) { in >> *this; };
    ~Contact(){};

    Coord GetCoord() const { return _c; };
    Order::UnitType GetType() const { return _type; };
    int GetEmp() const { return _e; };

    string ToString() const;
    friend ostream& operator<<(ostream &o, const Contact &c) {
      o << c.ToString(); return o;
    };
    friend istream& operator>>(istream &, Contact&);

    bool operator==(const Contact &c) const;

  private:
    Coord _c;
    Order::UnitType _type;
    int _e;
  };

  class Terrain {
  public:
    enum Type {
#define XX(a) a,
#include "TerrainTypes"
#undef XX
      __TR_END__
    };

    Terrain(Coord c, Type t):_c(c),_type(t){};
    Terrain(istream &in) { in >> *this; };
    ~Terrain(){};

    Coord GetCoord() const { return _c; };
    Type GetType() const { return _type; };

    string ToString() const;
    friend ostream& operator<<(ostream &o, const Terrain &t) {
      o << t.ToString(); return o;
    };
    friend istream& operator>>(istream &, Terrain&);

  private:
    Coord _c;
    Type _type;
    const string Innards() const;
  };

  class Active {
  public:
    Active(Coord c, int i, int h, Order o):_c(c),_id(i),_hits(h),_o(o){};
    Active(istream &in) : _o(Order(Order::CT,Order::GR,Coord(0,0),0)) {
      in >> *this;
    };
    ~Active(){};

    Coord GetCoord() const { return _c; };
    int GetId() const { return _id; };
    int GetHits() const { return _hits; };
    Order GetOrder() const { return _o; };

    string ToString() const;
    friend ostream& operator<<(ostream &o, const Active &a) {
      o << a.ToString(); return o;
    };
    friend istream& operator>>(istream &, Active&);

  private:
    Coord _c;
    int _id;
    int _hits;
    Order _o;
  };

  ContactsMsg(vector<Contact> c, vector<Terrain> t, vector<Active> a)
    : Message(_keyword), _c(c), _t(t), _a(a) {};
  ContactsMsg(istream &);
  ~ContactsMsg(){};

  static string Keyword() { return _keyword; };
  virtual const string Innards() const;

  vector<Contact> GetContacts() const { return _c; };
  vector<Terrain> GetTerrains() const { return _t; };
  vector<Active> GetActives() const { return _a; };

private:
  static const string _keyword;

  vector<Contact> _c;
  vector<Terrain> _t;
  vector<Active> _a;
};

#endif // CONTACTSMSG_H
