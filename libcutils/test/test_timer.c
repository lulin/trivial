/*
 * Copyright (c) 2014
 *
 * "License"
 *
 * Bug reports and issues: <"Email">
 *
 * This file is part of cwfragment.
 */

#include "timer.h"
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	struct timer *timer = timer_new();
	sleep(1);
	printf("Elapsed: %lu ms\n", timer_elapsed(timer, NULL));

	timer_stop(timer);
	sleep(1);
	printf("Elapsed: %lu ms\n", timer_elapsed(timer, NULL));

	timer_continue(timer);
	sleep(1);
	printf("Elapsed: %lu ms\n", timer_elapsed(timer, NULL));

	timer_destroy(&timer);
	return 0;
}
