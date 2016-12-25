/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2016                     */
/*                                                                   */
/* Author: Guantao Liu                                               */
/* Date: 11/13/2016                                                  */
/*                                                                   */
/* MovieLab.c: source file for the main function                     */
/*                                                                   */
/* Please use this template for your HW5.                            */
/*********************************************************************/

/* William Scotten's code */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#include "FileIO.h"
#include "DIPs.h"
#include "Movie.h"
#include "Image.h"

/* Load one movie frame from the input file */
YUVIMAGE* LoadOneFrame(const char* fname, int n, 
                       unsigned int width, unsigned height);

/* Load the movie frames from the input file */
MOVIE *LoadMovie(const char *fname, int frameNum,
                 unsigned int width, unsigned height);

/* Save the movie frames to the output file */
int SaveMovie(const char *fname, MOVIE *movie);

/* Print the command-line arguments usage of the program */
void PrintUsage();

int main(int argc, char *argv[])
{
	int x = 0;
	int xx;
	int i, ii;
	char *fin = NULL;
	unsigned int finLen = 0;
	char *fout = NULL;
	unsigned int foutLen = 0;
	char *t;
	MOVIE *movie = NULL;
	IENTRY *curr = NULL;
	IENTRY *currlast = NULL;
	int frame, frame2, frame3, width, height;
	int crop1, crop2;
	int factor;
	IMAGE *wmimage = NULL;
	char *wmin = NULL;
	unsigned int wminLen = 0;
	int xpos, ypos, radius, tempx, tempy, tempneg;
	int percent, temptemp;
	srand(time(NULL));
	/* the while loop to check options in the command line */
	while (x < argc) {
		/* the input file name */
		if (strcmp(argv[x], "-i") == 0) {
			if (x < argc - 1) {
				finLen = strlen(argv[x + 1]) + strlen(".yuv") + 1;
				fin = (char *)malloc(sizeof(char) * finLen);
				if (fin == NULL) {
					printf("Error in memory allocation for the input file name!\n");
					free(fout);
					return 5;
				}
				strcpy(fin, argv[x + 1]);
				strcat(fin, ".yuv");
			} /*fi*/
			else {
				printf("Missing argument for the input file name!\n");
				free(fin);
				free(fout);
				return 5;
			} /*esle*/
			x += 2;
			continue;
		} /*fi*/

		/* the output file name */
		if (strcmp(argv[x], "-o") == 0) {
			if (x < argc - 1) {
				foutLen = strlen(argv[x + 1]) + strlen(".yuv") + 1;
				fout = (char *)malloc(sizeof(char) *foutLen);
				if (fout == NULL) {
					printf("Error in memory allocation for the output file name!\n");
					free(fin);
					return 5;
				}
				strcpy(fout, argv[x + 1]);
				strcat(fout, ".yuv");
			} /*fi*/
			else {
				printf("Missing argument for the output file name!\n");
				free(fin);
				free(fout);
				return 5;
			} /*esle*/
			x += 2;
			continue;
		} /*fi*/
		
		/* number of frames */
       	        if (strcmp(argv[x], "-f") == 0) {
			if (x < argc - 1) {
				frame = atoi(argv[x+1]);
                	 	}
			else {
                                printf("Missing argument for the frame amount!\n");
                                free(fin);
                                free(fout);
                                return 5;
			}
			x+=2;
                        continue; 
                } /*fi*/
		
		/* Resolution */
                if (strcmp(argv[x], "-s") == 0) {
                        if (x < argc - 1) {
                                width = atoi(argv[x+1]);
                                t = strtok(argv[x+1],"x");
                                t = strtok(NULL, "x");
                                height = atoi(t);
				movie = LoadMovie(fin, frame, width, height);
                        	YUV2RGBMovie(movie);
                        	curr = movie->Frames->First;
				currlast = movie->Frames->Last;
                                }
                        else {
                                printf("Missing argument for the frame amount!\n");
                                free(fin);
                                free(fout);
                                return 5;
                        }
                        x+=2;
                        continue;
                } /*fi*/
		
		/* Aging */
		if (strcmp(argv[x], "-aging") == 0) {
			while (curr !=NULL)
				{
				curr->RGBImage = Aging(curr->RGBImage);
				curr = curr->Next;
				}
			printf("Operation Aging is done!\n");
			curr = movie->Frames->First;
			x+=1;
			continue;	
		}
		
		/* Edging */
                if (strcmp(argv[x], "-edge") == 0) {
                        while (curr !=NULL)
                                {
                                curr->RGBImage = Edge(curr->RGBImage);
                                curr = curr->Next;
                                }
                        printf("Operation Edge is done!\n");
			curr = movie->Frames->First;
                        x+=1;
                        continue;
		}
		/* HFlip */
                if (strcmp(argv[x], "-hflip") == 0) {
                        while (curr !=NULL)
                                {
                                curr->RGBImage = HFlip(curr->RGBImage);
                                curr = curr->Next;
                                }
                        printf("Operation HFlip is done!\n");
                        curr = movie->Frames->First;
			x+=1;
			continue;
		}
	
		/* Crop */
                if (strcmp(argv[x], "-crop") == 0) {
			if (x < argc - 1) {
                                crop1 = atoi(argv[x+1]);
                                t = strtok(argv[x+1],"-");
                                t = strtok(NULL, "-");
                                crop2 = atoi(t);	
				}
                        else {
                                printf("Missing argument for the crop amount!\n");
                                free(fin);
                                free(fout);
                                return 5;
                        }
			currlast = movie->Frames->Last;
			if (movie->Frames->Length > crop1 && movie->Frames->Length > crop2)
				CropImageList(movie->Frames, crop1, crop2);
			else 
				printf("Can't Crop image, crop paramters larger than movie frame size!\n");
			x+=2;
                        continue;
                }
	
		/* Fast Forward */
		if (strcmp(argv[x], "-fast") == 0) {
                        if (x < argc - 1) {
                                factor = atoi(argv[x+1]);
                                }
                        else {
                                printf("Missing argument for the Fast Forward Factor!\n");
                                free(fin);
                                free(fout);
                                return 5;
                        }
                        FastImageList(movie->Frames, factor);
                        x+=2;	
			continue;
                }
	
		/* Reverse */
                if (strcmp(argv[x], "-rvs") == 0) {
                        ReverseImageList(movie->Frames);
                        x+=1;
                        continue;
                }
		
		/* Watermark */
                if (strcmp(argv[x], "-watermark") == 0) {
                        if (x < argc - 1) {
                                wminLen = strlen(argv[x + 1]) + strlen(".ppm") + 1;
                                wmin = (char *)malloc(sizeof(char) * wminLen);
                                if (wmin == NULL) {
                                        printf("Error in memory allocation for the watermark file name!\n");
                                        free(fin);
					free(fout);
					return 5;
                                }
                                strcpy(wmin, argv[x + 1]);
                        }
                        else {
                                printf("Missing name of watermark image!\n");
                                free(fin);
                                free(fout);
                                return 5;
                        }
			frame2 = frame / WATERMARK_PER_FRAMES;
			frame3 = frame % WATERMARK_PER_FRAMES;
			wmimage = LoadImage(wmin);
			for(i = 0; i < frame2; i++){
				xpos = rand() % curr->RGBImage->Width;
                                ypos = rand() % curr->RGBImage->Height;
				for (ii = 0; ii < 15; ii++){
					curr->RGBImage = Watermark(curr->RGBImage, wmimage, xpos, ypos);
					if (curr->Next)
					curr = curr->Next;
					}
				}
			/* the final frames of image (% 15 remainder) */
			for (i=0; i <frame3; i++) {
				xpos = rand() % 25;
                                ypos = rand() % 25;
                                for (ii = 0; i < 15; i++){
                                        curr->RGBImage = Watermark(curr->RGBImage, wmimage, xpos, ypos);
                                        if (curr->Next)
					curr = curr->Next;
                                 	}
			}	
			printf("Operation Watermark is done!\n");
			free(wmin);
			DeleteImage(wmimage);
                        x+=2;
			continue;
                }
                /* Spotlight */
                if (strcmp(argv[x], "-spotlight") == 0) {
			if (x < argc - 1) {
                                radius = atoi(argv[x+1]);
                                }
                        else {
                                printf("Missing argument for the radius!\n");
                                free(fin);
                                free(fout);
                                return 5;
				}
			tempx = 0;
			tempy = 0;
			i = 0;
			tempneg = 0;
                        while(i < frame-1){
				while(tempy == curr->RGBImage->Height && tempx < curr->RGBImage->Width && tempneg == 0){
					for(tempx=tempx; tempx < curr->RGBImage->Width; tempx+=SPOTLIGHT_SPEED){
						curr->RGBImage = Spotlight(curr->RGBImage, tempx, tempy, radius);
						if(curr->Next){
							curr = curr->Next;
							tempy -=SPOTLIGHT_SPEED;
							i++;
							}
						else
                                                	break;
					}
				}
				while(tempy > 0 && tempx  == 0 && tempneg == 1){
                                        for(tempy=tempy; tempy > 0; tempy-=SPOTLIGHT_SPEED){
                                                curr->RGBImage = Spotlight(curr->RGBImage, tempx, tempy, radius);
                                                if(curr->Next){
							curr = curr->Next;
                                                	tempx +=SPOTLIGHT_SPEED;
                                                	i++;
                                                	}
						else
                                                	break;
                                        }
				}
				while(tempx == curr->RGBImage->Width && tempy > 0 && tempy < curr->RGBImage->Height && tempneg ==0){
					for(tempy=tempy; tempy >  0; tempy-=SPOTLIGHT_SPEED){
						curr->RGBImage = Spotlight(curr->RGBImage, tempx, tempy, radius);
						if(curr->Next){		
							curr = curr->Next;
                                                	tempx -=SPOTLIGHT_SPEED;
                                                	i++;
							}
						else
                                                	break;
					}
				}
				while(tempy == curr->RGBImage->Height && tempx < curr->RGBImage->Width && tempneg == 1){
                                        for(tempx=tempx; tempx >  0; tempx-=SPOTLIGHT_SPEED){
                                                curr->RGBImage = Spotlight(curr->RGBImage, tempx, tempy, radius);
                                                if(curr->Next){
							curr = curr->Next;
                                                	tempy -=SPOTLIGHT_SPEED;
                                                	i++;
							}
                                        	else
                                                	break;
					}
                                }
				while(tempy == 0 && tempx > 0 && tempx < curr->RGBImage->Width && tempneg == 0){
					for(tempx=tempx; tempx > 0; tempx-=SPOTLIGHT_SPEED){
						curr->RGBImage = Spotlight(curr->RGBImage, tempx, tempy, radius);
                                                if(curr->Next){
							curr = curr->Next;
                                	                tempy +=SPOTLIGHT_SPEED;
                        	                        i++;
							}
						else
                                                	break;
					}
				}
				while(tempy == 0 && tempx == curr->RGBImage->Width && tempneg == 0){
                                        for(tempx=tempx; tempy < curr->RGBImage->Height; tempy+=SPOTLIGHT_SPEED){
                                                curr->RGBImage = Spotlight(curr->RGBImage, tempx, tempy, radius);
                                                if(curr->Next){
                                        	        curr = curr->Next;
							tempx -=SPOTLIGHT_SPEED;
                         	                        i++;
                                                	}
                                                else
                                                	break;
                                        }
                                	tempneg = 1;
				}
				while(((tempx == 0 && tempy > 0 && tempy < curr->RGBImage->Height) || (tempx==0 && tempy ==0)) && tempneg == 0){
                                        for(tempy=tempy; tempy < curr->RGBImage->Height; tempy+=SPOTLIGHT_SPEED){
                                                curr->RGBImage = Spotlight(curr->RGBImage, tempx, tempy, radius);
                                                if(curr->Next){
                                                	curr = curr->Next;
                                                	tempx +=SPOTLIGHT_SPEED;
                                                	i++;
                                     	  	        }
                                                else
                                                	break;
                                        }
                                }
                        	while(tempy == 0 && tempx > 0 && tempx < curr->RGBImage->Width && tempneg == 1){
                                        for(tempx=tempx; tempx < curr->RGBImage->Width; tempx+=SPOTLIGHT_SPEED){
                                                curr->RGBImage = Spotlight(curr->RGBImage, tempx, tempy, radius);
                                                if(curr->Next){
                                        	        curr = curr->Next;
                                      	        	tempy +=SPOTLIGHT_SPEED;
                                                	i++;
                                        	        }
                                                else
                                 	               break;
                                        }
                                }
			while(tempy > 0 && tempx == curr->RGBImage->Width && tempneg == 1){
                                        for(tempy=tempy; tempy < curr->RGBImage->Height; tempy+=SPOTLIGHT_SPEED){
                                                curr->RGBImage = Spotlight(curr->RGBImage, tempx, tempy, radius);
                                                if(curr->Next){
                                                	curr = curr->Next;
                                                	tempx-=SPOTLIGHT_SPEED;
                                	                i++;
                                        	        }
                                                else
                         	                       break;
                                        }
                                }
			}
                        printf("Operation Spotlight is done!\n");
                        x+=2;
			continue;
                }	
			
			/* Zoom */
			if (strcmp(argv[x], "-zoom") == 0) {
			percent = 0;
			temptemp = 0;
			i = 0;
			while(i < frame-1){
				while (temptemp == 0){
					for(percent=percent; percent < ZOOM_FULL_SIZE; percent +=ZOOM_SPEED){	
                        			curr->RGBImage = Zoom(curr->RGBImage, percent);
						if(curr->Next){
							curr = curr->Next;
							i++;
							}
						else
							break;
					temptemp = 1;
					}
				}
				while (temptemp == 1){
					for(percent=percent; percent > 0; percent -=ZOOM_SPEED){
						curr->RGBImage = Zoom(curr->RGBImage, percent);
                                        	if(curr->Next){
							curr = curr->Next;
							i++;
							}
						else 	
							break;
						temptemp = 0;
					}
				}
			}
			printf("Operation Zoom is done!\n");
                        x+=1;
			continue;
                	}
			
		/* the help option */
		if (strcmp(argv[x], "-h") == 0) { 
			;PrintUsage();
			free(fin);
			free(fout);
			return 0;
		} /*fi*/

		x++;
	} /*elihw*/

	if (fin == NULL) {
		printf("Missing argument for the input file name!\n");
		PrintUsage();
		free(fin);
		free(fout);
		return 5;
	}

	if (fout == NULL) {
		printf("Missing argument for the output file name!\n");
		PrintUsage();
		free(fin);
		free(fout);
		return 5;
	}
	
	assert(movie);
        RGB2YUVMovie(movie);
        xx=SaveMovie(fout, movie);
	while(movie->Frames->First->Prev)
              movie->Frames->First = movie->Frames->First->Prev;
	movie->Frames->Last = currlast;
	while(movie->Frames->Last->Prev){
		movie->Frames->Last->Prev->Next = movie->Frames->Last;
		movie->Frames->Last = movie->Frames->Last->Prev;
		}
	movie->Frames->Last = currlast;
	free(fin);
	free(fout);
	fin = NULL;
	fout = NULL;
	DeleteMovie(movie);
	return 0;
}

