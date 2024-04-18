#include "InfinityMap.hpp"

void InfinityMap::init(){
  for(int i = 0; i < Game::GRID_WIDTH; ++i) actualCol[i] = virtualCol[i] = i;
  for(int i = 0; i < Game::GRID_HEIGHT; ++i) actualRow[i] = virtualRow[i] = i;
}

void InfinityMap::Move(int dir){
  if(dir == 0){
    for(int i = 0; i < Game::GRID_HEIGHT; ++i){
      virtualRow[i] = (virtualRow[i] + 1) % Game::GRID_HEIGHT;
      actualRow[virtualRow[i]] = i;
    }
  }
  else if(dir == 1){
    for(int i = 0; i < Game::GRID_HEIGHT; ++i){
      virtualRow[i] = (virtualRow[i] - 1 + Game::GRID_HEIGHT) % Game::GRID_HEIGHT;
      actualRow[virtualRow[i]] = i;
    }
  }
  else if(dir == 2){
    for(int i = 0; i < Game::GRID_WIDTH; ++i){
      virtualCol[i] = (virtualCol[i] - 1 + Game::GRID_WIDTH) % Game::GRID_WIDTH;
      actualCol[virtualCol[i]] = i;
    }
  }
  else{
    for(int i = 0; i < Game::GRID_WIDTH; ++i){
      virtualCol[i] = (virtualCol[i] + 1) % Game::GRID_WIDTH;
      actualCol[virtualCol[i]] = i;
    }
  }
}
