#include <stdio.h>

#include "image.h"
#include "algos.h"

int main(int argc, char**argv) {
	channel a = 5;
	a = (channel) test1();
	printf("test1: %d\n", a);
	//a = (channel) test3(); //there's is literally broken lmao, so much for their, yknow, everything...
	//printf("test3: %d\n", a);
	a = (channel) test4();
	printf("test4: %d\n", a);
	return 0;
}