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
    int& Number();
    void setNumber(int n);
    void pretty_print();
    static int getCount();

    std::string Name();

    typedef void hook_t(Assist *, SimpleCl *);
    void setHook(hook_t *, Assist *);
    void callHook();

    const static size_t name_size = 256;
    const static size_t array_size = 20;

    int& operator[](int index);

  private:
    static int count;
    int number;
    char name[name_size];
    int array[array_size];

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
    int getAnonymN() {return anonymN;}
  private:
    int number;
    // Anonymous struct
    struct {
      int anonymN;
    };
  };

  class TestCopyInit {
  public:
    TestCopyInit(int n = 0): N(n) {}
    TestCopyInit(TestCopyInit &t) {*this = t;}
    int N;
  private:
  };

  class TestRef {
  public:
    // TestRef();
    TestCopyInit & O() {return o;}
  private:
    TestCopyInit o;
  };

  class TestRefMemb {
  public:
    TestRefMemb(int &t): ref(t) {}
    int &Ref() {return ref;}
  private:
    int &ref;
  };

  class TestMembInit {
  public:
    TestMembInit(const char *s): sstr(std::string(s)) {}
    std::string & Sstr() {return sstr;}
  private:
    std::string sstr;
  };
}

#endif
