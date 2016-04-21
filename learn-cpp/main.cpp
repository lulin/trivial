#include <iostream>
#include "simple_class.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	cout << "My first c++ program.\n";

  // Create an auto variable
  Sample::SimpleCl sa(10);

  cout << "Auto object created: SimpleCl(10)" << endl;
  cout << "SimpleCl->count = " << sa.getCount() << endl;
	return 0;
}