void PrintUsage()
{
	printf("\nUsage: MovieLab -i <file> -o <file> -f <framenum> -s <WIDTHxHEIGHT> [options]\n"
	       "Options:\n"
	       "-aging                Activate the aging filter on every movie frame\n"
	       "-hflip                Activate horizontal flip on every movie frame\n"
	       "-edge                 Activate the edge filter on every movie frame\n"
	       "-crop <start-end>     Crop the movie frames from <start> to <end>\n"
	       "-fast <factor>        Fast forward the movie by <factor>\n"
	       "-rvs                  Reverse the frame order of the input movie\n"
	       "-watermark <file>     Add a watermark from <file> to every movie frame\n"
	       "-spotlight <radius>   Spotlight a circle of <radius> on every movie frame\n"
	       "-zoom                 Zoom in and out the input movie\n"
	       "-h                    Display this usage information\n"
	      );
}

/* Load one movie frame from the input file */
YUVIMAGE* LoadOneFrame(const char* fname, int n, 
                       unsigned int width, unsigned height)
{
	FILE *file;
	unsigned int x, y;
	unsigned char c;
	YUVIMAGE* YUVimage;

	/* Check errors */
	assert(fname);
	assert(n >= 0);

	YUVimage = CreateYUVImage(width, height);
	if (YUVimage == NULL) {
		return NULL;
	}

	/* Open the input file */
	file = fopen(fname, "r");
	if (file == NULL) {
		DeleteYUVImage(YUVimage);
		return NULL;
	}

	/* Find the desired frame */
	fseek(file, 1.5 * n * width * height, SEEK_SET);

	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			c = fgetc(file);
			SetPixelY(YUVimage, x, y, c);
		} /*rof*/
	}

	for (y = 0; y < height; y += 2) {
		for (x = 0; x < width; x += 2) {
			c = fgetc(file);
			SetPixelU(YUVimage, x, y, c);
			SetPixelU(YUVimage, x + 1, y, c);
			SetPixelU(YUVimage, x, y + 1, c);
			SetPixelU(YUVimage, x + 1, y + 1, c);
		}
	}

	for (y = 0; y < height; y += 2) {
		for (x = 0; x < width; x += 2) {
			c = fgetc(file);
			SetPixelV(YUVimage, x, y, c);
			SetPixelV(YUVimage, x + 1, y, c);
			SetPixelV(YUVimage, x, y + 1, c);
			SetPixelV(YUVimage, x + 1, y + 1, c);
		}
	}

	/* Check errors */
	assert(ferror(file) == 0);

	/* Close the input file and return */
	fclose(file);
	file = NULL;
	return YUVimage;
}

