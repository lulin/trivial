#include "person.hpp"
using namespace std;

Sex::Sex()
{
  cout << "field of bool, uninitialized explicitly: " << s << endl;
  s = ESex_male;
  cout << "initialized: " << this->to_str() << endl;
}

Sex::Sex(int s_)
{
  if (s_ < ESex_male || s_ >= ESex_female)
    s = ESex_unknown;
  else
    s = s_;
}

string Sex::to_str()
{
  if (s == ESex_male)
    return string("male");
  if (s == ESex_female)
    return string("female");
  return string("unknown");
}

Sex gsex = Sex(0);
Person::Person(const std::string &nam)
  :sex(), orign_sex(gsex)
{
  name = nam;
  this->age = 20;
  std::cout << name << " " << age << std::endl;
}

Person::Person(int s, const string& n, int a)
  : name(n), sex(s), orign_sex(gsex)
{
  if (a < 1)
    age = 20;
}

// test cases

int PersonUtils::test_constructor(void *arg)
{
  (void)arg;
  Person("lily");
  return 0;
}

void PersonUtils::showPerson(Person &per)
{
  (void)per;
  return;
}

