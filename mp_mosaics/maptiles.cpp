/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */

   int row=theSource.getRows();
   int col=theSource.getColumns();
   size_t tile_len=theTiles.size();
   MosaicCanvas* mosaic=new MosaicCanvas(row,col);
   vector<Point<3>> points;
   map<Point<3>,size_t> plots;
   for(size_t i=0; i<tile_len; i++){
       LUVAPixel pic=theTiles[i].getAverageColor();
       points.push_back(convertToXYZ(pic));
       plots.insert(pair<Point<3>, size_t>(convertToXYZ(pic),i));
   }
   KDTree<3>* tree= new KDTree<3>(points);
   for(int i=0; i<row; i++){
       for(int j=0; j<col; j++){
           size_t index=plots[tree->findNearestNeighbor(convertToXYZ(theSource.getRegionColor(i,j)))];
           mosaic->setTile(i,j,&theTiles[index]);
       }
   }
   delete tree;
   return mosaic;
}

