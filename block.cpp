#include "block.h"

// set values in data attribute, based on a dimension x dimension square region
  //   with upper-left corner at (left, upper) in the input PNG image
  // The orientation of the pixels in the data vector must match the orientation
  //   of the pixels in the PNG.
  // PRE: upper and left (and upper + dimension, left + dimension) are valid
  //        vector indices
void Block::Build(PNG& im, int upper, int left, int dimension){
  std::vector<HSLAPixel> rowVals;
  for (int row = upper; row<upper+dimension;row++){
    for (int col = left; col<left+dimension;col++){
      rowVals.push_back(*im.getPixel(row,col));
    }
    data.push_back(rowVals);
  }

}

  // write the pixel colour data fom data attribute into im,
  //   with upper-left corner at (left, upper)
  // PRE: upper and left (and upper + dimension, left + dimension) are valid
  //        vector indices
  void Block::Render(PNG& im, int upper, int left) const{
    
  }

  // "Reverse" the Hue and Luminance channels for each pixel in the data attribute
  //   to simulate a photo-negative effect.
  // Refer to the HSLAPixel documentation to determine an appropriate transformation
  //   for "reversing" hue and luminance.
  void Block::Negative(){}

  // Return the horizontal (or vertical) size of the data block's image region
  int  Block::Dimension() const{
    return data.size();
  }
