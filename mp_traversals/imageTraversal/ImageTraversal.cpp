#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator(){
  /** @todo [Part 1] */
  trav=NULL;
  unsigned x=0;
  unsigned y=0;
  pts.resize(png_.width(), std::vector<bool>(png_.height()));
  while(x<png_.width()){
    while(y<png_.height()){
      pts[x][y]=false;
      y++;
    }
    x++;
  }
}


bool ImageTraversal::Iterator::status(Point pt){
  if(pt.x>=png_.width()||pt.y>=png_.height()){
    return false;
  }
  if(pt.x<png_.width()&&pt.y<png_.height()){
    HSLAPixel & begin = png_.getPixel(start_.x,start_.y);
    HSLAPixel &comp=png_.getPixel(pt.x,pt.y);
    if(calculateDelta(begin, comp)<tolerance_){
      if(!(pts[pt.x][pt.y])){
        return true;
      }
    }
  }
  return false;
}
ImageTraversal::Iterator::Iterator(Point start, PNG png, ImageTraversal* traversal, double tolerance){
  start_=start;
  curr= start;
  png_= png;
  trav=traversal;
  tolerance_ = tolerance;
  unsigned x= 0;
  unsigned y= 0;
  pts.resize(png_.width(), std::vector<bool>(png_.height()));
  while(x<png_.width()){
    while(y<png_.height()){
      pts[x][y]=false;
      y++;
    }
    x++;
  }
  if(status(curr)){
    pts[curr.x][curr.y]=true;
  }
}
/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  unsigned x=curr.x;
  unsigned y=curr.y;
  pts[x][y]=true;
  Point top=Point(x,y-1);
  Point right=Point(x+1,y);
  Point down=Point(x,y+1);
  Point left=Point(x-1,y);
  if(status(right)==true){
    trav->add(right);
  }
  if(status(down)==true){
    trav->add(down);
  }
  if(status(left)==true){
    trav->add(left);
  }
  if(status(top)==true){
    trav->add(top);
  }
  while(!(status(trav->peek()))&&!(trav->empty())){
    trav->pop();
    if(trav->empty()){
      return *this;
    }
  }
  if(trav->empty()){
    trav=NULL;
    return *this;
  }
  if(!trav->empty()){
    curr=trav->peek();
    return *this;
  }
  return *this;
}


/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return curr;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  bool selfcheck=false;
  bool othercheck=false;
  if(trav==NULL){
    selfcheck=true;
  }
  if(other.trav==NULL){
    othercheck=true; 
  }
  if(selfcheck==false){
    selfcheck=trav->empty();
  }
  if(othercheck==false){
    othercheck=other.trav->empty();
  }
  if(selfcheck==true&&othercheck==true){
    return false;
  }
  if(selfcheck==false&&othercheck==false){
    return (trav!=other.trav);
  }
  return true;
}