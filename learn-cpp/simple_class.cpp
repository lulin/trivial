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
}
