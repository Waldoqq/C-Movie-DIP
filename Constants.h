/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2016                     */
/*                                                                   */
/* Author: Guantao Liu                                               */
/* Date: 11/13/2016                                                  */
/*                                                                   */
/* Constants.h: header file for macros                               */
/*                                                                   */
/*********************************************************************/

/* None of William Scotten's code */

#ifndef CONSTANTS_H
#define CONSTANTS_H

/* Global macros */
/* Maximum length of file names */
#define SLEN 80 

/* Adjustment ratio in watermark */
#define WATERMARK_RATIO 1.45 

/* Number of frames on which the watermark stays in the same place */
#define WATERMARK_PER_FRAMES 15 

/* Movement speed of spotlight */
#define SPOTLIGHT_SPEED 10

/* Zoom speed */
#define ZOOM_SPEED 2

/* Full size in zoom */
#define ZOOM_FULL_SIZE 100

#endif
