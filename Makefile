#hand-written Makefile, because I'm cool like that B)

#fefault target executed when no arguments are given to make
default_target: all
#specify as phony since "all" isn't a file, we don't want to check its existence or produce it as output
.PHONY : default_target

#specify library and header paths
#PNG_LIBDIR = /path/to/dir/containing/.so/or/.a/files
PNG_LIBDIR = .
PNG_LIB_FILE = NAME_OF_FILE
#PNG_HDIR = /path/to/dir/containing/.h/files
PNG_HDIR = ./libspng-0.7.1/spng
BMP_LIBDIR = ./qdbmp_1.0.0
BMP_LIB_FILE = qdbmp.o
BMP_SRC_FILE = qdbmp.c
BMP_HDIR = ./qdbmp_1.0.0

#source/include dirs
SDIR = ./src
IDIR = ./src

#build dir
BDIR = ./build

#flags
CC = gcc
CINCL = -I$(PNG_HDIR) -I$(BMP_HDIR) -I$(IDIR)
CLIBS = -L$(PNG_LIBDIR)
CFLAGS = $(CINCL) $(CLIBS) -g

#target lists
#LIB_TARGETS = pnglib bmplib
#LIB_TARGETS = pnglib
LIB_TARGETS = bmplib
SRC_TARGETS = image algos main

all: $(LIB_TARGETS) $(SRC_TARGETS)

main: algos
	$(CC) $(CFLAGS) $(SDIR)/hacstego.c $(BDIR)/image.o $(BDIR)/algos.o -o $(BDIR)/hacstego.x
	
algos: image
	$(CC) $(CFLAGS) -c $(SDIR)/algos.c -o $(BDIR)/algos.o
image: $(LIB_TARGETS)
	$(CC) $(CFLAGS) -c $(SDIR)/image.c $(BMP_LIBDIR)/$(BMP_LIB_FILE) -o $(BDIR)/image.o

pnglib: $(PNG_LIBDIR)/$(PNG_LIB_FILE)
#not specifying how to make it cuz scary

bmplib:
	$(CC) $(CFLAGS) -c $(BMP_LIBDIR)/$(BMP_SRC_FILE) -o $(BMP_LIBDIR)/$(BMP_LIB_FILE)