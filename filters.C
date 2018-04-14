#include <stdio.h>
#include "filters.h"
#include "image.h"
#include <iostream>
#include "logging.h"
#include <fstream>

using namespace std;

const char* filter:: FilterName(){
    return 0;
}


LRConcat :: LRConcat(void){
    GetOutput()-> SetFilter(this);
   
}

const char* LRConcat:: SourceName() const{
    return "LRConcat";
}

const char* LRConcat:: SinkName() const{
    return "LRConcat";
}
void LRConcat :: Execute() const{
    char msg1[1024];
    sprintf(msg1, "%s: about to execute \n", SourceName());
    Logger::LogEvent(msg1);

            LeftRightConcatenate(*input_img1, *input_img2, *GetOutput()); 
    char msg2[1024];
    sprintf(msg2, "%s: done executing \n", SourceName());
    Logger::LogEvent(msg2);
}


void LRConcat :: Update() const {
    char msg1[1024];
    sprintf(msg1, "%s: about to update \n", SourceName());
    Logger::LogEvent(msg1);
	if(input_img1 != NULL){
		//if (input_img1 -> isUpdated != true){
		if(true){
			char up1[1024];
			sprintf(up1, "%s: about to update image 1 \n", SourceName());
			Logger :: LogEvent(up1);

			input_img1->Update();
			char up2[1024];
			sprintf(up2, "%s: updated image 1 \n", SourceName());
			Logger :: LogEvent(up2);

			input_img1->SetUpdate(true);}}
	else{
   	char msg3[1024];
    	sprintf(msg3, "%s: missing input image 1", SourceName());
    	Logger::LogEvent(msg3);
	DataFlowException e(SourceName(), msg3);
    	throw e;
}
	if (input_img2 != NULL){
		//if (input_img2 -> isUpdated != true){
			if(true){
			char up3[1024];
			sprintf(up3, "%s: about to update image 2 \n", SourceName());
			Logger::LogEvent(up3);
			
			input_img2->Update();
			
			char up4[1024];
			sprintf(up4, "%s: about to update image 1 \n", SourceName());
			Logger :: LogEvent(up4);}
		}
	else{
   	char msg5[1024];
    	sprintf(msg5, "%s: missing input image 2", SourceName());
    	Logger::LogEvent(msg5);
	DataFlowException e(SourceName(), msg5);
    	throw e;

}
	if(input_img1->GetHeight() != input_img2->GetHeight()){
		char msg2[1024];
    		sprintf(msg2, "%s: heights must match: %d, %d", SourceName(), input_img1->GetHeight(), input_img2->GetHeight());
    		Logger:: LogEvent(msg2);
		DataFlowException e(SourceName(), msg2);
		throw e;}
		else{
 		Execute();
    }
char msg4[1024];
sprintf(msg4, "%s: done updating \n", SourceName());
Logger::LogEvent(msg4);
}

void LRConcat :: LeftRightConcatenate(const Image &leftInput, const Image &rightInput, Image &output)const{

int image_width = leftInput.GetWidth() + rightInput.GetWidth();
int image_height = leftInput.GetHeight();
output.SetWidth(image_width);
output.SetHeight(image_height);


output.pixel_list = (Pixel *)malloc(sizeof(Pixel)*image_width*image_height);

for(int j=0; j < leftInput.GetHeight(); j++){
    for(int i= 0; i < leftInput.GetWidth(); i++){
        (output.pixel_list)[i+j*image_width] = (leftInput.pixel_list)[i+ j*leftInput.GetWidth()];
        }
    }
for(int j =0; j < rightInput.GetHeight(); j++){
    for(int i =0; i < rightInput.GetWidth(); i++){
        (output.pixel_list)[(i+leftInput.GetWidth())+j*image_width] = (rightInput.pixel_list)[i+ j*rightInput.GetWidth()];
        }
}
}



TBConcat :: TBConcat(void){
    GetOutput()->SetFilter(this);
}

const char* TBConcat:: SourceName() const{
    return "TBConcat";
}

const char* TBConcat:: SinkName() const{
    return "TBConcat";
}

void TBConcat :: Execute() const{
char msg1[1024];
sprintf(msg1, "%s: about to execute \n", SourceName());
Logger::LogEvent(msg1);
	TopBottomConcatenate(*input_img1, *input_img2, *GetOutput());
char msg2[1024];
sprintf(msg2, "%s: done executing \n", SourceName());
Logger::LogEvent(msg2);
}

