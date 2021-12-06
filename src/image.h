#ifndef HACSTEGO_IMAGES_H
#define HACSTEGO_IMAGES_H

#define PNG_MAGIC_SIZE 8
#define MAX_CHANNELS 5
#define MAX_CHANNEL_BIT_DEPTH 8

typedef unsigned char channel;

struct PixelData {
	void* data;
	unsigned char channelBitDepths[MAX_CHANNELS];
	unsigned char nChannels;
	unsigned long nPixels;
};
struct Pixel {
	channel red, green, blue, c4, c5;
};

int Pixel_Data_From_BMP_File(const char *filename, struct PixelData **pDat);

int test1();
int test2();
int test3();
int test4();
int test5();
int test6();

#endif
