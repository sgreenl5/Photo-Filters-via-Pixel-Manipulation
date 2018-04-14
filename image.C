#include "image.h"
#include <stdlib.h>
#include <stdio.h>
#include "filters.h"
#include <iostream>
#include "PNMreader.h"

using namespace std;

Image :: Image(void){
    width = 0;
    height = 0;
    pixel_list = NULL;
    isUpdated = false;
    Filter_type = NULL;
    PNMreader_var = NULL;
}

Image::~Image(){
    free(pixel_list);
}

Image :: Image(int w, int h){
    width = w;
    height = h;
    pixel_list = (Pixel *)malloc(sizeof(Pixel)*w*h);
}

void Image :: SetFilter(filter* fil){
    Filter_type = fil;
}

void Image :: SetUpdate(bool updated) const{
    isUpdated = updated;
}

void Image :: SetPNM(PNMreader* reader){
    PNMreader_var = reader;
}

void Image :: Update() const{

    if (isUpdated != true){
	if(Filter_type != NULL){
	    Filter_type->Update();
	}else if(PNMreader_var != NULL){
	    PNMreader_var->Update();
}
}
}

Image :: Image(Image &old){
int image_width = old.width;
int image_height = old.height;

pixel_list =(Pixel*) malloc(sizeof(Pixel)*image_width*image_height);

width = image_width;
height = image_height;

for(int j=0; j <image_height; j++){
    for(int i= 0; i < image_width; i++){
        (pixel_list)[i +j*image_width] = (old.pixel_list)[i+j*image_width];
        }
    }

}


int Image::GetWidth(void) const {
     return width;
}     

void Image::SetWidth(int wid){
    width = wid;
}
int Image::GetHeight(void) const {
    return height;
}

void Image::SetHeight(int hgt){
    height = hgt;
}

void Image:: ResetSize(int w, int h){
    width = w;
    height = h;
    pixel_list = (Pixel *)malloc(sizeof(Pixel)*w*h);
}
