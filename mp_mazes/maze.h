/* Your code here! */
#pragma once
#include "dsets.h"
#include <vector>
#include "cs225/PNG.h"
using namespace cs225;
class SquareMaze{
public:
  SquareMaze();
  void makeMaze(int width, int height);
  bool canTravel(int x, int y, int dir) const;
  void setWall(int x, int y, int dir, bool exists);
  std::vector<int> solveMaze();
  PNG* drawMaze() const;
  PNG* drawMazeWithSolution();
private:
  int width_; 
  int height_;
  int size;
  int longestPath;
  DisjointSets set;
  std::vector<bool> right;
  std::vector<bool> down;
};