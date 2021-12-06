#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "image.h"
#include "algos.h"

int main(int argc, char**argv) {
	struct PixelData *pDat;
	char *outfilename;
	int fd;
	unsigned char do_R, do_G, do_B;
	channel a = 5, flag;
	/*
	a = (channel) test1();
	printf("test1: %d\n", a);
	//a = (channel) test3(); //there's is literally broken lmao, so much for their, yknow, everything...
	//printf("test3: %d\n", a);
	a = (channel) test4();
	printf("test4: %d\n", a);
	a = (channel) test5();
	printf("test5: %d\n", a);
	a = (channel) test6();
	printf("test6: %d\n", a);
	*/
	
	//args: <bin_name> s:filename.bmp b:R b:G b:B x:flag
	/*if (argc != 6) {
		printf("format: <bin_name> s:filename.bmp b:R b:G b:B hx:flag\n");
		return 1;
	}
	sscanf(argv[2], "%c", &do_R);
	sscanf(argv[3], "%c", &do_G);
	sscanf(argv[4], "%c", &do_B);
	*/
	
	//args: <bin_name> s:algo s:filename.bmp x:arg
		//arg is FLAG or N or 0, but always provide it!
	
	Pixel_Data_From_BMP_File(argv[2], &pDat);
	sscanf(argv[3], "%hhx", &flag);
	outfilename = malloc(strlen(argv[1])+strlen(argv[2])+2); //opportunity to error-check
	strcpy(outfilename, argv[2]);
	outfilename[strlen(argv[2])-4] = 0;
	strcat(outfilename, "_");
	strcat(outfilename, argv[1]);
	strcat(outfilename, ".bin");
	printf("outfilename: %s\n", outfilename);
	fd = open(outfilename, O_TRUNC | O_RDWR | O_CREAT);
	if (fd < 0) {
		printf("failed to open file, E:%d :(\n", fd);
		return fd;
	}
	//printf("%hhx\n", flag);
	
	if (strcmp(argv[1], "LSB_Red")) return LSB_Red(fd, pDat);
	else if (strcmp(argv[1], "nLSB_Red")) return nLSB_Red(fd, pDat, flag);
	else if (strcmp(argv[1], "fB_Red")) return fB_Red(fd, pDat, flag);
	else if (strcmp(argv[1], "MSB_Red")) return MSB_Red(fd, pDat);
	else if (strcmp(argv[1], "nMSB_Red")) return nMSB_Red(fd, pDat, flag);
	
	else if (strcmp(argv[1], "LSB_Green")) return LSB_Green(fd, pDat);
	else if (strcmp(argv[1], "nLSB_Green")) return nLSB_Green(fd, pDat, flag);
	else if (strcmp(argv[1], "fB_Green")) return fB_Green(fd, pDat, flag);
	else if (strcmp(argv[1], "MSB_Green")) return MSB_Green(fd, pDat);
	else if (strcmp(argv[1], "nMSB_Green")) return nMSB_Green(fd, pDat, flag);
	
	else if (strcmp(argv[1], "LSB_Blue")) return LSB_Blue(fd, pDat);
	else if (strcmp(argv[1], "nLSB_Blue")) return nLSB_Blue(fd, pDat, flag);
	else if (strcmp(argv[1], "fB_Blue")) return fB_Blue(fd, pDat, flag);
	else if (strcmp(argv[1], "MSB_Blue")) return MSB_Blue(fd, pDat);
	else if (strcmp(argv[1], "nMSB_Blue")) return nMSB_Blue(fd, pDat, flag);
	
	else if (strcmp(argv[1], "LSB_RGB")) return LSB_RGB(fd, pDat);
	else if (strcmp(argv[1], "nLSB_RGB")) return nLSB_RGB(fd, pDat, flag);
	else if (strcmp(argv[1], "fB_RGB")) return fB_RGB(fd, pDat, flag);
	else if (strcmp(argv[1], "MSB_RGB")) return MSB_RGB(fd, pDat);
	else if (strcmp(argv[1], "nMSB_RGB")) return nMSB_RGB(fd, pDat, flag);
	


	/*
	if (do_R || do_G || do_B) {
		if (do_R) {
			if (do_G && do_B) //RGB
			else if (!(do_G || do_B)) //R
			else return 2;
		}
		else if (do_G) {
			if (do_R && do_B) //RGB
			else if (!(do_R || do_B)) //G
			else return 2;
		}
		else if (do_B) {
			if (do_G && do_R) //RGB
			else if (!(do_G || do_R)) //B
			else return 2;
		}
	} else return 2;
	*/
	
	return 3;
}
