#include "person.hpp"
using namespace std;

sex::sex()
{
  cout << s << endl;
}

Person::Person(const std::string &nam)
{
  name = nam;
  this->age = 0;
  std::cout << name << " " << age << std::endl;
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

