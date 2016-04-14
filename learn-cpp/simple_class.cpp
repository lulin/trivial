#include <iostream>

#include "simple_class.hpp"

namespace Sample {
	namespace SimpleCl {
		static int SimpleCl::count = 0;
		SimpleCl(int n = 0) {number = n; cout++;}
		SimpleCl(const char *name, int n = 0) {
			snprintf(this->name, name_size, "%s", name);
			number = n;
			cout++;
		}
	}
}
