#include <iostream>
#include <cmath>
#include <cstdlib>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "Image.h"

using cs225::HSLAPixel;
using cs225::PNG;

Image::Image(){}
Image::Image(Image const &other): PNG(other){}

void Image::lighten(){
    for (unsigned int x = 0; x < this->width(); x++) {
        for (unsigned int y = 0; y < this->height(); y++) {
            HSLAPixel & pixel = this->getPixel(x, y);
            if((pixel.l<=0.9)&&(pixel.l>=0)){
                pixel.l+=0.1;
            }
            else{
                pixel.l=1;
            }
        }
    }
}


void Image::lighten(double amount){
    for (unsigned int x = 0; x < this->width(); x++) {
        for (unsigned int y = 0; y < this->height(); y++) {
            HSLAPixel & pixel = this->getPixel(x, y);
            if((pixel.l+amount>=0)&&(pixel.l+amount<=1)){
                pixel.l+=amount;
            }
            else{
                pixel.l=1;
            }
        }
    }

}

void Image::darken(){
    for (unsigned int x = 0; x < this->width(); x++) {
        for (unsigned int y = 0; y < this->height(); y++) {
            HSLAPixel & pixel = this->getPixel(x, y);
            if((pixel.l-0.1>=0)&&(pixel.l-0.1<=1)){
                pixel.l-=0.1;
            }
            else{
                pixel.l=0;
            }
        }
    }

}

void Image::darken(double amount){
    for (unsigned int x = 0; x < this->width(); x++) {
        for (unsigned int y = 0; y < this->height(); y++) {
            HSLAPixel & pixel = this->getPixel(x, y);
            if((pixel.l-amount>=0)&&(pixel.l-amount<=1)){
                pixel.l-=amount;
            }
            else{
                pixel.l=0;
            }
        }
    }

}
void Image::saturate(){
    for (unsigned int x = 0; x < this->width(); x++) {
        for (unsigned int y = 0; y < this->height(); y++) {
            HSLAPixel & pixel = this->getPixel(x, y);
            if((pixel.s+0.1>=0)&&(pixel.s+0.1<=1)){
                pixel.s+=0.1;
            }
            else{
                pixel.s=1;
            }
        }
    }

}

void Image::saturate(double amount){
    for(unsigned int x=0; x<this->width(); x++){
        for(unsigned int y=0; y<this->height(); y++){
            HSLAPixel & pixel= this->getPixel(x,y);
            if((pixel.s+amount>=0)&&(pixel.s+amount<=1)){
                pixel.s+=amount;
            }
            else{
                pixel.s=1;
            }
        }
    }
}
    
void Image::grayscale() {
    for (unsigned int x = 0; x < this->width(); x++) {
        for (unsigned int y = 0; y < this->height(); y++) {
        HSLAPixel & pixel = this->getPixel(x, y);

            // `pixel` is a pointer to the memory stored inside of the PNG `image`,
            // which means you're changing the image directly.  No need to `set`
            // the pixel since you're directly changing the memory of the image.
        pixel.s = 0;
        }
    }
}

void Image::rotateColor(double degrees){
    for(unsigned int x=0; x<this->width(); x++){
        for(unsigned int y=0; y<this->height(); y++){
            HSLAPixel & pixel= this->getPixel(x,y);
            if((pixel.h+degrees>360)){
                double deg=pixel.h+degrees;
                pixel.h=deg-360;
            }
            else if((pixel.h+degrees<0)){
                double deg=pixel.h+degrees;
                pixel.h=deg+360;
            }
            else{
                pixel.h+=degrees;
            }
        }
    }
}

void Image::illinify(){
    for(unsigned int x=0; x<this->width(); x++){
        for(unsigned int y=0; y<this->height(); y++){
            HSLAPixel & pixel=this->getPixel(x,y);
            if(((pixel.h>=0)&&(pixel.h<113.5))||((pixel.h>=278.5)&&(pixel.h<360))){
                pixel.h=11;
            }
            if((pixel.h>=113.5)&&(pixel.h<278.5)){
                pixel.h=216;
            }
        }
    }
}

void Image::scale(double factor){
    unsigned w = (unsigned)(factor*this->width());
    unsigned h = (unsigned) (factor*this->height());
    PNG firstImage=*this;
    this->resize(w, h);
    unsigned origX=0;
    unsigned origY=0;
    for (unsigned x = 0; x < w; x++) {
        for (unsigned y = 0; y < h; y++) {
        origX = (unsigned) ((double)x / factor);
        origY= (unsigned) ((double)y / factor);
        HSLAPixel & pixel_new = this->getPixel(x, y);
        HSLAPixel & pixel_old = firstImage.getPixel(origX, origY);
        pixel_new=pixel_old;
        }
    }
}

void Image::scale(unsigned w, unsigned h){
    double width= (double)this->width();
    double height=(double)this->height();
    double fac_width=(double)w/width;
    double fac_height=(double)h/height;
    if(fac_width<fac_height){
        scale(fac_width);
    }
    else{
        scale(fac_height);
    }

}
Image const & Image::operator=(Image const &other){
    return (Image const &)PNG::operator=(other);
}

bool Image::operator==(Image const &other)const{
    return PNG::operator==(other);
}

bool Image::operator!=(Image const & other)const{
    return PNG::operator!=(other);
}