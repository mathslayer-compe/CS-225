/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include <vector>
using std::vector;
#include "cs225/PNG.h"
#include "Image.h"
using namespace cs225;
class StickerSheet{
    public:
        StickerSheet(const Image & picture, unsigned max);
        ~StickerSheet();
        StickerSheet(const StickerSheet & other);
        int addSticker(Image & sticker, unsigned x, unsigned y);
        void changeMaxStickers(unsigned max);
        Image * getSticker(unsigned index);
        const StickerSheet & operator=(const StickerSheet & other);
        void removeSticker(unsigned index);
        Image render()const;
        bool translate(unsigned index, unsigned x, unsigned y);
    private:
        Image image;
        unsigned int max_;
        vector<Image *> img;
        vector<unsigned int> x_vec;
        vector<unsigned int> y_vec;
};
 
