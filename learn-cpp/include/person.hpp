#ifndef PERSON_HPP_
#define PERSON_HPP_

#include <iostream>
#include <string>

enum ESex {
  ESex_male,
  ESex_female,
  ESex_unknown
};
class Sex {
public:
  Sex();
  Sex(int s_);
  std::string to_str();
private:
  int s;
};

extern Sex gsex;
class Person {
public:
  Person(const std::string &nam);
  Person(int sex_, const std::string& nam = "noname", int age_ = 20);
  const std::string& getName();
  void rename(std::string& nam);
  const Sex& getSex();
  void setSex(Sex& s);
  int getAge();
  void setAge(int a);
  bool isMarried();
  void setMarried(bool m);
  const std::string& getPhone();
  void setPhone(std::string &p);

private:
  std::string name;
  Sex sex;
  const Sex& orign_sex;
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
