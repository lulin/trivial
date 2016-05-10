#ifndef SIMPLE_CLASS_H_
#define SIMPLE_CLASS_H_

#include <unistd.h>           // for size_t

namespace Sample {
  class SimpleCl {
  public:
    SimpleCl(int n = 0);
    SimpleCl(const char *name, int n = 0);
    ~SimpleCl();
    int Number();
    void setNumber(int n);
    void pretty_print();
    static int getCount();

    std::string Name();

    const static size_t name_size = 256;

  private:
    static int count;
    int number;
    char name[name_size];
  };
}

#endif
