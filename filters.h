#ifndef FUNCTION_MAKE
#define FUNCTION_MAKE

#include "sink.h"
#include "source.h"

class filter :public sink,public source{
public:
    virtual const char* FilterName();

};

class Shrinker : public filter{
public:
    Shrinker(void);
    void Execute() const;
    void Update() const;
    const char* SourceName() const;
    const char* SinkName() const;
private:
    void HalveInSize(const Image &input_image, Image &output_image) const;
};

class LRConcat : public filter{
public:
    LRConcat(void);
    void Execute() const;
    void Update() const;
    const char* SourceName() const;
    const char* SinkName() const;
   
private:
    void LeftRightConcatenate(const Image &leftInput, const Image &rightInput, Image &output)const;

};

class TBConcat: public filter{
public:
    TBConcat(void);
    void Execute() const;
    void Update() const;
    const char* SourceName() const;
    const char* SinkName() const;
private:
    void TopBottomConcatenate(const Image &topInput, const Image &bottomInput, Image &output) const;
};

class Blender : public filter{
public:
    Blender(void);
    float factor;
    void Execute() const;
    void Update() const;
    void SetFactor(float num);
    const char* SourceName() const;
    const char* SinkName() const;
private:
    void Blend(const Image &input1, const Image &input2, float factor, Image &output) const;

};

class Mirror : public filter{
public:
    Mirror(void); 
    void Execute() const;
    void Update() const;
    const char* SourceName() const;
    const char* SinkName() const;

private: 	
    void MirrorImage(const Image &input_image, Image &output_image) const;
};

class Rotate : public filter{
public:
    Rotate(void); 
    void Execute() const;
    void Update() const;
    const char* SourceName() const;
    const char* SinkName() const;

private: 	
    void RotateImage(const Image &input_image, Image &output_image) const;
    
};

class Subtract : public filter{
public:
    Subtract(void); 
    void Execute() const;
    void Update() const;
    const char* SourceName() const;
    const char* SinkName() const;

private: 	
    void SubtractImage(const Image &topInput, const Image &bottomInput, Image &output) const;
    
};


class Grayscale : public filter{
public:
    Grayscale(void); 
    void Execute() const;
    void Update() const;
    const char* SourceName() const;
    const char* SinkName() const;

private: 	
    void GrayImage(const Image &input_image, Image &output_image) const;
    
};

class Blur : public filter{
public:
    Blur(void);
    void Execute() const;
    void Update() const;
    const char* SourceName() const;
    const char* SinkName() const;
private:
    void BlurImage(const Image &input_image, Image &output_image) const;
};

class CheckSum : public sink{
public:
    void OutputCheckSum(char* filename);
    const char* SinkName() const;
};

class Color : public source{
public:
    Color(int w, int h, unsigned char r, unsigned char g, unsigned char b);
    const char* SourceName() const;
    void Execute() const;
    void Update() const;
};

#endif
