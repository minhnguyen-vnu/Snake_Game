#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include<bits/stdc++.h>

#define PLAY 0
#define EXIT 1
#define PAUSE 2
#define AGAIN 3

using namespace std;

struct IconManage{
  SDL_Texture* playIcon;
  SDL_Texture* exitIcon;
  SDL_Texture* pauseMenu;
  SDL_Texture* again;
  SDL_Rect pos[6];

  void init(SDL_Renderer* &renderer, int w, int h);
  void Pause(SDL_Renderer* &renderer);
  bool CheckFocusWithRect(int x, int y, SDL_Rect rect);
  void free();
  SDL_Texture* LoadTexture(SDL_Renderer* &renderer, string path);
};
