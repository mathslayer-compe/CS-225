#include <iostream>
#include <cmath>
#include <cstdlib>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "Image.h"
#include "StickerSheet.h"
#include <vector>
using cs225::HSLAPixel;
using cs225::PNG;
using std::vector;
StickerSheet::StickerSheet(const Image & picture, unsigned max):
image(picture){
    max_=max;
    img.reserve(max);
    x_vec.reserve(max);
    y_vec.reserve(max);
}
    
const StickerSheet& StickerSheet::operator=(const StickerSheet &other){
    if(this!=&other){
        this->image=other.image;
        max_=other.max_;
        img.reserve(max_);
        x_vec.reserve(max_);
        y_vec.reserve(max_);
        for(unsigned long i=0; i<other.img.size(); i++){
            this->img.push_back(other.img[i]);
            this->x_vec.push_back(other.x_vec[i]);
            this->y_vec.push_back(other.y_vec[i]);
        }
    }
    return *this;
}


StickerSheet::StickerSheet(const StickerSheet & other){
    this->image=other.image;
    max_=other.max_;
    img.reserve(max_);
    x_vec.reserve(max_);
    y_vec.reserve(max_);
    for(unsigned long i=0; i<other.img.size(); i++){
        this->img.push_back(other.img[i]);
        this->x_vec.push_back(other.x_vec[i]);
        this->y_vec.push_back(other.y_vec[i]);
    }
}

StickerSheet::~StickerSheet(){}

int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y){
    if(img.size()!=max_){
        img.push_back(&sticker);
        x_vec.push_back(x);
        y_vec.push_back(y);
        int index=img.size()-1;
        return index;
    }
    else{
        return -1;
    }
}

void StickerSheet::changeMaxStickers(unsigned max){
    if(max==max_){
        return;
    }
    else{
        if(max<max_){
            if(max<img.size()){
                img.erase(img.begin()+max, img.end());
                x_vec.erase(x_vec.begin()+max, x_vec.end());
                y_vec.erase(y_vec.begin()+max, y_vec.end());
            }
        }

        else if(max>max_){
            img.reserve(max);
            x_vec.reserve(max);
            y_vec.reserve(max);
        }


    }
    
    max_=max;
}

Image* StickerSheet::getSticker(unsigned index){
    if(index>=0 && index<img.size() && img[index]!=NULL){
        return img[index];
    }
    else{
        return NULL;
    }
}

void StickerSheet::removeSticker(unsigned index){
    img.erase(img.begin()+index);
    x_vec.erase(x_vec.begin()+index);
    y_vec.erase(y_vec.begin()+index);
}

Image StickerSheet::render()const{
    Image base(image);
    for(unsigned long int i=0; i<img.size(); i++){
        if(img[i]->width()+x_vec[i]>base.width()){
            base.resize(img[i]->width()+x_vec[i],base.height());
        }
        if(img[i]->height()+y_vec[i]>base.height()){
            base.resize(base.width(), img[i]->height()+y_vec[i]);
        }
    
        for(unsigned int x=0; x<img[i]->width(); x++){
            for(unsigned int y=0; y<img[i]->height(); y++){
                HSLAPixel & base_pixel=base.getPixel(x+x_vec[i],y+y_vec[i]);
                HSLAPixel & stk_pixel=img[i]->getPixel(x,y);
                if(stk_pixel.a!=0){
                    base_pixel.l=stk_pixel.l;
                    base_pixel.s=stk_pixel.s;
                    base_pixel.h=stk_pixel.h;
                    base_pixel.a=stk_pixel.a;
                }
            }
        }
    }
        return base;

}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
    if(index>=0 && index<img.size() && img[index]!=NULL){
        x_vec[index]=x;
        y_vec[index]=y;
        return true;
    }
    else{
        return false;
    }
}






