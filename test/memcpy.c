#include <stdio.h>

void *_memcpy(void *dst, void *src, size_t len);
void *_memcpy2(void *dst, void *src, size_t len);
void test__memcpy() {
	int a[10] = {3906, 1, 20, 7083, 11, 36};
	int *p = a + 3;
	int i;

	for (i = 0; i < sizeof(a)/sizeof(typeof(a[0])); i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
	printf("a=^^\n");

	int b[sizeof(a)/sizeof(typeof(a[0]))];
	_memcpy(b, a, sizeof(a));
	for (i = 0; i < sizeof(b)/sizeof(typeof(b[0])); i++) {
		printf("%d ", b[i]);
	}
	printf("\n");
	printf("copy from a to b=^^\n");

	_memcpy(p, a, sizeof(a) - 3 * sizeof(a[0]));
	for (i = 0; i < sizeof(a)/sizeof(typeof(a[0])); i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
	printf("copy from a to a+3=^^\n");

	int c[10] = {1, 2, 3, 4, 5, 6, 7, 8};
	p = c + 2;
	_memcpy2(p, c, sizeof(c) - 2 * sizeof(c[0]));
	for (i = 0; i < sizeof(c)/sizeof(typeof(c[0])); i++) {
		printf("%d ", c[i]);
	}
	printf("\n");
	printf("copy from c to c+2=^^\n");
}


static char *
__memcpy__(char *dst, char *src, size_t len) {
	char *to, *from;
	size_t i, shift;

	if (dst - src < len && dst - src > 0) {             /* overlapped */
		to = dst + len - 1;
		from = src + len  - 1;
		shift = -1;
	} else {
		to = dst;
		from = src;
		shift = 1;
	}

	for (i = 0; i < len; i++) {
		*to = *from;
		to += shift;
		from += shift;
	}

	return dst;
}

void *
_memcpy(void *dest, void *src, size_t len) {
	return __memcpy__(dest, src, len);
}

static char *
__memcpy2__(char *dst, char *src, size_t len) {
	char *p, *q;

	if (dst - src >= len || dst < src)                /* safe */
		for (p = dst, q = src; p != dst + len;)
			*p++ = *q++;
	else
		for (p = dst + len - 1, q = src + len - 1; p != dst - 1;)
			*p-- = *q--;

	return dst;
}

void *
_memcpy2(void *dest, void *src, size_t len) {
	return __memcpy2__(dest, src, len);
}

int
main() {
	test__memcpy();
	return 0;
}
