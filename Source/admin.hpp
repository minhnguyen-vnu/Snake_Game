#pragma once
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL.h>
#include <bits/stdc++.h>
#include "Vector2D.hpp"

using namespace std;

struct Admin{
  static const int MENU_WIDTH     = 1000;
  static const int MENU_HEIGHT    = 800;

  bool running = 1;
  int type;
  int returnValue = 0;
  int type_2;
  bool backButton = 0;
  bool highscoreButton = 0;
  int cnt_music = 0;

  SDL_Window* window = NULL;
  SDL_Renderer* renderer = NULL;

  void free();
  void run();
};

