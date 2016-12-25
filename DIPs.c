/* DIPs.c */
/* William Scotten's code */

#include <assert.h> /* assert */
#include <stdlib.h> /* NULL */
#include <stdio.h> /* printf */

#include "DIPs.h"
#include "Movie.h"

/* Aging */
IMAGE *Aging(IMAGE *image)
{
	int R, G, B;
	assert(image);
	int x, y;
	for(y = 0; y < image->Height; y ++ ) {
		for(x = 0; x < image->Width; x ++ ) {
			R = GetPixelR(image, x, y);
			G = GetPixelG(image, x, y);
			B = GetPixelB(image, x, y);
			B = (R + G + B) / 5;
			R = B * 1.6;
			G = B * 1.6;
			R = clip(R);
                        G = clip(G);
                        B = clip(B);
			SetPixelR(image, x, y, R);
			SetPixelG(image, x, y, G);
			SetPixelB(image, x, y, B);
		}
	}
	return image;
}
/* Add a watermark to an image */
IMAGE *Watermark(IMAGE *image, const IMAGE *watermark,
unsigned int topLeftX, unsigned int topLeftY)
{
	assert(image);
	assert(watermark);
	int R, G, B, RR, GG, BB;
	int x, y;
	for(y = 0; y < watermark->Height; y ++ ) {
                for(x = 0; x < watermark->Width; x ++ ) {
			R = GetPixelR(watermark, x, y);
			G = GetPixelG(watermark, x, y);
			B = GetPixelB(watermark, x, y);
			if( (R + G + B) == 0){
				if ((image->Width > x+topLeftX) && (image->Height > y+topLeftY)){ 
					RR = GetPixelR(image, x+topLeftX, y+topLeftY);
					GG = GetPixelG(image, x+topLeftX, y+topLeftY);
					BB = GetPixelB(image, x+topLeftX, y+topLeftY);
					RR = RR * WATERMARK_RATIO;
					GG = GG * WATERMARK_RATIO;
					BB = BB * WATERMARK_RATIO; 
					RR = clip(RR);
					GG = clip(GG);
					BB = clip(BB);
					SetPixelR(image, x+topLeftX, y+topLeftY, RR);	
					SetPixelG(image, x+topLeftX, y+topLeftY, GG);
					SetPixelB(image, x+topLeftX, y+topLeftY, BB);
				}
			}
		}	
	}
	return image;
}
/* Spotlight */
IMAGE *Spotlight(IMAGE *image, int centerX, int centerY, unsigned int radius)
{
	assert(image);
	int x, y;
	for(y = 0; y < (image->Height); y++ ) {
                for(x = 0; x < (image->Width); x++ ) {
			if((x-centerX)*(x-centerX) + (y-centerY)*(y-centerY) <= radius*radius)
			continue;
			else {
			SetPixelR(image, x, y, 0);
			SetPixelG(image, x, y, 0);
			SetPixelB(image, x, y, 0);
			}
		}
	}
	return image;
}

IMAGE *Edge(IMAGE *image) {

	int R, G, B;
	int A, BB, C, D, E, F, GG, H;
        assert(image);
        int x, y;
	IMAGE *tmpimage;
	tmpimage = CreateImage(image->Width,image->Height);
	assert(tmpimage);
	for(y = 0; y < (image->Height); y++ ) {
                for(x = 0; x < (image->Width); x++ ) {
			R = GetPixelR(image, x, y);
                        G = GetPixelG(image, x, y);
                        B = GetPixelB(image, x, y);
			SetPixelR(tmpimage, x, y, R);
                        SetPixelG(tmpimage, x, y, G);
                        SetPixelB(tmpimage, x, y, B);
		}
	}
	/* Set borders to black */

	for(x=0; x < image->Width; x++) 
		{SetPixelR(image, x, 0, 0);
		SetPixelG(image, x, 0, 0);
		SetPixelB(image, x, 0, 0);
		SetPixelR(image, x, image->Height-1, 0);
		SetPixelG(image, x, image->Height-1, 0);
		SetPixelB(image, x, image->Height-1, 0);
		}
	for(y=0; y < image->Height; y++)
		{
		SetPixelR(image, 0, y, 0);
		SetPixelG(image, 0, y, 0);
		SetPixelB(image, 0, y, 0);
		SetPixelR(image, image->Width-1, y, 0);
                SetPixelG(image, image->Width-1, y, 0);
                SetPixelB(image, image->Width-1, y, 0);					
		}
	/* Set Nonborder pixels */
        for(y = 1; y < (image->Height-1); y++ ) {
                for(x = 1; x < (image->Width-1);x++ ) {
                        R = GetPixelR(tmpimage, x, y);
                        G = GetPixelG(tmpimage, x, y);
                        B = GetPixelB(tmpimage, x, y);
			
			/* R value */			
			
			A = GetPixelR(tmpimage, x-1, y-1);
			BB = GetPixelR(tmpimage, x, y-1);
                        C = GetPixelR(tmpimage, x+1, y-1);
                        D = GetPixelR(tmpimage, x-1, y);
                        E = GetPixelR(tmpimage, x+1, y);
                        F = GetPixelR(tmpimage, x-1, y+1);
                        GG = GetPixelR(tmpimage, x, y+1);
                        H = GetPixelR(tmpimage, x+1, y+1);
			R = (8*R-A-BB-C-D-E-F-GG-H);
			R = clip(R);
                        SetPixelR(image, x, y, R);

			/* G value */

                        A = GetPixelG(tmpimage, x-1, y-1);
                        BB = GetPixelG(tmpimage, x, y-1);
                        C = GetPixelG(tmpimage, x+1, y-1);
                        D = GetPixelG(tmpimage, x-1, y);
                        E = GetPixelG(tmpimage, x+1, y);
                        F = GetPixelG(tmpimage, x-1, y+1);
                        GG = GetPixelG(tmpimage, x, y+1);
                        H = GetPixelG(tmpimage, x+1, y+1);
                        G = (8*G-A-BB-C-D-E-F-GG-H);
			G = clip(G);
                        SetPixelG(image, x, y, G);

			/* B value */

                        A = GetPixelB(tmpimage, x-1, y-1);
                        BB = GetPixelB(tmpimage, x, y-1);
                        C = GetPixelB(tmpimage, x+1, y-1);
                        D = GetPixelB(tmpimage, x-1, y);
                        E = GetPixelB(tmpimage, x+1, y);
                        F = GetPixelB(tmpimage, x-1, y+1);
                        GG = GetPixelB(tmpimage, x, y+1);
                        H = GetPixelB(tmpimage, x+1, y+1);
                        B = (8*B-A-BB-C-D-E-F-GG-H);
			B = clip(B);
                        SetPixelB(image, x, y, B);
                }
        }
	DeleteImage(tmpimage);
	tmpimage = NULL;
	return image;
}

