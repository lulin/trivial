#include "etimer.h"

int main(int argc, char *argv[])
{
	struct etimer *t1 = etimer_start(0);
	sleep(1);
	print("elapsed: %ld\n", etimer_elapsed(t1));
	return 0;
}
