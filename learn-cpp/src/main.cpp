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
  cout << "map[first].Number() = " << g_smap["first"]->Number() << endl;

  sa->Number() = 7;
  cout << "map[first].Number() = " << g_smap["first"]->Number() << endl;
  g_smap["first"]->Number() = 8;
  cout << "sa->Number() = " << sa->Number() << endl;

  cout << "+++++++++++++++g_smap[\"first\"].count = " << sa->getCount() << endl;

  cout << "addr sa = " << sa << " addr member = " << g_smap["first"] << endl;
  //delete sa;
  cout << "addr sa = " << sa << " addr member = " << g_smap["first"] << endl;
  g_smap["first"]->Number() = 9;
  cout << "map[first].Number() = " << g_smap["first"]->Number() << endl;
  cout << "-------------------g_smap[\"first\"].count = " << Sample::SimpleCl::getCount() << endl;
  Sample::SimpleCl *ppppp =  g_smap["first"];
  //delete ppppp;
  g_smap.erase("first");
  delete ppppp;
  cout << "-------------------g_smap[\"first\"].count = " << Sample::SimpleCl::getCount() << endl;
  cout << "g_smap[\"first\"].count = " << Sample::SimpleCl::getCount() << endl;

  cout << "Test `delete' keyword ..." << endl;
  Sample::SimpleCl *sb = new Sample::SimpleCl(99);
  cout << "Printing instance count after creating an object by new keyword: "
       << Sample::SimpleCl::getCount() << endl;

  Sample::SimpleCl *sc = sb;
  sc->setNumber(88);
  sc->Number() = 79;
  cout << "Printing instance count after referring by a new pointer: "
       << Sample::SimpleCl::getCount() << endl;
  cout << "sc->Number is " << sc->Number() << endl;

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

  // Test anonymous struct
  Sample::SpecConstr sc1(9);
  sc1.getAnonymN();

  // Test copy initialization
  Sample::TestCopyInit t1(10);
  Sample::TestCopyInit t2(t1);
  cout << "t1.N = " << t1.N << ";    t2.N = " << t2.N << endl;

  // Test reference returning
  Sample::TestRef tr1;
  tr1.O() = t2;
  cout << "tr1.O().N = " << tr1.O().N << endl;

  int ttrm1 = 9;
  Sample::TestRefMemb trm1(ttrm1);
  cout << "trm1.Ref() = " << trm1.Ref() << endl;

  cout << " SimpleCl.getCount = " << Sample::SimpleCl::getCount() << endl;
  Sample::SimpleCl *sp1 = new Sample::SimpleCl(99);
  Sample::SimpleCl *sp2 = sp1;
  cout << " SimpleCl.getCount = " << sp2->getCount() << endl;
  delete sp1;
  cout << "sp2.Number() = " << sp2->Number()
       << " SimpleCl.getCount = " << sp2->getCount() << endl;
  sp2->Number() = 11;
  // delete sp2;
  cout << " SimpleCl.getCount = " << Sample::SimpleCl::getCount() << endl;

  std::string str1;
  cout << "str1(uninitialized) content = " << str1 << endl;


  Sample::TestMembInit tm("hehe");
  cout << "tm.Sstr() = " << tm.Sstr() << endl;
  // Return ------------------------------------------
	return 0;
}
