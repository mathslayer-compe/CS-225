#include "../cs225/HSLAPixel.h"
#include "../Point.h"
#include "../cs225/PNG.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
MyColorPicker::MyColorPicker(std::string file){
  png_.readFromFile(file);
}
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  unsigned width=png_.width();
  unsigned height=png_.height();
  HSLAPixel pic=png_.getPixel(x%width, y%width);
  if(pic.l>1){
    pic=HSLAPixel(HSLAPixel(420,0.69,0.66));
  }
  return pic;
}
