/* Your code here! */
#include "maze.h"
#include <iostream>
#include <vector>
#include <queue>

SquareMaze::SquareMaze(){
    width_=0;
    height_=0;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists){
  if(dir==0){
    right[y*width_+x]=exists;
  }
  if(dir==1){
    down[y*width_+x]=exists;
  }
}

void SquareMaze::makeMaze(int width, int height){
  width_=width;
  height_=height;
  size=width*height;
  set.addelements(size);
  for(int i=0; i <size; i++){
    right.push_back(true);
    down.push_back(true);
  }
  while(set.size(0)!=size){ 
    int rand_width=rand() % width_;
    int rand_height=rand() % height_;
    int rand_cond=rand_height*width_+rand_width;
    if(rand()%2==0){
      if(rand_height!=height_ - 1){
        if(set.find(rand_cond)!=set.find(rand_cond+width_)){
            setWall(rand_width, rand_height, 1, false);
            set.setunion(rand_cond, rand_cond+width_);
        }
      }
    }
    if(rand_width!=width_ - 1){
        if(set.find(rand_cond)!=set.find(rand_cond+1)){
          right[rand_height * width_ + rand_width] = false;
          set.setunion(rand_cond,rand_cond+1);
        }
    }
  }
}

bool SquareMaze::canTravel(int x, int y, int dir) const{
  int rand_cond=y*width_+x;
  if(dir==0){
    if(right[rand_cond]==false){
      return true;
    }
  }
  if(dir==1){
    if(down[rand_cond]==false){
      return true;
    }
  }
  if(dir==2){
    if(x!=0){
      if(right[rand_cond-1]==false){
        return true;
      }
    }
    return false;
  }
  if(dir==3){
    if(y!=0){
      if(down[rand_cond-width_]==false){
        return true;
      }
    }
  }
  return false;
}

std::vector<int> SquareMaze::solveMaze(){
  std::vector<int> length;
  std::vector<int> prev; 
  length.push_back(0);
  prev.push_back(0); 
  for(int i=1; i<size; i++){
    length.push_back(0);
    prev.push_back(-1);
  }
  std::queue<int> search;
  search.push(0);
  int idx;
  while(!search.empty()){
    idx=search.front();
    int ind_width=idx%width_;
    int ind_height=idx/width_;
    search.pop();
    if(canTravel(ind_width,ind_height,0)&&prev[idx+1]<0){
      length[idx+1]=length[idx]+1;
      prev[idx+1]=idx;
      search.push(idx+1);
    }
    if(canTravel(ind_width,ind_height,1)&&prev[idx+width_]<0){
      length[idx+width_]=length[idx]+1;
      prev[idx+width_]=idx;
      search.push(idx+width_);
    }
    if(canTravel(ind_width,ind_height,2)&&prev[idx-1]<0){
      length[idx-1]=length[idx]+1;
      prev[idx-1]=idx;
      search.push(idx-1);
    }
    if(canTravel(ind_width,ind_height,3)&&prev[idx-width_]<0){
      length[idx-width_]=length[idx]+1;
      prev[idx-width_]=idx;
      search.push(idx-width_);
    }
  }
  longestPath=width_*(height_-1);
  for(int j=0; j<width_; j++){
    if(length[longestPath]<length[width_*(height_-1)+j]){
      longestPath=width_*(height_-1)+j;
    }
  }
  idx=longestPath;
  std::vector<int> path;
  while(idx!=0){
    if(prev[idx]==idx-1){
      path.push_back(0);
    }
    if(prev[idx]==idx-width_){
      path.push_back(1);
    }
    if(prev[idx] == idx + 1){
      path.push_back(2);
    }
    if(prev[idx]==idx + width_){
      path.push_back(3);
    }
    idx=prev[idx];
  }
  reverse(path.begin(), path.end());
  return path;
}

PNG* SquareMaze::drawMaze() const{
  PNG* maze=new PNG(width_*10+1,height_*10+1);
  int maze_width=width_*10+1;
  int maze_height=height_*10+1;
  for(int x= 10; x<maze_width; x++){
		HSLAPixel &p=maze->getPixel(x,0);
		p.h=0;
		p.s=0;
		p.l=0;
	}
	for(int y=0; y<maze_height; y++){
		HSLAPixel &p=maze->getPixel(0,y);
		p.h = 0;
		p.s = 0;
		p.l = 0;
	}
	for(int i=0; i<width_; i++){
		for(int j=0; j<height_; j++){
			if(right[j*width_+i]){
				for(int k = 0; k<11;k++){
					HSLAPixel &p=maze->getPixel((i+1)*10,(j*10+k));
					p.h=0;
					p.s=0;
					p.l=0;
				}
			}
			if(down[j*width_+i]){
				for(int l=0; l<11; l++){
					HSLAPixel &p=maze->getPixel((10*i+l),(j+1)*10);
					p.h=0;
					p.s=0;
					p.l=0;
				}
			}
		}
	}
	return maze;
}


PNG* SquareMaze::drawMazeWithSolution(){
  std::vector<int> path=solveMaze();
  PNG* maze=drawMaze();
	int x=5;
	int y=5;
	for(size_t i=0; i<path.size(); i++){
		if(path[i]==0){
      int count=0;
      while(count<10){
        HSLAPixel &p=maze->getPixel(x,y);
        p.h=0;
        p.s=1;
        p.l=0.5;
        x++;
        count++;
      }
		}
		if(path[i]==1){
      int count=0;
      while(count<10){
        HSLAPixel &p=maze->getPixel(x,y);
        p.h=0;
        p.s=1;
        p.l=0.5;
        y++;
        count++;
      }
		}
		if(path[i]==2){
      int count=0;
      while(count<10){
        HSLAPixel &p=maze->getPixel(x,y);
        p.h=0;
        p.s=1;
        p.l=0.5;
        x--;
        count++;
      }
		}
		if(path[i]==3){
      int count=0;
      while(count<10){
        HSLAPixel &p=maze->getPixel(x,y);
        p.h=0;
        p.s=1;
        p.l=0.5;
        y--;
        count++;
      }
		}
	}
  HSLAPixel &p=maze->getPixel(x,y);
  p.h = 0;    
  p.s = 1;
  p.l = 0.5;
  p.a = 1;
  x-=4;
  y+=5;
  int count=1;
  while(count<10){
    HSLAPixel &p=maze->getPixel(x,y);
    p.h=0;
    p.s=0;
    p.l=1;
    p.a=1;
    x++;
    count++;
  }
	return maze;
}