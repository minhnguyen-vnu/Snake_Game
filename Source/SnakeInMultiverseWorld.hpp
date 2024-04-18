#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include<bits/stdc++.h>

using namespace std;

#define pii pair<int, int>
#define ii pair<double, double>

struct Multi{
  static const int FRAME_RATE     = 1000 / 70;
  static const int SCREEN_WIDTH   = 792;
  static const int SCREEN_HEIGHT  = 648;
  static const int GRID_WIDTH     = 22;
  static const int GRID_HEIGHT    = 18;

  SDL_Window* window = NULL;
  SDL_Renderer* renderer = NULL;
  SDL_Surface* apple;
  SDL_Surface* board;
  SDL_Surface* brick;
  SDL_Surface* line;
  Mix_Music *music;

  enum class Block{
    Head,
    Body,
    Food,
    brick,
    Empty
  };
  enum class Move{
    up,
    down,
    left,
    right,
    none
  };
  Move dir = Move::none;
  Move last_dir = Move::none;
  Block grid[30][30];
  SDL_Point Head;
  struct{
    int x;
    int y;
  }pos;
  deque<SDL_Point> body;
  set<pii> food;
  vector<pii> brick_list;

  int speed = 4;
  int actualGrow = 0;
  int Size = 0;
  int Grow = 0;
  bool alive = true;
  bool running = true;
  int cnt = 0, fps = 0;
  bool isPause = 0;
  int score = 0;
  int Level = 1;
  int barrier = 0;
  int comp[35][35];
  int cp = 0, ap = 0;
  bool success = 1, win = 0;
  bool escape = 0;

  void init();
  void GenerateBarrier();
  void GenerateFood();
  void PollEvents();
  void Update();
  void DrawSnake(deque<SDL_Point> SnakeBody, SDL_Point head, bool type);
  void Render();
  void GameLoop();
  void refresh();
  void makeGraph();
  void dfs(int u, int v, int num);
  void genMap();
  void play();
//  SDL_Point Convert(pii P, Move dir)

  int dx[5] = {0, -1, 1, 0};
  int dy[5] = {1, 0, 0, -1};
  ii Add[30] = {ii(-6, 13), ii(-6.2, 13.2), ii(-6.4, 13.4), ii(-6.6, 13.6), ii(-6.8, 13.8), ii(-7, 14), ii(-7.2, 14.2), ii(-7.4, 14.4), ii(-7.6, 14.6), ii(-7.8, 14.8), ii(-8, 15), ii(-8.2, 15.2), ii(-8.4, 15.4), ii(-8.6, 15.6), ii(-8.8, 15.8), ii(-9, 16), ii(-9.2, 16.2), ii(-9.4, 16.4), ii(-9.6, 16.6), ii(-9.8, 16.8), ii(-10, 17), ii(-10, 17), ii(-10.1, 17.1), ii(-10.2, 17.2), ii(-10.3, 17.3), ii(-10.4, 17.4), ii(-10.5, 17.5)};
};

