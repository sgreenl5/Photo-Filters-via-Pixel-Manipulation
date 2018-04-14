#include "PNMreader.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include "logging.h"

using namespace std;

PNMreader::PNMreader(char* file_name){
    filename = (char*)malloc(sizeof(char)*(strlen(file_name)+1));
    strcpy(filename, file_name);
    GetOutput()-> SetPNM(this);
}

PNMreader:: ~PNMreader(){
    free(filename);
}

void PNMreader :: Update() const{
    Execute();
}

char* PNMreader:: SourceName()const{
    return "PNMreader";
}

void PNMreader:: Execute() const{
char msg1[1024];
sprintf(msg1, "%s: about to execute \n", SourceName());
Logger::LogEvent(msg1);
    ReadImage(filename, *GetOutput());

char msg2[1024];
sprintf(msg2, "%s: done executing \n", SourceName());
Logger::LogEvent(msg2);
}


void PNMreader:: ReadImage(char *filename, Image &image)
const{

ifstream infile(filename);


char magicNum[128];
int width, height, maxval;
infile >>  magicNum  >> width  >> height  >> maxval;

infile.seekg(1, ios ::cur);

image.pixel_list = (Pixel*)malloc(sizeof(Pixel)*width*height);

infile.read((char *) image.pixel_list, sizeof(Pixel)*width*height);

image.SetWidth(width);

image.SetHeight(height);

infile.close();
}
