#include <unistd.h>

#include "algos.h"
#include "image.h"

#define BUFFER_SIZE_BITS 8
#define N_LSB_FLAG(n) nLSB_flag(n)
#define N_MSB_FLAG(n) nMSB_flag(n)
#define LSB_FLAG 1
#define MSB_FLAG 255
#define NO_FLAG 0


int writeBufferToFile(int fd, char buffer) {
    int bufferSizeBytes = BUFFER_SIZE_BITS / 8;
    return write(fd, &buffer, bufferSizeBytes) == bufferSizeBytes;
}

int fB(int fd, struct PixelData *pd, unsigned char *flags) {
    unsigned char* data = (unsigned char*) pd->data;
    unsigned char buffer = 0, bufferLoad = 0, twoBytes, channelVal, leftPad = 0,
                  rightPad, channelBitDepth, flag, bitIsEncoded, encodedBit;
    for (unsigned long pixelNum = 0; pixelNum < pd->nPixels; pixelNum++) {
        for (unsigned char channelNum = 0; channelNum < pd->nChannels; channelNum++) {
            channelBitDepth = pd->channelBitDepths[channelNum];
            flag = flags[channelNum];
            rightPad = MAX_CHANNEL_BIT_DEPTH * 2 - channelBitDepth - leftPad;
            twoBytes = *((unsigned short *) data);
            channelVal = (unsigned char) (twoBytes << leftPad) >> rightPad;
            for (unsigned char bitNum = 0; bitNum < MAX_CHANNEL_BIT_DEPTH; bitNum++) {
                bitIsEncoded = flag & 1;
                if (bitIsEncoded) {
                    encodedBit = channelVal & 1;
                    buffer <<= 1;
                    buffer += encodedBit;
                    bufferLoad++;
                    if (bufferLoad == BUFFER_SIZE_BITS) {
                        if (!writeBufferToFile(fd, buffer)) return 0;
                        bufferLoad = 0;
                    }
                }
                flag >>= 1;
                channelVal >>= 1;
            }
            data += (rightPad + channelBitDepth) / BUFFER_SIZE_BITS;
            leftPad = (rightPad + channelBitDepth) % BUFFER_SIZE_BITS;
        }
    }
    if (bufferLoad != 0) {
        buffer <<= BUFFER_SIZE_BITS - bufferLoad;
        if (!writeBufferToFile(fd, buffer)) return 0;
    }
    return 1;
}

unsigned char nLSB_flag(unsigned char nBits) {
    unsigned char flag = (unsigned char) -1;
    for (unsigned char i = 0; i < 8 - nBits; i++) {
        flag >>= 1;
    }
    return flag;
}

unsigned char nMSB_flag(unsigned char nBits) {
    unsigned char flag = (unsigned char) -1;
    for (unsigned char i = 0; i < nBits; i++) {
        flag <<= 1;
    }
    return flag;
}


int fB_Red(int fd, struct PixelData *pd, unsigned char flag) {
    unsigned char flags[] = {NO_FLAG, NO_FLAG, flag};
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


int fB_Blue(int fd, struct PixelData *pd, unsigned char flag) {
    unsigned char flags[] = {flag, NO_FLAG, NO_FLAG};
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


int fB_Green(int fd, struct PixelData *pd, unsigned char flag) {
    unsigned char flags[] = {NO_FLAG, flag, NO_FLAG};
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


int fB_RGB(int fd, struct PixelData *pd, unsigned char flag) {
    unsigned char flags[] = {flag, flag, flag};
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
