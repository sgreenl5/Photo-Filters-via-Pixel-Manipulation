#include "source.h"
#include <stdlib.h>
#include <stdio.h>


//Sourse:: source() {output.SetSource(this);

Image* source:: GetOutput()const {
    return &output_img;

}

void source :: Update() const {
}

void source :: Execute() const{
}

const char* source:: SourceName()const{
return 0;}
