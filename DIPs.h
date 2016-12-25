/* DIPs.h */
/* William Scotten's code */


#ifndef DIPS_H_INCLUDED_
#define DIPS_H_INCLUDED_


#include "Image.h"
#include "Constants.h"


/* Aging */
IMAGE *Aging(IMAGE *image);


/* GOOD */
/* Horizontal flip */
IMAGE *HFlip(IMAGE *image);


/* GOOD */
/* Edge detection */ 
IMAGE *Edge(IMAGE *image);

/* Add a watermark to an image */
IMAGE *Watermark(IMAGE *image, const IMAGE *watermark,
unsigned int topLeftX, unsigned int topLeftY);

/* Spotlight */
IMAGE *Spotlight(IMAGE *image, int centerX, int centerY, unsigned int radius);

/* GOOD */
/* Zoom an image */
IMAGE *Zoom(IMAGE *image, unsigned int percentage);

#endif /* DIPS_H_INCLUDED_ */
