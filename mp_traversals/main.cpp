
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  PNG mickey;    
  mickey.readFromFile("mickey.png");
  FloodFilledImage image(mickey);
  DFS dfs1(mickey, Point(0, 0), 0.1);
  DFS dfs2(mickey, Point(119, 0), 0.1);
  DFS dfs3(mickey, Point(0, 144), 0.1);
  DFS dfs4(mickey, Point(60, 55), 0.1);    
  DFS dfs5(mickey, Point(100, 65), 0.1);
  DFS dfs6(mickey, Point(200, 90), 0.1);
  DFS dfs7(mickey, Point(83, 73), 0.1);
  BFS bfs1(mickey, Point(0, 0), 0.1);
  BFS bfs2(mickey, Point(119, 0), 0.1);
  BFS bfs3(mickey, Point(0, 144), 0.1);
  BFS bfs4(mickey, Point(60, 55), 0.1);
  BFS bfs5(mickey, Point(100, 65), 0.1);
  BFS bfs6(mickey, Point(200, 90), 0.1);
  BFS bfs7(mickey, Point(83, 73), 0.1);
  MyColorPicker donald("donald.png");
  SolidColorPicker col(HSLAPixel(420, 0.69, 0.66));
  image.addFloodFill(dfs1, col);
  image.addFloodFill(dfs2, col);
  image.addFloodFill(dfs3, col);
  image.addFloodFill(dfs4, col);
  image.addFloodFill(dfs5, col);
  image.addFloodFill(dfs6, col);
  image.addFloodFill(dfs7, col);
  image.addFloodFill(bfs1, donald);
  image.addFloodFill(bfs2, donald);
  image.addFloodFill(bfs3, donald);
  image.addFloodFill(bfs4, donald);
  image.addFloodFill(bfs5, donald);
  image.addFloodFill(bfs6, donald);
  image.addFloodFill(bfs7, donald);
  Animation animation = image.animate(80000);
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");    
  animation.write("myFloodFill.gif");
  return 0;
}
