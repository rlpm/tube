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
    Contact(std::istream &in) { in >> *this; };
    ~Contact(){};

    Coord GetCoord() const { return _c; };
    Order::UnitType GetType() const { return _type; };
    int GetEmp() const { return _e; };

    std::string ToString() const;
    friend std::ostream& operator<<(std::ostream &o, const Contact &c) {
      o << c.ToString(); return o;
    };
    friend std::istream& operator>>(std::istream &, Contact&);

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
    Terrain(std::istream &in) { in >> *this; };
    ~Terrain(){};

    Coord GetCoord() const { return _c; };
    Type GetType() const { return _type; };

    std::string ToString() const;
    friend std::ostream& operator<<(std::ostream &o, const Terrain &t) {
      o << t.ToString(); return o;
    };
    friend std::istream& operator>>(std::istream &, Terrain&);

  private:
    Coord _c;
    Type _type;
    const std::string Innards() const;
  };

  class Active {
  public:
    Active(Coord c, int i, int h, Order o):_c(c),_id(i),_hits(h),_o(o){};
    Active(std::istream &in) : _o(Order(Order::CT,Order::GR,Coord(0,0),0)) {
      in >> *this;
    };
    ~Active(){};

    Coord GetCoord() const { return _c; };
    int GetId() const { return _id; };
    int GetHits() const { return _hits; };
    Order GetOrder() const { return _o; };

    std::string ToString() const;
    friend std::ostream& operator<<(std::ostream &o, const Active &a) {
      o << a.ToString(); return o;
    };
    friend std::istream& operator>>(std::istream &, Active&);

  private:
    Coord _c;
    int _id;
    int _hits;
    Order _o;
  };

  ContactsMsg(std::vector<Contact> c, std::vector<Terrain> t, std::vector<Active> a)
    : Message(_keyword), _c(c), _t(t), _a(a) {};
  ContactsMsg(std::istream &);
  ~ContactsMsg(){};

  static std::string Keyword() { return _keyword; };
  virtual const std::string Innards() const;

  std::vector<Contact> GetContacts() const { return _c; };
  std::vector<Terrain> GetTerrains() const { return _t; };
  std::vector<Active> GetActives() const { return _a; };

private:
  static const std::string _keyword;

  std::vector<Contact> _c;
  std::vector<Terrain> _t;
  std::vector<Active> _a;
};

#endif // CONTACTSMSG_H
