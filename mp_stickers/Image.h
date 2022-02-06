/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */

#pragma once
#include "cs225/PNG.h"
using namespace cs225;
class Image : public PNG{
    public:
    Image();
        Image(Image const &other);
        void lighten();
        void lighten(double amount);
        void darken();
        void darken(double amount);
        void saturate();
        void saturate(double amount);
        void desaturate();
        void desaturate(double amount);
        void grayscale();
        void rotateColor(double degrees);
        void illinify();
        void scale(double factor);
        void scale(unsigned w, unsigned h);
        Image const & operator=(Image const &other);
        bool operator==(Image const &other)const;
        bool operator!=(Image const &other)const;
};