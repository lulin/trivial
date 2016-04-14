#ifndef SIMPLE_CLASS_H_
#define SIMPLE_CLASS_H_

#include <unistd.h>           // for size_t

namespace {
	class SimpleCl {
		public:
			SimpleCl();
			SimpleCl(const char *name);
			~SimpleCl();
			void pretty_print();

			const static size_t name_size = 256;

		private:
			static int count;
			int number;
			char name[name_size];
	};
}

#endif
