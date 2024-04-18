#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include<bits/stdc++.h>

using namespace std;

class Snake{
public:
  SDL_Surface* head_up;
  SDL_Surface* head_down;
  SDL_Surface* head_left;
  SDL_Surface* head_right;

  SDL_Surface* tail_up;
  SDL_Surface* tail_down;
  SDL_Surface* tail_left;
  SDL_Surface* tail_right;

  SDL_Surface* body_vertical;
  SDL_Surface* body_horizontal;
  SDL_Surface* body_topleft;
  SDL_Surface* body_bottomleft;
  SDL_Surface* body_topright;
  SDL_Surface* body_bottomright;

  void init();
  void Draw(SDL_Renderer* gRenderer, SDL_Texture* gTexture, SDL_Rect r);
  void DrawSnakeHead(SDL_Renderer* gRenderer, int dir, SDL_Rect r, bool type);
  void DrawSnakeBody(SDL_Renderer* gRenderer, int dir, SDL_Rect r, bool type);
  void DrawSnakeTail(SDL_Renderer* gRenderer, int dir, SDL_Rect r, bool type);
  void DrawSnakeSmile(SDL_Renderer* gRenderer, int dir, SDL_Rect r, bool type);
  void free();
};
