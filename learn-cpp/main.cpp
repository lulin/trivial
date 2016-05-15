#include <iostream>
#include <map>
#include "simple_class.hpp"

using namespace std;

extern map<string, Sample::SimpleCl *> g_smap;
Sample::SimpleCl *g_simple = new Sample::SimpleCl();

int main(int argc, char *argv[])
{
	cout << "My first c++ program.\n";

  // Create an auto variable
  Sample::SimpleCl *sa = new Sample::SimpleCl(10);

  cout << "Auto object created: SimpleCl(10)" << endl;
  cout << "SimpleCl->count = " << sa->getCount() << endl;

  cout << "g_smap[\"first\"].count = " << sa->getCount() << endl;
  g_smap.insert(pair<string, Sample::SimpleCl *>(string("first"), sa));

  cout << "g_smap[\"first\"].count = " << sa->getCount() << endl;
  delete sa;
  cout << "g_smap[\"first\"].count = " << Sample::SimpleCl::getCount() << endl;
  cout << "segment fault? " << g_smap["first"]->getCount() << endl;
  g_smap.erase("first");
  //delete sa;
  cout << "g_smap[\"first\"].count = " << Sample::SimpleCl::getCount() << endl;

  cout << "Test `delete' keyword ..." << endl;
  Sample::SimpleCl *sb = new Sample::SimpleCl(99);
  cout << "Printing instance count after creating an object by new keyword: "
       << Sample::SimpleCl::getCount() << endl;

  Sample::SimpleCl *sc = sb;
  sc->setNumber(88);
  cout << "Printing instance count after referring by a new pointer: "
       << Sample::SimpleCl::getCount() << endl;

  delete sb;
  cout << "Printing instance count after deletting a pointer: "
       << Sample::SimpleCl::getCount() << endl;

  // Will calling delete on a pointer affect the equal reference which is an
  // element of a map?
  cout << "Test map element referring." << endl;
  Sample::SimpleCl *sd = new Sample::SimpleCl("sd", 7);
  g_smap.insert(pair<string, Sample::SimpleCl *>(sd->Name(), sd));
  cout << "New instance: " << sd->Name() << "," << sd->Number() << endl;
  cout << "Count: " << sd->getCount() << endl;

  cout << "Erase (" << sd->Name() << "," << sd->Number() << ") from map" << endl;
  g_smap.erase(sd->Name());
  cout << "Count: " << sd->getCount() << endl;
  cout << "map(" << sd->Name() << ") ?= nil : "
       << (g_smap[sd->Name()] == NULL? "yes": "no")
       << endl;

  // Test operator overload
  Sample::SimpleCl se(10);
  // se = se + 1;
  cout << "Number of SimpleCl(10) + 1 = " << (se + 1).Number() << endl;

  Sample::Assist as;
  se.setHook(&as.hook, &as);
  se.callHook();

  se[0] = 65;
  cout << "Se[0] = " << se[0] << endl;
	return 0;
}
