#include "game.hpp"

struct AISnake{
public:
  SDL_Point AISnakeHead = {0, 7};
  struct{
    float x = 0;
    float y = 7;
  }AIpos;
  deque<SDL_Point> AISnakeBody;

  double AIspeed = 0.2;
  int AIgrow = 0;
  int AIscore = 0;
  int AIsize = 1;
  int AInSize = 1;
  int AIactualGrow = 0;
  int f[35][35];
  int forbid[35][35];
  int AIdirX[6] = {0, 0, 1, -1};
  int AIdirY[6] = {-1, 1, 0, 0};
  bool isDuplicate = 1;
  bool isMove = 0;
  bool AIalive = 1;

  vector<int> AIPath;

  Game::Move AIdir = Game::Move::down;
  Game::Move AIlastdir = Game::Move::down;

  struct Data{
    int u, v;
    Game::Move Dir;
  };
  queue<Data> qu;
  Data trace[35][35];

  AISnake(Game &MyGame);
  void Init();
  void addEdge(int x, int y, int u, int v);
  vector<int> BFS(int x, int y, int u, int v, Game::Move CurrentDir, bool type);
  void getPath(SDL_Point Start, SDL_Point End);
  void GrowBody(int x);
  void AINextDir();
  void AIMovement(Game &MyGame);
  void AIRender(Game &MyGame, int tmp);
  void refresh(Game &MyGame);
};
