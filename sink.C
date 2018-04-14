#include "sink.h"
#include <stdio.h>
#include <stdlib.h>

void sink:: SetInput(Image* img){
	input_img1 = img;
    }

void sink::  SetInput2(Image* img){
	input_img2 = img;
    }
const char* sink::SinkName()const{
return 0;
}

sink::sink(void){
	input_img1 = NULL;
	input_img2 = NULL;
}
