#ifndef SIMPLE_CLASS_H_
#define SIMPLE_CLASS_H_

#include <unistd.h>           // for size_t

namespace Sample {
  class Assist;
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

    typedef void hook_t(Assist *, SimpleCl *);
    void setHook(hook_t *, Assist *);
    void callHook();

    const static size_t name_size = 256;

  private:
    static int count;
    int number;
    char name[name_size];

    hook_t *hk;
    Assist *a;
  };

  // Operators:
  SimpleCl& operator+(SimpleCl&, int);

  class Assist {
  public:
    Assist(std::string m = std::string("hehe"));
    static void hook(Assist *, SimpleCl *);
    std::string& getMsg();
  private:
    std::string msg;
  };

  class SpecConstr {
  public:
    SpecConstr(int n);
    int getNumber();
  private:
    int number;
  };
}

#endif
