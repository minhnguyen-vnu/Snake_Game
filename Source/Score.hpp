#pragma once
#include "admin.hpp"
#include <SDL_ttf.h>

class Score{
public:
  TTF_Font* fontt;
  void init();
  void free();
  void DrawScore(SDL_Renderer* gRenderer, int score, int tmp);
  void DrawTime(SDL_Renderer* gRenderer, int cst, int tm, int tmp);
  void DrawScore1(SDL_Renderer* gRenderer, int score, int tmp);
  void DrawTime1(SDL_Renderer* gRenderer, int cst, int tm, int tmp);
  void DrawScore2(SDL_Renderer* gRenderer, int score, int tmp);
  void DrawScore3(SDL_Renderer* gRenderer, int score1, int score2, int tmp);
};
