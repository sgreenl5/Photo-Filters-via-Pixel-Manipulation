#ifndef SOURCE_MAKE
#define SOURCE_MAKE


#include "image.h"
#include <stdlib.h>
#include <stdio.h>


class source{
public:
    mutable Image output_img;  
    virtual Image* GetOutput()const ;
    virtual void Update()const;
    virtual const char* SourceName() const;
protected:
    virtual void Execute() const;
};


#endif