IMAGE *HFlip(IMAGE *image) {
        int x, y, xx;
        xx= image->Width;
        unsigned char R, G, B;
        IMAGE *tmpimage;
        tmpimage = CreateImage(image->Width,image->Height);
        assert(tmpimage);
        for(y = 0; y < (image->Height); y++ ) {
                for(x = 0; x < (image->Width); x++ ) {
                        R = GetPixelR(image, x, y);
                        G = GetPixelG(image, x, y);
                        B = GetPixelB(image, x, y);
                        SetPixelR(tmpimage, x, y, R);
                        SetPixelG(tmpimage, x, y, G);
                        SetPixelB(tmpimage, x, y, B);
                }      
 	}
        for(y = 0; y <image->Height; y++ ) {
                for(x = 0; x < image->Width; x++) {
                        R = GetPixelR(tmpimage, x, y);
                        G = GetPixelG(tmpimage, x, y);
                        B = GetPixelB(tmpimage, x, y);
                        SetPixelR(image,(xx-x-1), y, R);
                        SetPixelG(image,(xx-x-1), y, G);
                        SetPixelB(image,(xx-x-1), y, B);
                        }
                }
	DeleteImage(tmpimage);
	tmpimage = NULL;
	return image;
}


IMAGE *Zoom(IMAGE *image, unsigned int percentage) {
	assert(image);
	if(percentage < 0 || percentage > ZOOM_FULL_SIZE){
        	printf("Resizing percentage %d%% should be in [0, ZOOM_FULL_SIZE], operation canceled \n", percentage);
        	return image;
		}
	if (percentage == ZOOM_FULL_SIZE) 
		return image;
	int x, y, x1, y1, x2, y2, i, j, tmpR, tmpG, tmpB;
	const int NEW_WIDTH = image->Width * percentage / 100;
    	const int NEW_HEIGHT = image->Height * percentage / 100;
	IMAGE *image_tmp = CreateImage(image->Width, image->Height);
	if (!image_tmp) return image;
	for(x = 0; x < image->Width; x ++){
                for(y = 0; y < image->Height; y++){
			SetPixelR(image_tmp, x, y, 0);
			SetPixelG(image_tmp, x, y, 0);
			SetPixelB(image_tmp, x, y, 0);
		}
	}
	for(x = 0; x < NEW_WIDTH; x ++){
        	for(y = 0; y < NEW_HEIGHT; y++){
			x1 = (int)(x / (percentage / 100.00));
                	y1 = (int)(y / (percentage / 100.00));
                	x2 = (int)((x + 1) / (percentage / 100.00));
                	y2 = (int)((y + 1) / (percentage / 100.00));
                	tmpR = tmpB = tmpG = 0;
                	for(i = x1; i < x2; i ++){
                   		for(j = y1; j < y2; j ++){
                        		tmpR += GetPixelR(image, i, j); 
                        		tmpG += GetPixelG(image, i, j); 
                        		tmpB += GetPixelB(image, i, j); 
                   		 }   
                	}
		
		SetPixelR(image_tmp, x, y, tmpR / ((x2 - x1) * (y2 - y1)));
                SetPixelG(image_tmp, x, y, tmpG / ((x2 - x1) * (y2 - y1)));
                SetPixelB(image_tmp, x, y, tmpB / ((x2 - x1) * (y2 - y1)));
            }   
        }
  	DeleteImage(image);
	image = NULL;
	return image_tmp;
}
