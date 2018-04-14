# Photo-Filters-via-Pixel-Manipulation
A C script using structs to read in an input pnm file and produce a manipulated output pnm image using pixel manipulation.

This is the final project for the Computer Science course C/C++ and Unix. It takes an input pnm file, in this case our UO Logo,
and performs a series of actions on the photo. The filters are predetermined in the main3G.c file, and include:

Mirror
Greyscale
Rotate
Subtract
Blur
Constant Color
Right Left Concatinate 
Left Right Concatinate
Top Bottom Concatinate
Shinker


The resulting image is one pnm file with all of the filter's outcomes side by side. The input image is called Input.pnm and 
the output, after being converted to a png file for easy access, is called FilterOutcome.png. 
