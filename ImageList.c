/* ImageList.c */
/* William Scotten's code */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Image.h"
#include "ImageList.h"

/* Create a new image list */
ILIST *CreateImageList(void)
{
	/* Ilist */
	ILIST *list;
	list = malloc(sizeof(ILIST));
	if (! list)
		{ perror("Out of memomry!  Aborting...");
		exit(10);}
	list->Length = 0;
	list->First = NULL;
	list->Last = NULL;
	assert(list);
	return list;
	
}
/* Delete an image list (and all entries) */
void DeleteImageList(ILIST *list)
{
	IENTRY *x, *y;
	assert(list);
	assert(list->Length);
	assert(list->First);
	assert(list->Last);
	x = list->First;
	while(x){
		y = x->Next;
		if (x->RGBImage)
			DeleteImage(x->RGBImage);
		
		else {
			assert(x->YUVImage);
			DeleteYUVImage(x->YUVImage);
		}
		free(x);
		x = y;
	}
	list->Length = 0;
	list->First = NULL;
	list->Last = NULL;
	free(list);
}
/* Insert a RGB image to the image list at the end */
void AppendRGBImage(ILIST *list, IMAGE *RGBimage)
{
        IENTRY *ientryRGB = NULL;
        assert(list);
        assert(RGBimage);
        ientryRGB=malloc(sizeof(IENTRY));
        if (! ientryRGB)
        { perror("Out of memory! Aborting...");
          exit(10); }
        ientryRGB->List = NULL;
        ientryRGB->Next = NULL;
        ientryRGB->Prev = NULL;
        ientryRGB->RGBImage=RGBimage;
        ientryRGB->YUVImage=NULL;
        if (list->Last)
        	{
	        ientryRGB->List = list;
        	ientryRGB->Next = list->First;
	        ientryRGB->Prev = list->Last;
        	list->Last->Next = ientryRGB;
	        list->Last = ientryRGB;
        	}
        else
	        {
       		ientryRGB->List = list;
	        ientryRGB->Next = NULL;
        	ientryRGB->Prev = NULL;
	        list->First = ientryRGB;
        	list->Last = ientryRGB;
        	}
        list->Length++;	        
}

/* Insert a YUV image to the image list at the end */
void AppendYUVImage(ILIST *list, YUVIMAGE *YUVimage)
{
        IENTRY *ientryYUV = NULL;
        assert(list);
        assert(YUVimage);
        ientryYUV = malloc(sizeof(IENTRY));
        if (! ientryYUV)
        { perror("Out of memory! Aborting...");
          exit(10); }
        ientryYUV->List = NULL;
        ientryYUV->Next = NULL;
        ientryYUV->Prev = NULL;
        ientryYUV->YUVImage=YUVimage;
        ientryYUV->RGBImage=NULL;
        if (list->Last)
        {
        ientryYUV->List = list;
        ientryYUV->Next = NULL;
        ientryYUV->Prev = list->Last;
        list->Last->Next = ientryYUV;
        list->Last = ientryYUV;
        }
        else
        {
        ientryYUV->List = list;
        ientryYUV->Next = NULL;
        ientryYUV->Prev = NULL;
        list->First = ientryYUV;
        list->Last = ientryYUV;
        }
        list->Length++;

}
/* Crop an image list */
void CropImageList(ILIST *list, unsigned int start, unsigned int end)
{
	assert(list);
	int i, temp;
	temp = list->Length - 1 - end;
	for (i = 0; i < start; i++){
		list->First = list->First->Next;	
		list->Length--;
		}
	for (i = 0; i < temp; i++) {
		list->Last = list->Last->Prev;
		list->Length--;
		}
	list->Last->Next = NULL;
	i = end-start+1;
	printf("Operation Crop is done! New number of frames is %d\n", list->Length);
}
/* Fast forward an image list */
void FastImageList(ILIST *list, unsigned int factor)
{
	assert(list);
	ILIST *listtemp;
	listtemp = CreateImageList();
	int i, ii;
	listtemp->First = list->First;
	listtemp->Length = list->Length;
	if (factor > 1)
		{
		for (i = 0; i < listtemp->Length/(factor); i++){
			for (ii = 0; ii < (factor-1); ii++){
				if (list->First->Next->Next){
					list->First->Next = list->First->Next->Next;
					list->Length--;
					}
				else {
				break;
				}
			}
			list->First = list->First->Next;
		}
	}
	list->First = listtemp->First;
	free(listtemp);
	printf("Operation Fast Forward is done! New number of frames is %d\n", list->Length);
}
/* Reverse an image list */
void ReverseImageList(ILIST *list)
{
	assert(list);
	int i;
	ILIST *listtemp;
	listtemp = CreateImageList();
	listtemp->First = list->First;
	listtemp->First->Next = list->First->Next;
	listtemp->Last = list->Last;
	listtemp->Length = list->Length;

	list->First = list->Last;
	list->First->Next = list->First->Prev;
	list->First->Prev = NULL;
	
	list->Last = listtemp->First;
	list->Last->Prev = list->Last->Next;
	list->Last->Next = NULL;

	list->First = list->First->Next;

	for (i = 0; i < list->Length-2; i++){
		list->First->Next = list->First->Prev;
		list->First = list->First->Next;
		}
	list->First = listtemp->Last;
	free(listtemp);
	printf("Operation Reverse is done!\n");
}
