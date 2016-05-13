#include <iostream>
#include <stdio.h>

#include "simple_class.hpp"

namespace Sample {
  using namespace std;

  int SimpleCl::count = 0;

  SimpleCl::SimpleCl(int n) {number = n; count++;}

  SimpleCl::SimpleCl(const char *name, int n) {
    snprintf(this->name, name_size, "%s", name);
    number = n;
    count++;
  }

  SimpleCl::~SimpleCl() {
    count--;
  }

  int SimpleCl::Number() {return number;}
  void SimpleCl::setNumber(int n) {number = n;}
  int SimpleCl::getCount() {return count;}
  void SimpleCl::pretty_print() {
    return;
  }

  string SimpleCl::Name() {return string(this->name);}

  void SimpleCl::setHook(hook_t *h, Assist *a) {
    if (h && a) {
      hk = h;
      this->a = a;
    }
  }

  void SimpleCl::callHook() {
    if (hk && a)
      hk(a, this);
  }

  // Operators:
  SimpleCl& operator+(SimpleCl& s, int n) {
    s.setNumber(s.Number() + n);
    return s;
  }

  Assist::Assist(string m): msg(m) {};
  void Assist::hook(Assist *a, SimpleCl *s) {
    cout << "Call hook : " << s->Number() << endl;
    cout << "Assist says \"" << a->getMsg() << "\"" << endl;
  }

  string& Assist::getMsg() {return msg;}

  SpecConstr::SpecConstr(int n): number(n) {};
  int SpecConstr::getNumber() {return number;}
}
