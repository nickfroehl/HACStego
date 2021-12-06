#include <unistd.h>

#include "algos.h"
#include "image.h"
#include "errno.h"

#define BITS_PER_CHAR 8
#define BUFFER_SIZE_BITS BITS_PER_CHAR
#define ENCODED_ORDER 1 //1==MSB, 0==LSB

#define N_LSB_FLAG(n) nLSB_flag(n)
#define N_MSB_FLAG(n) nMSB_flag(n)
#define LSB_FLAG 1
#define MSB_FLAG 128 //this was incorrectly set to 255; once again saved by macros!
#define NO_FLAG 0
#define LSH1 <<=1
#define RSH1 >>=1

int writeBufferToFile(int fd, char buffer) {
	int bufferSizeBytes = BUFFER_SIZE_BITS / 8;
	return write(fd, &buffer, bufferSizeBytes) == bufferSizeBytes;
}

#define BITSKIP (leftPad + pd->channelBitDepths[channelNum])
#if ENCODED_ORDER == 1 //MSB
	#define CHANNEL_SH LSH1
	#define CHANNEL_MASK MSB_FLAG
#else
	#define CHANNEL_SH RSH1
	#define CHANNEL_MASK LSB_FLAG
#endif
#define BUFF_SH LSH1
int fB(int fd, struct PixelData *pd, channel *flags) {
	channel channelVal, flag, *data = (channel *) pd->data;
	unsigned short twoBytes;
	unsigned char buffer = 0, bufferLoad = 0, leftPad = 0, rightPad, bitIsEncoded, encodedBit;
	for (unsigned long pixelNum = 0; pixelNum < pd->nPixels; pixelNum++) {
		for (unsigned char channelNum = 0; channelNum < pd->nChannels; channelNum++) {
			flag = flags[channelNum];
			rightPad = MAX_CHANNEL_BIT_DEPTH * 2 - BITSKIP;
			//twoBytes = *((unsigned short *) data);
			twoBytes = (((unsigned short)data[0])<<BITS_PER_CHAR) + data[1];
			channelVal = (channel) ((twoBytes << leftPad) >> leftPad+rightPad);
			//should this loop not incorporate channelBitDepth?
			for (unsigned char bitNum = 0; bitNum < MAX_CHANNEL_BIT_DEPTH; bitNum++) {
				bitIsEncoded = flag & CHANNEL_MASK;
				if (bitIsEncoded) {
					encodedBit = channelVal & CHANNEL_MASK;
					buffer BUFF_SH;
					//buffer += encodedBit;
					//if non-zero, screw shifting, just inc
					if (encodedBit) buffer++;
					bufferLoad++;
					if (bufferLoad == BUFFER_SIZE_BITS) {
						if (!writeBufferToFile(fd, buffer)) return EBADWRITE;
						bufferLoad = 0;
					}
				}
				flag CHANNEL_SH;
				channelVal CHANNEL_SH;
			}
			data += (BITSKIP) / BUFFER_SIZE_BITS;
			leftPad = (BITSKIP) % BUFFER_SIZE_BITS;
		}
	}
	if (bufferLoad != 0) {
		buffer <<= BUFFER_SIZE_BITS - bufferLoad;
		if (!writeBufferToFile(fd, buffer)) return EBADWRITE;
	}
	return close(fd);
}

unsigned char nLSB_flag(unsigned char nBits) {
	channel flag = (channel) -1;
	for (unsigned char i = 0; i < 8 - nBits; i++) {
		flag >>= 1;
	}
	return flag;
}

unsigned char nMSB_flag(unsigned char nBits) {
	channel flag = (channel) -1;
	for (unsigned char i = 0; i < nBits; i++) {
		flag <<= 1;
	}
	return flag;
}


int fB_Red(int fd, struct PixelData *pd, channel flag) {
	channel flags[] = {NO_FLAG, NO_FLAG, flag};
	return fB(fd, pd, flags);
}

int LSB_Red(int fd, struct PixelData *pd) {
	return fB_Red(fd, pd, LSB_FLAG);
}

int nLSB_Red(int fd, struct PixelData *pd, unsigned char nBits) {
	return fB_Red(fd, pd, N_LSB_FLAG(nBits));
}

int MSB_Red(int fd, struct PixelData *pd) {
	return fB_Red(fd, pd, MSB_FLAG);
}

int nMSB_Red(int fd, struct PixelData *pd, unsigned char nBits) {
	return fB_Red(fd, pd, N_MSB_FLAG(nBits));
}


int fB_Blue(int fd, struct PixelData *pd, channel flag) {
	channel flags[] = {flag, NO_FLAG, NO_FLAG};
	return fB(fd, pd, flags);
}

int LSB_Blue(int fd, struct PixelData *pd) {
	return fB_Blue(fd, pd, LSB_FLAG);
}

int nLSB_Blue(int fd, struct PixelData *pd, unsigned char nBits) {
	return fB_Blue(fd, pd, N_LSB_FLAG(nBits));
}

int MSB_Blue(int fd, struct PixelData *pd) {
	return fB_Blue(fd, pd, MSB_FLAG);
}

int nMSB_Blue(int fd, struct PixelData *pd, unsigned char nBits) {
	return fB_Blue(fd, pd, N_MSB_FLAG(nBits));
}


int fB_Green(int fd, struct PixelData *pd, channel flag) {
	channel flags[] = {NO_FLAG, flag, NO_FLAG};
	return fB(fd, pd, flags);
}

int LSB_Green(int fd, struct PixelData *pd) {
	return fB_Green(fd, pd, LSB_FLAG);
}

int nLSB_Green(int fd, struct PixelData *pd, unsigned char nBits) {
	return fB_Green(fd, pd, N_LSB_FLAG(nBits));
}

int MSB_Green(int fd, struct PixelData *pd) {
	return fB_Green(fd, pd, MSB_FLAG);
}

int nMSB_Green(int fd, struct PixelData *pd, unsigned char nBits) {
	return fB_Green(fd, pd, N_MSB_FLAG(nBits));
}


int fB_RGB(int fd, struct PixelData *pd, channel flag) {
	channel flags[] = {flag, flag, flag};
	return fB(fd, pd, flags);
}

int LSB_RGB(int fd, struct PixelData *pd) {
	return fB_RGB(fd, pd, LSB_FLAG);
}

int nLSB_RGB(int fd, struct PixelData *pd, unsigned char nBits) {
	return fB_RGB(fd, pd, N_LSB_FLAG(nBits));
}

int MSB_RGB(int fd, struct PixelData *pd) {
	return fB_RGB(fd, pd, MSB_FLAG);
}

int nMSB_RGB(int fd, struct PixelData *pd, unsigned char nBits) {
	return fB_RGB(fd, pd, N_MSB_FLAG(nBits));
}
