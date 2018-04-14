#ifndef IMAGE_CREATION
#define IMAGE_CREATION

class filter;
class source;
class sink;
class PNMreader;


class Pixel
{
public:
    unsigned char r;
    unsigned char g;
    unsigned char b;

};


class Image
{
public:
    Image(void);
    Image(int w, int h);
    Image(Image &old);
    ~Image();

    Pixel *pixel_list;
    int GetWidth(void) const;
    void SetWidth(int wid);
    int GetHeight(void) const;
    void SetHeight(int hgt);
    void Update() const;
    void ResetSize(int w, int h);
      
    void SetUpdate(bool updated) const;
    mutable bool isUpdated;
    void SetFilter(filter* fil);
    filter* Filter_type;
    PNMreader* PNMreader_var;    
    void SetPNM(PNMreader* reader);
   
private:
    int width;
    int height;
    
};
#endif
