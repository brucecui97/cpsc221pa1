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
    std::vector<HSLAPixel> rowVals;
    for (int col = left; col<left+dimension;col++){
      double h = im.getPixel(col,row)->h;
      double l= im.getPixel(col,row)->l;
      double s= im.getPixel(col,row)->s;
      double a = im.getPixel(col,row)->a;
      HSLAPixel pixel = HSLAPixel(h,s,l,a);
      rowVals.push_back(pixel);
    }
    data.push_back(rowVals);
  }

}

  // write the pixel colour data fom data attribute into im,
  //   with upper-left corner at (left, upper)
  // PRE: upper and left (and upper + dimension, left + dimension) are valid
  //        vector indices
  void Block::Render(PNG& im, int upper, int left) const{

    for (int row = upper; row<upper+Dimension();row++){
    for (int col = left; col<left+Dimension();col++){
      im.getPixel(col,row)->h = data[row-upper][col-left].h;
      im.getPixel(col,row)->s = data[row-upper][col-left].s;
      im.getPixel(col,row)->l = data[row-upper][col-left].l;
      im.getPixel(col,row)->a = data[row-upper][col-left].a;
    }

  }

  }

  // "Reverse" the Hue and Luminance channels for each pixel in the data attribute
  //   to simulate a photo-negative effect.
  // Refer to the HSLAPixel documentation to determine an appropriate transformation
  //   for "reversing" hue and luminance.
  void Block::Negative(){
    for (int row = 0;row<Dimension();row++){
      for (int col=0;col<Dimension();col++){
        double new_h = data[row][col].h + 180;
        if (new_h>=360){
          new_h = new_h - 360;
        }
        data[row][col].h = new_h;
        double before = data[row][col].l;
        data[row][col].l = 1.0-data[row][col].l;
        double after = data[row][col].l;

      }

    }
  }

  // Return the horizontal (or vertical) size of the data block's image region
  int  Block::Dimension() const{
    return data.size();
  }
