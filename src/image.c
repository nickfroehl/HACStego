#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
	bmp = BMP_ReadFile("./images/tinier_primary.bmp");
	BMP_CHECK_ERROR( stderr, -1 ); /* If an error has occurred, notify and exit */

	/* Get image's dimensions */
	width = BMP_GetWidth( bmp );
	height = BMP_GetHeight( bmp );

	/* Iterate through all the image's pixels */
	for ( x = 0 ; x < width ; ++x ) {
		for ( y = 0 ; y < height ; ++y ) {
			/* Get pixel's RGB values */
			BMP_GetPixelRGB( bmp, x, y, &r, &g, &b );
			printf("(%ld,%ld): %x,%x,%x\n", x,y,r,g,b);
			/* Invert RGB values */
			//BMP_SetPixelRGB( bmp, y, x, 255 - r, 255 - g, 255 - b );
		}
	}

	/* Save result */
	//BMP_WriteFile( bmp, "./images/custom_inv.bmp" );
	BMP_CHECK_ERROR( stderr, -2 );

	/* Free all memory allocated for the image */
	BMP_Free( bmp );

	return 0;
}

int Packed_RGB_To_Pixel_Data(void *rgb, unsigned int size, BMP_Header *header, struct PixelData **pDat) {
	pDat = malloc(sizeof(struct PixelData)); //opportunity to error-check
	(*pDat)->data = rgb;
	
	if (header->BitsPerPixel == 8) {
		(*pDat)->channelBitDepths[0] = 3;
		(*pDat)->channelBitDepths[1] = 2;
		(*pDat)->channelBitDepths[2] = 3;
		(*pDat)->channelBitDepths[3] = 0;
		(*pDat)->channelBitDepths[4] = 0;
	} else if (header->BitsPerPixel == 16) {
		(*pDat)->channelBitDepths[0] = 5;
		(*pDat)->channelBitDepths[1] = 6;
		(*pDat)->channelBitDepths[2] = 5;
		(*pDat)->channelBitDepths[3] = 0;
		(*pDat)->channelBitDepths[4] = 0;
	} else if (header->BitsPerPixel == 16) {
		(*pDat)->channelBitDepths[0] = 5;
		(*pDat)->channelBitDepths[1] = 6;
		(*pDat)->channelBitDepths[2] = 5;
		(*pDat)->channelBitDepths[3] = 0;
		(*pDat)->channelBitDepths[4] = 0;
	} else return EINVAL_DEPTH;
	
	(*pDat)->nChannels = 3; //i think that's universal?
	(*pDat)->nPixels = (unsigned long) size / (header->BitsPerPixel>>3);
	
	return 0;
}

#define BMP_DATABYTES_PER_ROW (bmp->Header.Width*(bmp->Header.BitsPerPixel>>3))
#define BMP_PADDING_PER_ROW ((4-((BMP_DATABYTES_PER_ROW)%4))%4)
#define BMP_ROWWIDTH (BMP_DATABYTES_PER_ROW + BMP_PADDING_PER_ROW)
#define TOTAL_PADDING_BYTES (bmp->Header.Height*BMP_PADDING_PER_ROW)
int BMP_Data_To_Packed_RGB(BMP *bmp, void **rgb, unsigned int *size) {
	//TEMP: only supports 24 bit depth
		//but actually, should just... work, in general. only my printout was specific to 24 bit depth. heck yes!
	unsigned int i, rgb_offset, bmp_offset;
	//size is bmp data size, minus padding
		//padding is n_rows*padding_per_row
		//padding_per_row is (bit_depth>>3*width)%4
		//n_rows is height
	*size = bmp->Header.ImageDataSize - TOTAL_PADDING_BYTES;
	//printf("%u --> %u, because %u=%u*...\n", bmp->Header.ImageDataSize, *size, BMP_PADDING_PER_ROW, bmp->Header.Width);
	*rgb = malloc(*size); //opportunity to error-check
	printf("%lu-%lu = %lu = %lu*%u. %lu\n", BMP_ROWWIDTH, BMP_PADDING_PER_ROW, BMP_DATABYTES_PER_ROW, bmp->Header.Width, bmp->Header.BitsPerPixel>>3, bmp->Header.Height);
	for (i=0, /*rgb_offset=bmp->Header.Height*BMP_DATABYTES_PER_ROW,*/ bmp_offset=(bmp->Header.Height-1)*BMP_ROWWIDTH, rgb_offset=0;
		i<bmp->Header.Height;
		i++, rgb_offset+=BMP_DATABYTES_PER_ROW, bmp_offset-=BMP_ROWWIDTH
	) memcpy(*rgb+rgb_offset, bmp->Data+bmp_offset, BMP_DATABYTES_PER_ROW);
	return 0;
}

/*
int Packed_RGB_To_BMP_Data(BMP *bmp, void *rgb, unsigned int size, const char *pad_data, unsigned int pad_data_size) {
	//should? support non-24 bit depth just fine, so long as %8
	unsigned int i, rgb_offset, bmp_offset;//, pad_written;
	

	for (i=0, /*rgb_offset=bmp->Header.Height*BMP_DATABYTES_PER_ROW,*/ /*bmp_offset=(bmp->Header.Height-1)*BMP_ROWWIDTH, rgb_offset=0;
		i<bmp->Header.Height;
		i++, rgb_offset+=BMP_DATABYTES_PER_ROW, bmp_offset-=BMP_ROWWIDTH
	) {
		memcpy(bmp->Data+bmp_offset, *rgb+rgb_offset, BMP_DATABYTES_PER_ROW);
		if (pad_data_size >= BMP_PADDING_PER_ROW) {
			memcpy(bmp->Data+bmp_offset+BMP_DATABYTES_PER_ROW, , BMP_PADDING_PER_ROW);
			pad_data_size -= BMP_PADDING_PER_ROW;
		else if (pad_data_size) {
			memcpy(bmp->Data+bmp_offset+BMP_DATABYTES_PER_ROW, , pad_data_size);
			
			pad_data_size -= BMP_PADDING_PER_ROW;
			pad_data_size = 0;
		}
	}
	
}
*/
int RGB_From_BMP_File(const char *filename, void **rgb, unsigned int *size, BMP **bmp) {
	int res;
	*bmp = BMP_ReadFile(filename);
	res = BMP_Data_To_Packed_RGB(*bmp, rgb, size);
	return res;
}

int Pixel_Data_From_BMP_File(const char *filename, struct PixelData **pDat) {
	BMP *bmp;
	void *rgb;
	unsigned int size;
	RGB_From_BMP_File(filename, &rgb, &size, &bmp);
	Packed_RGB_To_Pixel_Data(rgb, size, &(bmp->Header), pDat);
	BMP_Free(bmp);
	return 0;
}

int test4() {
	BMP *bmp;
	unsigned char *rgb, depth;
	unsigned int size;
	UINT i, res;
	
	res = RGB_From_BMP_File( "./images/tinier_primary.bmp", &rgb, &size, &bmp );
	for (i=0; i<size; i+=3) printf("%x,%x,%x\n", rgb[i+2], rgb[i+1], rgb[i]);
	BMP_Free(bmp);
	return res;
}