/*
 * Copyright (c) 2014
 *
 * "License"
 *
 * Bug reports and issues: <"Email">
 *
 * This file is part of learn-glib.
 */

#include "l-garray.h"

void
learn_g_array()
{
	printf("Learn [garray] ... \n");
	printf("====\n");

	GArray *ar;
	char *strs[] = {
		"hello",
		"world",
		",",
		"I",
		"am",
		"learning",
		"GArray"
	};
	int i;

	ar = g_array_new(FALSE, FALSE, sizeof(void *));

	for (i = 0; i < sizeof(strs)/sizeof(char *); i++)
		g_array_append_val(ar, strs[i]);

	printf("Totally %d elements appended. They say:\n  \"", ar->len);
	for (i = 0; i < ar->len; i++)
		printf("%s ", g_array_index(ar, char *, i));

	printf("\b.\"\n");
	g_array_free(ar, TRUE);
}
