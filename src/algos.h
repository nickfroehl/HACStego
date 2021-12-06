#ifndef HACSTEGO_ALGOS_H
#define HACSTEGO_ALGOS_H

//simple, 1 bit LSB for all red
void* LSB_Red(struct PixelData *pd);
//n bits LSB for all red
void* nLSB_Red(struct PixelData *pd, unsigned char nBits);
//data encoded in the ON bits of the flag for all red
void* fB_Red(struct PixelData *pd, unsigned char flag);
//simple, 1 bit MSB for all red
void* MSB_Red(struct PixelData *pd);
//n bits MSB for all red
void* nMSB_Red(struct PixelData *pd, unsigned char nBits);

//simple, 1 bit LSB for all blue
void* LSB_Blue(struct PixelData *pd);
//n bits LSB for all blue
void* nLSB_Blue(struct PixelData *pd, unsigned char nBits);
//data encoded in the ON bits of the flag for all blue
void* fB_Blue(struct PixelData *pd, unsigned char flag);
//simple, 1 bit MSB for all blue
void* MSB_Blue(struct PixelData *pd);
//n bits MSB for all blue
void* nMSB_Blue(struct PixelData *pd, unsigned char nBits);

//simple, 1 bit LSB for all green
void* LSB_Green(struct PixelData *pd);
//n bits LSB for all green
void* nLSB_Green(struct PixelData *pd, unsigned char nBits);
//data encoded in the ON bits of the flag for all green
void* fB_Green(struct PixelData *pd, unsigned char flag);
//simple, 1 bit MSB for all green
void* MSB_Green(struct PixelData *pd);
//n bits MSB for all green
void* nMSB_Green(struct PixelData *pd, unsigned char nBits);

//simple, 1 bit LSB for all RGB
void* LSB_RGB(struct PixelData *pd);
//n bits LSB for all RGB
void* nLSB_RGB(struct PixelData *pd, unsigned char nBits);
//data encoded in the ON bits of the flag for all RGB
void* fB_RGB(struct PixelData *pd, unsigned char flag);
//simple, 1 bit MSB for all RGB
void* MSB_RGB(struct PixelData *pd);
//n bits MSB for all RGB
void* nMSB_RGB(struct PixelData *pd, unsigned char nBits);

#endif
