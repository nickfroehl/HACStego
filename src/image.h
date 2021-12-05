#ifndef HACSTEGO_IMAGES_H
#define HACSTEGO_IMAGES_H

#define PNG_MAGIC_SIZE 8

typedef unsigned char channel;

struct PixelData {
	void* data;
	unsigned char bitDepth;
	unsigned char nChannels;
};
struct Pixel {
	channel red, green, blue, c4, c5;
};

int test();

#endif