void TBConcat :: Update() const {
char msg1[1024];
sprintf(msg1, "%s: about to update \n", SourceName());
Logger::LogEvent(msg1);


if(input_img1 != NULL){
    //if (input_img1->isUpdated != true){
	if(true){
	char up1[1024];
	sprintf(up1, "%s: about to update image 1 \n", SourceName());
	Logger :: LogEvent(up1);
	
	input_img1->Update();
	
	char up2[1024];
	sprintf(up2, "%s: updated image 1 \n", SourceName());
	Logger :: LogEvent(up2);
	
	input_img1 -> SetUpdate(true);}
}else{
   	char msg3[1024];
    	sprintf(msg3, "%s: missing input image 1", SourceName());
    	Logger::LogEvent(msg3);
	DataFlowException e(SourceName(), msg3);
    	throw e;
}

if(input_img2 != NULL){

   // if (input_img2 -> isUpdated != true){
	if(true){
	char up3[1024];
	sprintf(up3, "%s: about to update image 2 \n", SourceName());
	Logger :: LogEvent(up3);
	input_img2->Update();
	
	char up4[1024];
	sprintf(up4, "%s: about to update image 2 \n", SourceName());
	Logger :: LogEvent(up4);
	

	input_img2->SetUpdate(true);
	
}
}else{
   	char msg3[1024];
    	sprintf(msg3, "%s: missing input image 2", SourceName());
    	Logger::LogEvent(msg3);
	DataFlowException e(SourceName(), msg3);
    	throw e;
}

Execute();

char msg2[1024];
sprintf(msg2, "%s: done updating \n", SourceName());
Logger::LogEvent(msg2);
}


void TBConcat :: TopBottomConcatenate(const Image &topInput, const Image &bottomInput, Image &output) const{

int image_width = topInput.GetWidth();
int image_height = topInput.GetHeight()+ bottomInput.GetHeight();
output.SetWidth(image_width);
output.SetHeight(image_height);


output.pixel_list = (Pixel *)malloc(sizeof(Pixel)*image_width*image_height);

for(int j=0; j < topInput.GetHeight(); j++){
    for(int i= 0; i < topInput.GetWidth(); i++){
        (output.pixel_list)[i+j*image_width] = (topInput.pixel_list)[i+ j*topInput.GetWidth()];
        }
    }
for(int j =0; j < bottomInput.GetHeight(); j++){
    for(int i =0; i < bottomInput.GetWidth(); i++){
        (output.pixel_list)[i+(j+topInput.GetHeight())*image_width] = (bottomInput.pixel_list)[i+ j*bottomInput.GetWidth()];
        }


}

}


Shrinker :: Shrinker(void){
    GetOutput()-> SetFilter(this);
}

const char* Shrinker:: SourceName() const{
    return "Shrinker";
}

const char* Shrinker:: SinkName() const{
    return "Shrinker";
}

void Shrinker :: Execute() const{
char msg1[1024];
sprintf(msg1, "%s: about to execute \n", SourceName());
Logger::LogEvent(msg1);
    	HalveInSize(*input_img1, *GetOutput());
char msg2[1024];
sprintf(msg2, "%s: done executing \n", SourceName());
Logger::LogEvent(msg2);
}

void Shrinker :: Update() const{
char msg1[1024];
sprintf(msg1, "%s: about to update \n", SourceName());
Logger::LogEvent(msg1);
 
if(input_img1 != NULL){
 //   if (input_img1->isUpdated != true){
	if(true){
	char up1[1024];
	sprintf(up1, "%s: about to update image 1 \n", SourceName());
	Logger :: LogEvent(up1);
	
	input_img1->Update();
	
	char up2[1024];
	sprintf(up2, "%s: updated image 1 \n", SourceName());
	Logger :: LogEvent(up2);
	
	input_img1 -> SetUpdate(true);
	Execute(); }
}else{
   	char msg3[1024];
    	sprintf(msg3, "%s: missing input image 1", SourceName());
    	Logger::LogEvent(msg3);
	DataFlowException e(SourceName(), msg3);
    	throw e;
}



char msg2[1024];
sprintf(msg2, "%s: done updating \n", SourceName());
Logger::LogEvent(msg2);
}

