#ifndef SINK_MAKE
#define SINK_MAKE

#include "image.h"
#include <stdio.h>
#include <stdlib.h>

class sink{
public:
    sink(void);
    const Image* input_img1;
    const Image* input_img2;
    void SetInput(Image* img);
    void SetInput2(Image* img);
    virtual const char* SinkName()const;
};

#endif
