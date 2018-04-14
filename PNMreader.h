#ifndef PNMREAD
#define PNMREAD

#include "source.h"
#include "image.h"

class PNMreader: public source
{
public:
    PNMreader(char* file_name);
    ~PNMreader();
    void Execute() const;
    void Update() const;
    char* SourceName() const;
    const char* SinkName();

private:
    char* filename;
    void ReadImage(char *filename, Image &image)const;
};

#endif
