#include <iostream>
#include <stdio.h>

#include "simple_class.hpp"

namespace Sample {
  int SimpleCl::count = 0;

  SimpleCl::SimpleCl(int n) {number = n; count++;}

  SimpleCl::SimpleCl(const char *name, int n) {
    snprintf(this->name, name_size, "%s", name);
    number = n;
    count++;
  }

  SimpleCl::~SimpleCl(){}

  int SimpleCl::getCount() {return count;}
}
