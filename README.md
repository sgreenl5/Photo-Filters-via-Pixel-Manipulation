# Photo-Filters-via-Pixel-Manipulation

Spring 2017, written in C

A collection of scripts using structs to read in an input pnm file and produce a manipulated output pnm image using pixel manipulation.

This project takes an input pnm file, in this case our UO Logo,
and performs a series of actions on the photo. The filters are predetermined in the main3G.c file, and include:

Mirror, 
Greyscale, 
Rotate, 
Subtract, 
Blur, 
Constant Color, 
Right Left Concatinate, 
Left Right Concatinate, 
Top Bottom Concatinate, and
Shinker


The resulting image is one pnm file with all of the filter's outcomes side by side. The input image is called Input.pnm and 
the output, after being converted to a png file for easy access, is called FilterOutcome.png. File logger will show the 
steps taken during excecution.
