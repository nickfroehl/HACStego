#include "image.h"

#ifndef HACSTEGO_ALGOS_H
#define HACSTEGO_ALGOS_H

//simple, 1 bit LSB for all red
int LSB_Red(int fd, struct PixelData *pd);
//n bits LSB for all red
int nLSB_Red(int fd, struct PixelData *pd, unsigned char nBits);
//data encoded in the ON bits of the flag for all red
int fB_Red(int fd, struct PixelData *pd, unsigned char flag);
//simple, 1 bit MSB for all red
int MSB_Red(int fd, struct PixelData *pd);
//n bits MSB for all red
int nMSB_Red(int fd, struct PixelData *pd, unsigned char nBits);

//simple, 1 bit LSB for all blue
int LSB_Blue(int fd, struct PixelData *pd);
//n bits LSB for all blue
int nLSB_Blue(int fd, struct PixelData *pd, unsigned char nBits);
//data encoded in the ON bits of the flag for all blue
int fB_Blue(int fd, struct PixelData *pd, unsigned char flag);
//simple, 1 bit MSB for all blue
int MSB_Blue(int fd, struct PixelData *pd);
//n bits MSB for all blue
int nMSB_Blue(int fd, struct PixelData *pd, unsigned char nBits);

//simple, 1 bit LSB for all green
int LSB_Green(int fd, struct PixelData *pd);
//n bits LSB for all green
int nLSB_Green(int fd, struct PixelData *pd, unsigned char nBits);
//data encoded in the ON bits of the flag for all green
int fB_Green(int fd, struct PixelData *pd, unsigned char flag);
//simple, 1 bit MSB for all green
int MSB_Green(int fd, struct PixelData *pd);
//n bits MSB for all green
int nMSB_Green(int fd, struct PixelData *pd, unsigned char nBits);

//simple, 1 bit LSB for all RGB
int LSB_RGB(int fd, struct PixelData *pd);
//n bits LSB for all RGB
int nLSB_RGB(int fd, struct PixelData *pd, unsigned char nBits);
//data encoded in the ON bits of the flag for all RGB
int fB_RGB(int fd, struct PixelData *pd, unsigned char flag);
//simple, 1 bit MSB for all RGB
int MSB_RGB(int fd, struct PixelData *pd);
//n bits MSB for all RGB
int nMSB_RGB(int fd, struct PixelData *pd, unsigned char nBits);

#endif