void Shrinker :: HalveInSize(const Image &input_image, Image &output_image) const{

int image_width = (input_image.GetWidth())/2;
int image_height = (input_image.GetHeight())/2;
output_image.SetWidth(image_width);
output_image.SetHeight(image_height);

output_image.pixel_list = (Pixel *)malloc(sizeof(Pixel)*image_width*image_height);


for(int j=0; j <image_height; j++){
    for(int i= 0; i < image_width; i++){
        (output_image.pixel_list)[i +j*image_width] = (input_image.pixel_list)[2*i+2*j*input_image.GetWidth()];
        }
    }



}


Blender :: Blender(void){
    GetOutput()->SetFilter(this);
}

void Blender :: SetFactor(float num){
    factor = num;
}

const char* Blender:: SourceName() const{
    return "Blender";
}

const char* Blender:: SinkName() const{
    return "Blender";
}

void Blender :: Update() const{

char msg1[1024];
sprintf(msg1, "%s: about to update \n", SourceName());
Logger::LogEvent(msg1);

if(input_img1 != NULL){
   // if (input_img1->isUpdated != true){
	if(true){
	char up1[1024];
	sprintf(up1, "%s: about to update image 1 \n", SourceName());
	Logger :: LogEvent(up1);
	
	input_img1->Update();
	
	char up2[1024];
	sprintf(up2, "%s: updated image 1 \n", SourceName());
	Logger :: LogEvent(up2);
	
	input_img1 -> SetUpdate(true);}
}else{
   	char msg3[1024];
    	sprintf(msg3, "%s: missing input image 1", SourceName());
    	Logger::LogEvent(msg3);
	DataFlowException e(SourceName(), msg3);
    	throw e;
}

if(input_img2 != NULL){

 //   if (input_img2 -> isUpdated != true){
	if(true){
	char up3[1024];
	sprintf(up3, "%s: about to update image 2 \n", SourceName());
	Logger :: LogEvent(up3);
	input_img2->Update();
	
	char up4[1024];
	sprintf(up4, "%s: about to update image 2 \n", SourceName());
	Logger :: LogEvent(up4);
	
	input_img2->SetUpdate(true);
}
}else{
   	char msg3[1024];
    	sprintf(msg3, "%s: missing input image 2", SourceName());
    	Logger::LogEvent(msg3);
	DataFlowException e(SourceName(), msg3);
    	throw e;
}




Execute();
char msg2[1024];
sprintf(msg2, "%s: done updating \n", SourceName());
Logger::LogEvent(msg2);

}
void Blender :: Execute() const{
char msg1[1024];
sprintf(msg1, "%s: about to execute \n", SourceName());
Logger::LogEvent(msg1);

if (factor <0 || factor >= 1){
   	char msg[1024];
    	sprintf(msg, "%s: invalid factor", SourceName());
    	Logger::LogEvent(msg);
	DataFlowException e(SourceName(), msg);
    	throw e;}
else{

        Blend(*input_img1, *input_img2, factor, *GetOutput());

}
char msg2[1024];
sprintf(msg2, "%s: done executing \n", SourceName());
Logger::LogEvent(msg2);
}

void Blender:: Blend(const Image &input1, const Image &input2, float factor, Image &output) const{

int image_width = input1.GetWidth();
int image_height = input2.GetHeight();
output.SetWidth(image_width);
output.SetHeight(image_height);

output.pixel_list = (Pixel *)malloc(sizeof(Pixel)*image_width*image_height);

float input2_color = 1 - factor;


for(int j=0; j <image_height; j++){
    for(int i= 0; i < image_width; i++){
        (output.pixel_list)[i +j*image_width].r = (input1.pixel_list)[i+j*image_width].r *factor +(input2.pixel_list)[i+j*image_width].r*input2_color;
        (output.pixel_list)[i +j*image_width].g = (input1.pixel_list)[i+j*image_width].g *factor +(input2.pixel_list)[i+j*image_width].g*input2_color;
        (output.pixel_list)[i +j*image_width].b = (input1.pixel_list)[i+j*image_width].b *factor +(input2.pixel_list)[i+j*image_width].b*input2_color;
    }

}
}


Mirror :: Mirror(void){
    GetOutput()->SetFilter(this);
}

const char* Mirror :: SourceName() const{
    return "Mirror";
}

const char* Mirror :: SinkName() const{
    return "Mirror";
}

