#ifndef PNMWRITE
#define PNMWRITE

#include "sink.h"

class PNMwriter: public sink{
public:
    void Write(char* img);
    const char* SourceName();
    const char* SinkName();

private:
    char* output_name;
    void WriteImage(char *filename,const Image *image);


};
#endif
