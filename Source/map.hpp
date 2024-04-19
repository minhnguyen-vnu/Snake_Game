#include<SDL.h>
#include<bits/stdc++.h>

using namespace std;

class MAP{
public:
  const int SCREEN_WIDTH = 640;
  const int SCREEN_HEIGHT = 640;
  const int CELL_SIZE = 40;
  const int BOARD_SIZE = 16;

  SDL_Window* gWindow = NULL;
  SDL_Renderer* gRenderer = NULL;

  bool initSDL();
  void drawBoard();
  void CreateMap();
};