void Mirror :: MirrorImage(const Image &input_image, Image &output_image) const{

int image_width = input_image.GetWidth();
int image_height = input_image.GetHeight();
output_image.SetWidth(image_width);
output_image.SetHeight(image_height);

output_image.pixel_list = (Pixel *)malloc(sizeof(Pixel)*image_width*image_height);


for(int j=0; j <image_height; j++){
    for(int i= 0; i < image_width; i++){
	(output_image.pixel_list)[i+j*image_width] = (input_image.pixel_list)[(image_width-i-1) + j*image_width];
	
}
    }
}



void Mirror :: Execute() const{
char msg1[1024];
sprintf(msg1, "%s: about to execute \n", SourceName());
Logger::LogEvent(msg1);
    	MirrorImage(*input_img1, *GetOutput());
char msg2[1024];
sprintf(msg2, "%s: done executing \n", SourceName());
Logger::LogEvent(msg2);
}

void Mirror :: Update() const{
char msg1[1024];
sprintf(msg1, "%s: about to update \n", SourceName());
Logger::LogEvent(msg1);
 

 
if(input_img1 != NULL){
   // if (input_img1->isUpdated != true){
	if(true){
	char up1[1024];
	sprintf(up1, "%s: about to update image 1 \n", SourceName());
	Logger :: LogEvent(up1);
	
	input_img1->Update();
	
	char up2[1024];
	sprintf(up2, "%s: updated image 1 \n", SourceName());
	Logger :: LogEvent(up2);
	
	input_img1 -> SetUpdate(true);
	Execute(); }
}else{
   	char msg3[1024];
    	sprintf(msg3, "%s: missing input image 1", SourceName());
    	Logger::LogEvent(msg3);
	DataFlowException e(SourceName(), msg3);
    	throw e;
}



char msg2[1024];
sprintf(msg2, "%s: done updating \n", SourceName());
Logger::LogEvent(msg2);
}




Rotate :: Rotate(void){
    GetOutput()->SetFilter(this);
}

const char* Rotate :: SourceName() const{
    return "Rotate";
}

const char* Rotate :: SinkName() const{
    return "Rotate";
}

void Rotate :: RotateImage(const Image &input_image, Image &output_image) const{

int image_width = input_image.GetHeight();
int image_height = input_image.GetWidth();
output_image.SetWidth(image_width);
output_image.SetHeight(image_height);

output_image.pixel_list = (Pixel *)malloc(sizeof(Pixel)*image_width*image_height);


for(int j=0; j <image_height; j++){
    for(int i= 0; i < image_width; i++){
	(output_image.pixel_list)[i+j*image_width] = (input_image.pixel_list)[(image_width-i-1)*image_height+ j];
	
}
    }
}

void Rotate :: Execute() const{
char msg1[1024];
sprintf(msg1, "%s: about to execute \n", SourceName());
Logger::LogEvent(msg1);
    	RotateImage(*input_img1, *GetOutput());
char msg2[1024];
sprintf(msg2, "%s: done executing \n", SourceName());
Logger::LogEvent(msg2);
}

void Rotate :: Update() const{
char msg1[1024];
sprintf(msg1, "%s: about to update \n", SourceName());
Logger::LogEvent(msg1);


if (input_img1 != NULL){  
 //   if (input_img1->isUpdated != true){
	if(true){
	char up1[1024];
	sprintf(up1, "%s: about to update image 1 \n", SourceName());
	Logger :: LogEvent(up1);
	
	input_img1->Update();
	
	char up2[1024];
	sprintf(up2, "%s: updated image 1 \n", SourceName());
	Logger :: LogEvent(up2);
	
	input_img1 -> SetUpdate(true);
	Execute(); }
}else{
   	char msg3[1024];
    	sprintf(msg3, "%s: missing input image 1", SourceName());
    	Logger::LogEvent(msg3);
	DataFlowException e(SourceName(), msg3);
    	throw e;
}



char msg2[1024];
sprintf(msg2, "%s: done updating \n", SourceName());
Logger::LogEvent(msg2);
}

Subtract :: Subtract(void){
    GetOutput()->SetFilter(this);
}

const char* Subtract :: SourceName() const{
    return "Subtract";
}

const char* Subtract :: SinkName() const{
    return "Subtract";
}

