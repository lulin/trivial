#include <iostream>
#include <map>
#include "simple_class.hpp"

using namespace std;

extern map<string, Sample::SimpleCl *> g_smap;

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
  //delete sa;
  g_smap.erase("first");
  delete sa;
  cout << "g_smap[\"first\"].count = " << Sample::SimpleCl::getCount() << endl;

	return 0;
}