/* Load the movie frames from the input file */
MOVIE *LoadMovie(const char *fname, int frameNum,
                 unsigned int width, unsigned height)
{	MOVIE *movie = NULL;
	movie = CreateMovie();
	YUVIMAGE *YUVimage;
	ILIST *list;
	list = CreateImageList();
	int i;
	for (i = 0; i < frameNum; i++)
		{
		YUVimage = LoadOneFrame(fname, i, width, height);
		assert(YUVimage);
		AppendYUVImage(list, YUVimage);
		}
	movie->Frames = list;
	printf("The movie file %s has been read successfully!\n", fname);
	assert(movie);
	return movie;
}
/* Save the movie frames to the output file */
int SaveMovie(const char *fname, MOVIE *movie)
{
	int count; 
	int x, y;
	FILE *file;
	IENTRY *curr;

	/* Open the output file */
	file = fopen(fname, "w");
	if (file == NULL) {
		return 1;
	}
	 
	count = 0; 
	curr = movie->Frames->First;
	while (curr != NULL) {
		for (y = 0; y < curr->YUVImage->Height; y++) { 
			for (x = 0; x < curr->YUVImage->Width; x++) {
				fputc(GetPixelY(curr->YUVImage, x, y), file);
			}
		}

		for (y = 0; y < curr->YUVImage->Height; y += 2) { 
			for (x = 0; x < curr->YUVImage->Width; x += 2) {
				fputc(GetPixelU(curr->YUVImage, x, y), file);
			}
		}

		for (y = 0; y < curr->YUVImage->Height; y += 2) { 
			for (x = 0; x < curr->YUVImage->Width; x += 2) {
				fputc(GetPixelV(curr->YUVImage, x, y), file);
			}
		}
		
		curr = curr->Next;	 
		count++;
	}

	fclose(file);
	file = NULL;

	printf("The movie file %s has been written successfully!\n", fname);
	printf("%d frames are written to the file %s in total.\n", count, fname); 
	return 0;
}
/* EOF */
