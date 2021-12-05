#include <stdio.h>

#include "image.h"
#include "algos.h"

int main(int argc, char**argv) {
	channel a = 5;
	printf("yay %d\n", a);
	a = (channel) test();
	printf("yay2 %d\n", a);
	return 0;
}