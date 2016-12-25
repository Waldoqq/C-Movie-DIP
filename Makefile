# William Scotten's code 

CC     = gcc
DEBUG  = -g -DDEBUG
CFLAGS = -ansi -Wall -c
LFLAGS = -Wall

VIDEO = out.yuv

DESIGN = MovieLab MovieLabTest
OBJS = MovieLab.o FileIO.o DIPs.o Image.o ImageList.o Movie.o
DEBUG_OBJS = MovieLab_DEBUG.o FileIO_DEBUG.o DIPs_DEBUG.o Image_DEBUG.o ImageList_DEBUG.o Movie_DEBUG.o
DEPS = Image.h ImageList.h FileIO.h DIPs.h Movie.h Constants.h

all: $(DESIGN)

MovieLab: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o MovieLab

MovieLabTest: $(DEBUG_OBJS)
	$(CC) $(LFLAGS) $(DEBUG) $(DEBUG_OBJS) -o MovieLabTest

########### generate object files ###########
MovieLab.o: MovieLab.c $(DEPS)
	$(CC) $(CFLAGS) MovieLab.c -o MovieLab.o

FileIO.o: FileIO.c FileIO.h Image.h
	$(CC) $(CFLAGS) FileIO.c -o FileIO.o

DIPs.o: DIPs.c DIPs.h Image.h
	$(CC) $(CFLAGS) DIPs.c -o DIPs.o

Image.o: Image.c Image.h
	$(CC) $(CFLAGS) Image.c -o Image.o

ImageList.o: ImageList.c ImageList.h
	$(CC) $(CFLAGS) ImageList.c -o ImageList.o

Movie.o: Movie.c Movie.h
	$(CC) $(CFLAGS) Movie.c -o Movie.o

MovieLab_DEBUG.o: MovieLab.c $(DEPS)
	$(CC) $(CFLAGS) $(DEBUG) MovieLab.c -o MovieLab_DEBUG.o

FileIO_DEBUG.o: FileIO.c FileIO.h Image.h
	$(CC) $(CFLAGS) $(DEBUG) FileIO.c -o FileIO_DEBUG.o

DIPs_DEBUG.o: DIPs.c DIPs.h Image.h
	$(CC) $(CFLAGS) $(DEBUG) DIPs.c -o DIPs_DEBUG.o

Image_DEBUG.o: Image.c Image.h
	$(CC) $(CFLAGS) $(DEBUG) Image.c -o Image_DEBUG.o

ImageList_DEBUG.o: ImageList.c ImageList.h 
	$(CC) $(CFLAGS) $(DEBUG) ImageList.c -o ImageList_DEBUG.o

Movie_DEBUG.o: Movie.c Movie.h
	$(CC) $(CFLAGS) $(DEBUG) Movie.c -o Movie_DEBUG.o

clean:
	rm -f *.o $(DESIGN) $(VIDEO) out.yuv
