/* Movie.c */
/* William Scotten's code */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "DIPs.h"
#include "Movie.h"

int clip(int x)
{	x = ((x > 255) ? 255 : (x < 0) ? 0 : x);
	return x;
}

/* Allocate the memory space for the movie and the memory space */
/* for the frame list. Return the pointer to the movie. */
MOVIE *CreateMovie(void)
{
	MOVIE *movie;
	movie = malloc(sizeof(MOVIE));
	if (! movie)
		{ perror("Out of memory!  Aborting...");
		exit(10);}
	movie->Frames = NULL;
	return movie;
}
/* Release the memory space for the frame list. */
/* Release the memory space for the movie. */
void DeleteMovie(MOVIE *movie)
{
	assert(movie);
	assert(movie->Frames);
	DeleteImageList(movie->Frames);
	movie->Frames = NULL;
	free(movie);
}
/* Convert a YUV movie to a RGB movie */
void YUV2RGBMovie(MOVIE *movie)
{
	int x, y;
	int C, D, E, R, G, B, Y, U, V;
	IENTRY *curr;
        curr = movie->Frames->First;
	while (curr != NULL) {
		curr->RGBImage = CreateImage(curr->YUVImage->Width, curr->YUVImage->Height);
		for (y = 0; y < curr->YUVImage->Height; y++) {
                        for (x = 0; x < curr->YUVImage->Width; x++) { 
				Y = GetPixelY(curr->YUVImage, x, y);
				U = GetPixelU(curr->YUVImage, x, y);
				V = GetPixelV(curr->YUVImage, x, y);
				C = Y - 16;
				D = U - 128;
				E = V - 128;
				R = clip(( 298 * C + 409 * E + 128) >> 8);
				G = clip(( 298 * C - 100 * D - 208 * E + 128) >> 8);
				B = clip(( 298 * C + 516 * D + 128) >> 8);
				SetPixelR(curr->RGBImage, x, y, R);
				SetPixelG(curr->RGBImage, x, y, G);
				SetPixelB(curr->RGBImage, x, y, B);
			}
		}
		DeleteYUVImage(curr->YUVImage);
		curr->YUVImage = NULL;
		curr = curr-> Next;
	}
}
/* Convert a RGB movie to a YUV movie */
void RGB2YUVMovie(MOVIE *movie)
{
        int x, y;
        int R, G, B, Y, U, V;
        IENTRY *curr;
	assert(movie->Frames->First);
        curr = movie->Frames->First;
        while (curr != NULL) {
		curr->YUVImage = CreateYUVImage(curr->RGBImage->Width, 
						curr->RGBImage->Height);
                for (y = 0; y < curr->YUVImage->Height; y++) {
                        for (x = 0; x < curr->YUVImage->Width; x++) {
				R = GetPixelR(curr->RGBImage, x, y);
				G = GetPixelG(curr->RGBImage, x, y);
				B = GetPixelB(curr->RGBImage, x, y);
                                Y = clip( ( ( 66 * R + 129 * G + 25 * B + 128) >> 8) + 16 );
				U = clip( ( ( -38 * R - 74 * G + 112 * B + 128) >> 8) + 128 );
				V = clip( ( ( 112 * R - 94 * G - 18 * B + 128) >> 8) + 128 );
                                SetPixelY(curr->YUVImage, x, y, Y);
                                SetPixelU(curr->YUVImage, x, y, U);
                                SetPixelV(curr->YUVImage, x, y, V);
                        }
                }
		DeleteImage(curr->RGBImage);
		curr->RGBImage = NULL;
                curr = curr->Next;
       } 
}

