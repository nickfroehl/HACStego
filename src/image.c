#include <stdio.h>

#include <png.h>
#include "image.h"
#include "errno.h"
#include "qdbmp.h"
//#include "spng.h"


int test() {
	printf("test\n");
	return 1;
}

char is_png(const char *file_name) {
	FILE *fp;
	char magic[PNG_MAGIC_SIZE];
	
	fp = fopen(file_name, "rb");
	
	if (!fp) return EBADFILE;
	fread(header, 1, PNG_MAGIC_SIZE, fp);
	if (png_sig_cmp(magic, 0, PNG_MAGIC_SIZE)) return ENOTPNG;
	else return 0;
}