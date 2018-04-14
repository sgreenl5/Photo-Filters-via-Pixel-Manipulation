#include "PNMwriter.h"
#include "image.h"
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <iostream>


void PNMwriter:: Write(char* filename){
    WriteImage(filename, input_img1);

}

const char* PNMwriter:: SinkName(){
    return "PNMwriter";
}

void PNMwriter:: WriteImage(char *filename,const Image* img)
{
using namespace std; 

ofstream outfile; 
outfile.open(filename);

int image_width =  img->GetWidth();
int image_height = img->GetHeight();
char magicNum[128];

outfile << "P6"<< endl;
outfile << image_width << " " <<  image_height << endl;
outfile << 255 <<endl;

outfile.write((char *) img->pixel_list, sizeof(Pixel)*image_width*image_height);

outfile.close();

}



