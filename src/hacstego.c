#include <stdio.h>

#include "image.h"
#include "algos.h"

int main(int argc, char**argv) {
	channel a = 5;
	a = (channel) test1();
	printf("test1: %d\n", a);
	a = (channel) test3();
	printf("test3: %d\n", a);
	return 0;
}