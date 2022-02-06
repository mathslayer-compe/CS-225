#include "Image.h"
#include "StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image sword;
  sword.readFromFile("sword.png");
 /* Image fred;
  fred.readFromFile("15-150170_clip-art-fred-encyclopedia-spongebobia-fandom-my-leg.png");
  Image frog;
  frog.readFromFile("111-1114538_frog-png-red-eyed-tree-frog-png-transparent.png");
  frog.resize(20,30);
  Image bully;
  bully.readFromFile("dance3-01.png");
  */
  StickerSheet stick(sword,4);
  Image mouse;
  mouse.readFromFile("mouse.png");
  stick.addSticker(mouse, 420,300);
  Image motorcycle;
  motorcycle.readFromFile("motorcycle.png");
  stick.addSticker(motorcycle, 200,0);
  Image pong;
  pong.readFromFile("pong.png");
  stick.addSticker(pong, 50,150);
  Image result=stick.render();
  result.writeToFile("myImage.png");
  return 0;
}
