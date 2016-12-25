#ifndef MOVIE_H_INCLUDED_
#define MOVIE_H_INCLUDED_


/* William Scotten's code */

#include "Image.h"
#include "Constants.h"
#include "ImageList.h"

/* the movie structure */
typedef struct {
ILIST *Frames; /* Pointer to the frame list */
} MOVIE;


/* Allocate the memory space for the movie and the memory space */
/* for the frame list. Return the pointer to the movie. */
MOVIE *CreateMovie(void);

/* Release the memory space for the frame list. */
/* Release the memory space for the movie. */
void DeleteMovie(MOVIE *movie);

/* Convert a YUV movie to a RGB movie */
void YUV2RGBMovie(MOVIE *movie);

/* Convert a RGB movie to a YUV movie */
void RGB2YUVMovie(MOVIE *movie);

/* Make sure image is between 0 and 255 */
int clip(int x);


#endif