void Subtract :: SubtractImage(const Image &input1, const Image &input2,  Image &output) const{

int image_width = input1.GetWidth();
int image_height = input2.GetHeight();
output.SetWidth(image_width);
output.SetHeight(image_height);

output.pixel_list = (Pixel *)malloc(sizeof(Pixel)*image_width*image_height);



for(int j=0; j <image_height; j++){
    for(int i= 0; i < image_width; i++){
		if((input1.pixel_list)[i +j*image_width].r > (input2.pixel_list)[i+j*image_width].r){
        (output.pixel_list)[i +j*image_width].r = (input1.pixel_list)[i+j*image_width].r -(input2.pixel_list)[i+j*image_width].r;
}else{
	(output.pixel_list)[i + j*image_width].r = 0;
}

		if((input1.pixel_list)[i +j*image_width].g > (input2.pixel_list)[i+j*image_width].g){
        (output.pixel_list)[i +j*image_width].g = (input1.pixel_list)[i+j*image_width].g -(input2.pixel_list)[i+j*image_width].g;
}else{
	(output.pixel_list)[i + j*image_width].g = 0;
}
		if((input1.pixel_list)[i +j*image_width].b > (input2.pixel_list)[i+j*image_width].b){
        (output.pixel_list)[i +j*image_width].b = (input1.pixel_list)[i+j*image_width].b -(input2.pixel_list)[i+j*image_width].b;
}else{
	(output.pixel_list)[i + j*image_width].b = 0;
}
    }

}
}

void Subtract :: Update() const{
    char msg1[1024];
    sprintf(msg1, "%s: about to update \n", SourceName());
    Logger::LogEvent(msg1);
 


	if(input_img1 != NULL){
	//	if (input_img1 -> isUpdated != true){
	if(true){
			char up1[1024];
			sprintf(up1, "%s: about to update image 1 \n", SourceName());
			Logger :: LogEvent(up1);

			input_img1->Update();
			char up2[1024];
			sprintf(up2, "%s: updated image 1 \n", SourceName());
			Logger :: LogEvent(up2);

			input_img1->SetUpdate(true);}}
	else{
   	char msg3[1024];
    	sprintf(msg3, "%s: missing input image 1", SourceName());
    	Logger::LogEvent(msg3);
	DataFlowException e(SourceName(), msg3);
    	throw e;
}
	if (input_img2 != NULL){
//		if (input_img2 -> isUpdated != true){
	if(true){
			char up3[1024];
			sprintf(up3, "%s: about to update image 2 \n", SourceName());
			Logger::LogEvent(up3);
			
			input_img2->Update();
			
			char up4[1024];
			sprintf(up4, "%s: about to update image 1 \n", SourceName());
			Logger :: LogEvent(up4);}
		}
	else{
   	char msg5[1024];
    	sprintf(msg5, "%s: missing input image 2", SourceName());
    	Logger::LogEvent(msg5);
	DataFlowException e(SourceName(), msg5);
    	throw e;

}
	if(input_img1->GetHeight() != input_img2->GetHeight()){
		char msg2[1024];
    		sprintf(msg2, "%s: heights must match: %d, %d", SourceName(), input_img1->GetHeight(), input_img2->GetHeight());
    		Logger:: LogEvent(msg2);
		DataFlowException e(SourceName(), msg2);
		throw e;}
		else{
 		Execute();
    }
char msg4[1024];
sprintf(msg4, "%s: done updating \n", SourceName());
Logger::LogEvent(msg4);
}

void Subtract :: Execute() const{
    char msg1[1024];
    sprintf(msg1, "%s: about to execute \n", SourceName());
    Logger::LogEvent(msg1);

            SubtractImage(*input_img1, *input_img2, *GetOutput()); 
    char msg2[1024];
    sprintf(msg2, "%s: done executing \n", SourceName());
    Logger::LogEvent(msg2);
}

Grayscale :: Grayscale(void){
    GetOutput()->SetFilter(this);
}

const char* Grayscale :: SourceName() const{
    return "Grayscale";
}

const char* Grayscale :: SinkName() const{
    return "Grayscale";
}

