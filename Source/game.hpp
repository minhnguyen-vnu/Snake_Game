#pragma once
#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>

using namespace std;

#define ii pair<double, double>

class Game{
public:
  void Run();
  int GetSize();
  void duplicateFood();
  void duplicateBigFood();
  void duplicateBigFood2();
  void duplicateFood2();
  void GrowBody(int q);
  void UpdateWindowTitle();
  void GameLoop();
  void PollEvents();
  void Update();
  void Render();
  void close();
  void DrawSnake();
  bool ok(int x, int y);
  bool ok2(int x, int y);
  void refresh();

  bool running = true;
  bool alive = false;
  int fps = 0;
  bool AI_refresh = 1;

  static const int FRAME_RATE     = 1000 / 60;
  static const int SCREEN_WIDTH   = 800;
  static const int SCREEN_HEIGHT  = 800;
  static const int GRID_WIDTH     = 25;
  static const int GRID_HEIGHT    = 25;
  static const int SCREEN_WIDTH1  = 500;
  static const int SCREEN_HEIGHT1 = 500;


  SDL_Window* window = NULL;
  SDL_Renderer* renderer = NULL;
  SDL_Surface* backGround = NULL;
  SDL_Surface* Blur = NULL;
  SDL_Surface* imageSurface;
  SDL_Surface* Type4;
  SDL_Surface* AIWIN;
  SDL_Surface* PLAYERWIN;

  enum class Block{Head, Body, Food, Empty, BigFood, AIHead, AIBody};
  enum class Move{none, up, down, left, right};

  Move last_dir = Move::up;
  Move dir  = Move::up;

  struct{
    float x = GRID_WIDTH / 2;
    float y = GRID_HEIGHT / 2;
  }pos;
  Block grid[GRID_WIDTH][GRID_HEIGHT];
  Block grid2[GRID_WIDTH][GRID_HEIGHT];
  SDL_Point head = {pos.x, pos.y};
  SDL_Point food, food2;
  SDL_Point bigfood = {-1, -1}, bigfood2 = {-1, -1};
  deque<SDL_Point> body;

  double speed = 0.2;
  int grow = 0;
  int score = 0;
  int size = 1;
  int nSize = 1;
  int actualGrow = 0;
  int cnt = 0;
  bool attend = 0, attend2 = 0;
  int timecount = 0, timecount2 = 0;
  int type = 3;
  int GameTime = 59;
  int isMove = 0;
  vector<int> AIPath;
  bool notice = 0;
  bool isPause = 0;

  int dirX[9] = {0, 0, -1, -1, -1, 1, 1, 1};
  int dirY[9] = {1, -1, 1, 0, -1, 1, 0, -1};
  ii Add[30] = {ii(-6, 13), ii(-6.2, 13.2), ii(-6.4, 13.4), ii(-6.6, 13.6), ii(-6.8, 13.8), ii(-7, 14), ii(-7.2, 14.2), ii(-7.4, 14.4), ii(-7.6, 14.6), ii(-7.8, 14.8), ii(-8, 15), ii(-8.2, 15.2), ii(-8.4, 15.4), ii(-8.6, 15.6), ii(-8.8, 15.8), ii(-9, 16), ii(-9.2, 16.2), ii(-9.4, 16.4), ii(-9.6, 16.6), ii(-9.8, 16.8), ii(-10, 17), ii(-10, 17), ii(-10.1, 17.1), ii(-10.2, 17.2), ii(-10.3, 17.3), ii(-10.4, 17.4), ii(-10.5, 17.5)};
};
