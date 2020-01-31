// File:        gridlist.cpp
// Date:        2020-01-18 00:11
// Description: Contains partial implementation of GridList class
//              CPSC 221 2019W2 PA1
//              Function bodies to be completed by yourselves
//
// ADD YOUR FUNCTION IMPLEMENTATIONS IN THIS FILE
//

#include "gridlist.h"
#include "gridlist_given.cpp"

// Creates a PNG of appropriate pixel dimensions according to the GridList's structure
//   and colours each pixel according the each GridNode's Block data.
// The fully coloured PNG is returned.
PNG GridList::Render() const
{
  if (dimx == 0 && dimy == 0)
  {
    PNG image;
    return image;
  }
  else
  {
    int blockSize = northwest->data.Dimension();
    int width = dimx * blockSize;
    int height = dimy * blockSize;
    PNG image(width, height);

    GridNode *curr = northwest;

    for (int row = 0; row < height; row = row + blockSize)
    {
      for (int col = 0; col < width; col = col + blockSize)
      {
        // std::cout<<curr->data.data[0][0]<<std::endl;
        curr->data.Render(image, row, col);
        curr = curr->next;
      }
    }

    // enter your code here

    return image;
  }
}

// Allocates a new GridNode containing bdata and
//   attaches it to end of this list.
// Be careful of the special case of inserting into an empty list.
void GridList::InsertBack(const Block &bdata)
{
  GridNode *lastNode = new GridNode(bdata);
  lastNode->next = NULL;
  lastNode->prev = NULL;

  if (northwest == NULL || southeast == NULL)
  {
    northwest = lastNode;
    southeast = lastNode;
    return;
  }
  else
  {
    southeast->next = lastNode;
    lastNode->prev = southeast;
    southeast = southeast->next;
  }
}

// if this list has an odd number of column blocks, then the right side will have more blocks
// PRE:  this list and inner are not the same physical list
//       this list must have at least two column blocks
//       inner list must have at least one column block
//       inner list must have the same vertical resolution, vertical block dimension, and block size
// POST: this list has nodes of the entire inner list in between the left and right halves of this list
//         and inner list becomes empty
//       otherwise both lists are not modified
// THIS MUST BE ACHIEVED USING POINTER REASSIGNMENTS.
// DO NOT ALLOCATE OR DELETE ANY NODES IN THIS FUNCTION.
void GridList::Sandwich_H(GridList &inner)
{
  if (dimy != inner.dimy)
  {
    return;
  }

  int left_col_num_original = dimx / 2 - 1;
  int right_col_num_original = dimx / 2;

  int left_col_num_inner = 0;
  int right_col_num_inner = inner.Length() / dimy - 1;

  std::vector<GridNode *> original_left = extractColumn(left_col_num_original);
  std::vector<GridNode *> original_right = extractColumn(right_col_num_original);
  std::vector<GridNode *> inner_left = inner.extractColumn(left_col_num_inner);
  std::vector<GridNode *> inner_right = inner.extractColumn(right_col_num_inner);

  int inner_left_size = inner_left.size();
  int inner_right_size = inner_right.size();
  GridNode *foo = inner_right[0];
  GridNode *bar = original_right[0];

  for (int i = 0; i < original_left.size(); i++)
  {
    // std::cout << "original_left " << i << original_left[i]->data.data[0][0] << std::endl;
    // std::cout << "inner_left " << i << inner_left[i]->data.data[0][0] << std::endl;
    original_left[i]->next = inner_left[i];
    inner_left[i]->prev = original_left[i];

    // std::cout << "original_right " << i << original_right[i]->data.data[0][0] << std::endl;
    //  std::cout << "inner_right " << i << inner_right[i]->data.data[0][0] << std::endl;
    inner_right[i]->next = original_right[i];
    original_right[i]->prev = inner_right[i];
  }
   dimx = dimx + inner.dimx;

  inner.setNorthWest(NULL);
  inner.setSouthEast(NULL);
  inner.dimx=0;
  inner.dimy=0;

  // enter your code here
  //extractColumn(northwest,1);
}

// inner list must have the same horizontal resolution, horizontal block dimension, and block size
// if this list has an odd number of row blocks, then the bottom side will have more blocks
// PRE:  this list and inner are not the same physical list
//       this list must have at least two row blocks
//       inner list must have at least one row block
//       inner list must have same horizontal resolution, horizontal block dimension, and block size
// POST: this list has nodes of the entire inner list in between the upper and lower halves of this list
//         and inner list becomes empty
//       otherwise both lists are not modified
// THIS MUST BE ACHIEVED USING POINTER REASSIGNMENTS.
// DO NOT ALLOCATE OR DELETE ANY NODES IN THIS FUNCTION.
void GridList::Sandwich_V(GridList &inner)
{
  // enter your code here
}

// PRE:  this list and otherlist have the same pixel dimensions, block dimensions, and block size
// POST: this list and otherlist are checkered with each other's nodes
//       each list's dimensions remain the same
// THIS MUST BE ACHIEVED USING POINTER REASSIGNMENTS.
// DO NOT ALLOCATE OR DELETE ANY NODES IN THIS FUNCTION.
void GridList::CheckerSwap(GridList &otherlist)
{
  // enter your code here
}

// POST: this list has the negative effect applied selectively to GridNodes to form
//         a checkerboard pattern.
//       The northwest block is normal (does not have the negative effect applied).
// Ensure that the checkering looks correct for both odd and even horizontal block dimensions
void GridList::CheckerN()
{
  if (northwest == NULL)
  {
    return;
  }
  GridNode *curr = northwest;

  for (int row = 0; row < dimy; row++)
  {
    if (row % 2 == 0)
    {
      checkerBoardRow(curr, false, dimx);
    }
    else
    {
      checkerBoardRow(curr, true, dimx);
    }

    for (int col = 0; col < dimx; col++)
    {
      curr = curr->next;
    }
  }
}

// Deallocates any dynamic memory associated with this list
//   and re-initializes this list to an empty state
void GridList::Clear()
{
  // enter your code here
}

// Allocates new nodes into this list as copies of all nodes from otherlist
void GridList::Copy(const GridList &otherlist)
{
  // enter your code here
}

// IMPLEMENT ANY PRIVATE FUNCTIONS YOU HAVE ADDED BELOW
//
//

void GridList::checkerBoardRow(GridNode *startNode, bool flag, int rowLen)
{
  GridNode *curr = startNode;
  for (int i = 0; i < rowLen; i++)
  {
    if (flag)
    {
      curr->data.Negative();
    }
    flag = !flag;
    curr = curr->next;
  }
}

std::vector<GridNode *> GridList::extractColumn(int column)
{
  std::vector<GridNode *> res;
  GridNode *curr = northwest;
  for (int row = 0; row < dimy; row++)
  {
    for (int col = 0; col < dimx; col++)
    {
      if (col == column)
      {
        res.push_back(curr);
      }
      curr = curr->next;
    }
  }
  return res;
}

void GridList::setNorthWest(GridNode *start)
{
  northwest = start;
}

void GridList::setSouthEast(GridNode *end)
{
  southeast = end;
}