void Grayscale :: GrayImage(const Image &input1, Image &output) const{

int image_width = input1.GetWidth();
int image_height = input1.GetHeight();
output.SetWidth(image_width);
output.SetHeight(image_height);

output.pixel_list = (Pixel *)malloc(sizeof(Pixel)*image_width*image_height);



for(int j=0; j <image_height; j++){
    for(int i= 0; i < image_width; i++){
        (output.pixel_list)[i +j*image_width].r = (input1.pixel_list)[i+j*image_width].r/5 +(input1.pixel_list)[i+j*image_width].g/2 + (input1.pixel_list)[i+j*image_width].b/4;
        (output.pixel_list)[i +j*image_width].g = (input1.pixel_list)[i+j*image_width].r/5 +(input1.pixel_list)[i+j*image_width].g/2 + (input1.pixel_list)[i+j*image_width].b/4;
        (output.pixel_list)[i +j*image_width].b = (input1.pixel_list)[i+j*image_width].r/5 +(input1.pixel_list)[i+j*image_width].g/2 + (input1.pixel_list)[i+j*image_width].b/4;
    }

}
}

void Grayscale :: Execute() const{
char msg1[1024];
sprintf(msg1, "%s: about to execute \n", SourceName());
Logger::LogEvent(msg1);
    	GrayImage(*input_img1, *GetOutput());
char msg2[1024];
sprintf(msg2, "%s: done executing \n", SourceName());
Logger::LogEvent(msg2);
}

void Grayscale :: Update() const{
char msg1[1024];
sprintf(msg1, "%s: about to update \n", SourceName());
Logger::LogEvent(msg1);



if(input_img1 != NULL){  
   // if (input_img1->isUpdated != true){
	if(true){
	char up1[1024];
	sprintf(up1, "%s: about to update image 1 \n", SourceName());
	Logger :: LogEvent(up1);
	
	input_img1->Update();
	
	char up2[1024];
	sprintf(up2, "%s: updated image 1 \n", SourceName());
	Logger :: LogEvent(up2);
	
	input_img1 -> SetUpdate(true);
	Execute(); }
}else{
   	char msg3[1024];
    	sprintf(msg3, "%s: missing input image 1", SourceName());
    	Logger::LogEvent(msg3);
	DataFlowException e(SourceName(), msg3);
    	throw e;
}



char msg2[1024];
sprintf(msg2, "%s: done updating \n", SourceName());
Logger::LogEvent(msg2);
}





Blur :: Blur(void){
    GetOutput()->SetFilter(this);
}

const char* Blur :: SourceName() const{
    return "Blur";
}

const char* Blur :: SinkName() const{
    return "Blur";
}

void Blur :: BlurImage(const Image &input1, Image &output) const{

int image_width = input1.GetWidth();
int image_height = input1.GetHeight();
output.SetWidth(image_width);
output.SetHeight(image_height);

output.pixel_list = (Pixel *)malloc(sizeof(Pixel)*image_width*image_height);



for(int j=0; j < image_height; j++){
    for(int i= 0; i < image_width; i++){
	if (j == 0 || i == 0 || j == image_height-1 || i == image_width-1){
		(output.pixel_list)[i+j*image_width].r = (input1.pixel_list)[i +j*image_width].r;
		(output.pixel_list)[i+j*image_width].g = (input1.pixel_list)[i +j*image_width].g;
		(output.pixel_list)[i+j*image_width].b = (input1.pixel_list)[i +j*image_width].b;
	        
} else{ 
		(output.pixel_list)[i +j*image_width].r = (input1.pixel_list)[i+1+((j-1)*image_width)].r/8 +(input1.pixel_list)[i+1+j*image_width].r/8 + (input1.pixel_list)[i+1+((j+1)*image_width)].r/8 +(input1.pixel_list)[i+((j-1)*image_width)].r/8 +(input1.pixel_list)[i+((j+1)*image_width)].r/8 +(input1.pixel_list)[i-1+((j-1)*image_width)].r/8+(input1.pixel_list)[i-1+(j*image_width)].r/8 +(input1.pixel_list)[i-1+((j+1)*image_width)].r/8;
		(output.pixel_list)[i +j*image_width].g = (input1.pixel_list)[i+1+((j-1)*image_width)].g/8 +(input1.pixel_list)[i+1+j*image_width].g/8 + (input1.pixel_list)[i+1+((j+1)*image_width)].g/8 +(input1.pixel_list)[i+((j-1)*image_width)].g/8 +(input1.pixel_list)[i+((j+1)*image_width)].g/8 +(input1.pixel_list)[i-1+((j-1)*image_width)].g/8+(input1.pixel_list)[i-1+(j*image_width)].g/8 +(input1.pixel_list)[i-1+((j+1)*image_width)].g/8;    

		(output.pixel_list)[i +j*image_width].b = (input1.pixel_list)[i+1+((j-1)*image_width)].b/8 +(input1.pixel_list)[i+1+j*image_width].b/8 + (input1.pixel_list)[i+1+((j+1)*image_width)].b/8 +(input1.pixel_list)[i+((j-1)*image_width)].b/8 +(input1.pixel_list)[i+((j+1)*image_width)].b/8 +(input1.pixel_list)[i-1+((j-1)*image_width)].b/8+(input1.pixel_list)[i-1+(j*image_width)].b/8 +(input1.pixel_list)[i-1+((j+1)*image_width)].b/8;
}


}
}
}

