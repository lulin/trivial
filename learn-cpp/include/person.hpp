#ifndef PERSON_HPP_
#define PERSON_HPP_

#include <iostream>
#include <string>

class sex {
public:
  sex();
  sex(int s_);
  std::string to_str();
private:
  int s;
};
class Person {
public:
  Person(const std::string &nam);

private:
  std::string name;
  sex sex;
  int age;
  bool married;
  std::string phone;
};

class PersonUtils {
public:
  static void showPerson(Person& per);
  static int test_constructor(void *arg);
};

#endif
