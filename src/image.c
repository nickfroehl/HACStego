#include <stdio.h>
#include <stdlib.h>
#include <png.h>

#include "image.h"
#include "errno.h"
#include "qdbmp.h"
//#include "spng.h"


char is_png(const char *file_name) {
	FILE *fp;
	char magic[PNG_MAGIC_SIZE];
	
	fp = fopen(file_name, "rb");
	
	if (!fp) return EBADFILE;
	fread(magic, 1, PNG_MAGIC_SIZE, fp);
	if (png_sig_cmp(magic, 0, PNG_MAGIC_SIZE)) return ENOTPNG;
	else return 0;
}

int test1() {
	printf("test\n");
	return is_png("./images/spectrum.png");
}
int test2() {
	png_structp read_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,0,0,0);
	png_infop info_ptr = png_create_info_struct(read_ptr);
	//png_infop end_info_ptr = png_create_info_struct(read_ptr);
	png_bytep *cpp;
	FILE *fp = fopen("./images/16by4.png", "rb");
	//FILE *fp = fopen("./images/spectrum.png", "rb");
	png_uint_32 width, height;
	unsigned int i, j, bit_depth, color_type, blah;

	png_init_io(read_ptr, fp);
	//png_read_info(read_ptr, info_ptr);
	//png_get_IHDR(read_ptr, info_ptr, &width, &height, &bit_depth, &color_type, &blah, NULL, NULL);
	png_read_png(read_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);
	printf("width, height: %d,%d\n", width, height);
	cpp = png_get_rows(read_ptr, info_ptr);
	for (i=0; i<height && i<10; i++) for (j=0; j<width && j<30; j+=3) {
		printf("(%d,%d): %d,%d,%d\n", 
			i,j,
			cpp[i][j], cpp[i][j+1], cpp[i][j+2]
		);
	}
	
	fclose(fp);
	return bit_depth;
}

int test3() {
	BMP *bmp;
	UCHAR r,g,b;
	UINT width, height, x, y;
	
	/* Read an image file */
	bmp = BMP_ReadFile("./images/all_gray.bmp");
	BMP_CHECK_ERROR( stderr, -1 ); /* If an error has occurred, notify and exit */

	/* Get image's dimensions */
	width = BMP_GetWidth( bmp );
	height = BMP_GetHeight( bmp );

	/* Iterate through all the image's pixels */
	for ( x = 0 ; x < width ; ++x ) {
		for ( y = 0 ; y < height ; ++y ) {
			/* Get pixel's RGB values */
			BMP_GetPixelRGB( bmp, x, y, &r, &g, &b );
			printf("(%d,%d): %d,%d,%d\n", x,y,r,g,b);
			/* Invert RGB values */
			BMP_SetPixelRGB( bmp, x, y, 255 - r, 255 - g, 255 - b );
		}
	}

	/* Save result */
	BMP_WriteFile( bmp, "./images/custom_inv.bmp" );
	BMP_CHECK_ERROR( stderr, -2 );

	/* Free all memory allocated for the image */
	BMP_Free( bmp );

	return 0;
}

#define BMP_DATABYTES_PER_ROW bmp->Header->Width*((bmp->Header->BitsPerPixel>>3)
#define BMP_PADDING_PER_ROW (4-((BMP_DATABYTES_PER_ROW)%4))
//runs slow, but time is money; better to write own / modify BMP library to auto-do this
int BMP_Data_To_Packed_RGB(BMP *bmp, void **rgb, unsigned long *size) {
	unsigned long i, rgb_offset, bmp_offset;
	//size is bmp data size, minus padding
		//padding is n_rows*padding_per_row
		//padding_per_row is (bit_depth>>3*width)%4
		//n_rows is height
	*size = bmp->Header->ImageDataSize - bmp->Header->Height*BMP_PADDING_PER_ROW;
	*rgb = malloc(*size); //opportunity to error-check
	for (i=rgb_offset=bmp_offset=0;
		i<bmp->Header->Height;
		i++, rgb_offset+=BMP_DATABYTES_PER_ROW, bmp_offset=BMP_PADDING_PER_ROW
	) memcpy(*rgb+rgb_offset, bmp->Data+bmp_offset, BMP_COLORBYTES_PER_ROW);
	return 0;
}
int RGB_From_BMP_File(const char *filename, void **rgb, unsigned long *size) {
	BMP *bmp;
	bmp = BMP_ReadFile(filename);
	return int BMP_Data_To_Packed_RGB(bmp, rgb, size);
}