void Blur :: Execute() const{
char msg1[1024];
sprintf(msg1, "%s: about to execute \n", SourceName());
Logger::LogEvent(msg1);
    	BlurImage(*input_img1, *GetOutput());
char msg2[1024];
sprintf(msg2, "%s: done executing \n", SourceName());
Logger::LogEvent(msg2);
}

void Blur :: Update() const{
char msg1[1024];
sprintf(msg1, "%s: about to update \n", SourceName());
Logger::LogEvent(msg1);


 
if (input_img1 != NULL){ 
	if(true){
	char up1[1024];
	sprintf(up1, "%s: about to update image 1 \n", SourceName());
	Logger :: LogEvent(up1);
	
	input_img1->Update();
	
	char up2[1024];
	sprintf(up2, "%s: updated image 1 \n", SourceName());
	Logger :: LogEvent(up2);
	
	input_img1 -> SetUpdate(true);
	Execute(); }
}else{
   	char msg3[1024];
    	sprintf(msg3, "%s: missing input image 1", SourceName());
    	Logger::LogEvent(msg3);
	DataFlowException e(SourceName(), msg3);
    	throw e;
}



char msg2[1024];
sprintf(msg2, "%s: done updating \n", SourceName());
Logger::LogEvent(msg2);
}





void CheckSum:: OutputCheckSum(char* filename){
    ofstream outfile;
    outfile.open(filename);
   
    unsigned char red =0;
    unsigned char green=0;
    unsigned char blue=0;

    int image_width = input_img1->GetWidth();
    int image_height = input_img1->GetHeight();

for(int j=0; j <image_height; j++){
    for(int i= 0; i < image_width; i++){
	red += (input_img1->pixel_list)[i+ image_width*j].r;
	green += (input_img1->pixel_list)[i+ image_width*j].g;
	blue += (input_img1->pixel_list)[i+ image_width*j].b;
	
}
    } 


outfile <<"CHECKSUM: " << (int) red << ", " << (int)green << ", " << (int) blue << endl;

    outfile.close();

}



const char* CheckSum:: SinkName() const{
    return "CheckSum";
}

const char* Color :: SourceName() const{
    return "Color";
}


void Color :: Execute() const{
/*char msg1[1024];
sprintf(msg1, "%s: about to execute \n", SourceName());
Logger::LogEvent(msg1);
    	ColorImage(int w, int h, int r, int g, int b);
char msg2[1024];
sprintf(msg2, "%s: done executing \n", SourceName());
Logger::LogEvent(msg2);
*/}

void Color :: Update() const{
/*char msg1[1024];
sprintf(msg1, "%s: about to update \n", SourceName());
Logger::LogEvent(msg1);
  
    if (input_img1->isUpdated != true){
	char up1[1024];
	sprintf(up1, "%s: about to update image 1 \n", SourceName());
	Logger :: LogEvent(up1);
	
	input_img1->Update();
	
	char up2[1024];
	sprintf(up2, "%s: updated image 1 \n", SourceName());
	Logger :: LogEvent(up2);
	
	input_img1 -> SetUpdate(true);
	Execute(); }
else{
   	char msg3[1024];
    	sprintf(msg3, "%s: missing input image 1", SourceName());
    	Logger::LogEvent(msg3);
	DataFlowException e(SourceName(), msg3);
    	throw e;
}*/
}

Color :: Color(int w, int h, unsigned char red, unsigned char green, unsigned char blue){

output_img.SetWidth(w);
output_img.SetHeight(h);

output_img.pixel_list = (Pixel *)malloc(sizeof(Pixel)*w*h);

for(int j=0; j < h ; j++){
    for(int i= 0; i < w; i++){
	(output_img.pixel_list)[i +j*w].r = red;
	(output_img.pixel_list)[i +j*w].g =green;	
 	(output_img.pixel_list)[i +j*w].b = blue;
}
    } 


}
