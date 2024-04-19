#include "AISnake.hpp"
#include "Snake.hpp"
#include "Score.hpp"

Snake DrawingTools;

AISnake::AISnake(Game &MyGame){
  if(MyGame.type == 3 || MyGame.type == 2){
    SDL_Point temp = {AISnakeHead.x, AISnakeHead.y -1};
    AIsize = AInSize = 3;
    AISnakeBody.push_back(temp);
    temp = {AISnakeHead.x, AISnakeHead.y - 2};
    AISnakeBody.push_back(temp);
    for(int i = 0; i < Game::GRID_WIDTH; ++i){
      for(int j = 0; j < Game::GRID_HEIGHT; ++j){
        MyGame.grid2[i][j] = Game::Block::Empty;
        if(i == AISnakeHead.x && j == AISnakeHead.y - 1 || i == AISnakeHead.x && j == AISnakeHead.y - 2) MyGame.grid2[i][j] = Game::Block::AIBody;
      }
    }
  }
}

void AISnake::refresh(Game &MyGame){
  DrawingTools.free();
  AISnakeHead = {0, 7};
  AIpos.x = 0; AIpos.y = 7;
  AISnakeBody.clear();

  AIspeed = 0.2;
  AIgrow = 0;
  AIscore = 0;
  AIsize = 1;
  AInSize = 1;
  AIactualGrow = 0;
  isDuplicate = 1;
  isMove = 0;
  AIalive = 1;

  AIPath.clear();
  while((int)qu.size()) qu.pop();
  AIdir = Game::Move::down;
  AIlastdir = Game::Move::down;

  SDL_Point temp = {AISnakeHead.x, AISnakeHead.y -1};
  AIsize = AInSize = 3;
  AISnakeBody.push_back(temp);
  temp = {AISnakeHead.x, AISnakeHead.y - 2};
  AISnakeBody.push_back(temp);
  for(int i = 0; i < Game::GRID_WIDTH; ++i){
    for(int j = 0; j < Game::GRID_HEIGHT; ++j){
      MyGame.grid2[i][j] = Game::Block::Empty;
      if(i == AISnakeHead.x && j == AISnakeHead.y - 1 || i == AISnakeHead.x && j == AISnakeHead.y - 2) MyGame.grid2[i][j] = Game::Block::AIBody;
    }
  }
  DrawingTools.init();
  if(MyGame.type == 3) MyGame.duplicateFood2();
}

vector<int> AISnake::BFS(int x, int y, int u, int v, Game::Move CurrentDir, bool type){
  memset(f, -1, sizeof f);
  memset(forbid, 0, sizeof forbid);

  f[x][y] = 0;
  qu.push({x, y, CurrentDir});
  Game::Move lastDir = CurrentDir;
  if(type){
    for(int i = 0; i < (int)AISnakeBody.size(); ++i){
      SDL_Point cur = AISnakeBody[i];
      if(i == (int)AISnakeBody.size() - 1) continue;
      forbid[cur.x][cur.y] = 1;
    }
  }
  while(qu.size()){
    int nx = qu.front().u;
    int ny = qu.front().v;
    Game::Move Dir = qu.front().Dir;
    qu.pop();

    for(int index = 0; index <= 3; index++){
      int toX = nx + AIdirX[index];
      int toY = ny + AIdirY[index];
      if(toX >= Game::GRID_WIDTH) toX = 0;
      else if(toX < 0) toX = Game::GRID_WIDTH - 1;

      if(toY >= Game::GRID_HEIGHT) toY = 5;
      else if(toY < 5) toY = Game::GRID_HEIGHT - 1;

      if(Dir == Game::Move::up && index == 1) continue;
      else if(Dir == Game::Move::down && index == 0) continue;
      else if(Dir == Game::Move::left && index == 2) continue;
      else if(Dir == Game::Move::right && index == 3) continue;

      if(type){
        if(forbid[toX][toY]) continue;
      }

      if(f[toX][toY] == -1 || f[toX][toY] > f[nx][ny] + 1){
        f[toX][toY] = f[nx][ny] + 1;
        if(index == 0){
          qu.push({toX, toY, Game::Move::up});
          trace[toX][toY] = {nx, ny, Game::Move::up};
        }
        else if(index == 1){
          qu.push({toX, toY, Game::Move::down});
          trace[toX][toY] = {nx, ny, Game::Move::down};
        }
        else if(index == 2){
          qu.push({toX, toY, Game::Move::right});
          trace[toX][toY] = {nx, ny, Game::Move::right};
        }
        else if(index == 3){
          qu.push({toX, toY, Game::Move::left});
          trace[toX][toY] = {nx, ny, Game::Move::left};
        }
      }
    }
  }

  vector<int> res;

  if(f[u][v] == -1 && type == 1) return BFS(x, y, u, v, CurrentDir, 0);
  else if(f[u][v] == -1 && type == 0){
    if(CurrentDir == Game::Move::up) res.push_back(0);
    else if(CurrentDir == Game::Move::down) res.push_back(1);
    else if(CurrentDir == Game::Move::left) res.push_back(2);
    else if(CurrentDir == Game::Move::right) res.push_back(3);
    return res;
  }

  while(u != x || v != y){
    if(trace[u][v].Dir == Game::Move::up) res.push_back(0);
    if(trace[u][v].Dir == Game::Move::down) res.push_back(1);
    if(trace[u][v].Dir == Game::Move::right) res.push_back(2);
    if(trace[u][v].Dir == Game::Move::left) res.push_back(3);

    Data temp = trace[u][v];
    u = temp.u;
    v = temp.v;
  }

  return res;
}

void AISnake::getPath(SDL_Point Start, SDL_Point End){ AIPath = BFS(Start.x, Start.y, End.x, End.y, AIdir, 1); }

void AISnake::AINextDir(){
  int temp = AIPath.back();
  AIPath.pop_back();
  if(temp == 0) AIdir = Game::Move::up;
  else if(temp == 1) AIdir = Game::Move::down;
  else if(temp == 2) AIdir = Game::Move::right;
  else AIdir = Game::Move::left;
}

void AISnake::GrowBody(int x){AIgrow += x;}

void AISnake::AIMovement(Game &MyGame){
  if(MyGame.isPause) return;
  if(AIalive == false || MyGame.GameTime == 0){
    MyGame.attend2 = 0;
    return;
  }

  if(MyGame.type != 2){
    if((int)AIPath.size() == 0){
      if(MyGame.attend2) getPath(AISnakeHead, MyGame.bigfood2);
      else getPath(AISnakeHead, MyGame.food2);
    }
    else if(MyGame.attend2) getPath(AISnakeHead, MyGame.bigfood2);
  }
  else{
    if((int)AIPath.size() == 0){
      if(MyGame.attend) getPath(AISnakeHead, MyGame.bigfood);
      else getPath(AISnakeHead, MyGame.food);
    }
    else if(MyGame.attend) getPath(AISnakeHead, MyGame.bigfood);
  }

  if(isMove){
    AINextDir();
    isMove = 0;
  }

  switch(AIdir){
    case MyGame.Move::up:
      AIpos.y -= AIspeed;
      AIpos.x = floorf(AIpos.x);
      break;
    case MyGame.Move::down:
      AIpos.y += AIspeed;
      AIpos.x = floorf(AIpos.x);
      break;
    case MyGame.Move::left:
      AIpos.x -= AIspeed;
      AIpos.y = floorf(AIpos.y);
      break;
    case MyGame.Move::right:
      AIpos.x += AIspeed;
      AIpos.y = floorf(AIpos.y);
      break;
  }

  int new_x = AIpos.x;
  int new_y = AIpos.y;

  if(new_x < 0) AIpos.x = MyGame.GRID_WIDTH - 1;
  else if(new_x > MyGame.GRID_WIDTH - 1) AIpos.x = 0;

  if(new_y < 5) AIpos.y = MyGame.GRID_HEIGHT - 1;
  else if(new_y > MyGame.GRID_HEIGHT - 1) AIpos.y = 5;

  new_x = AIpos.x;
  new_y = AIpos.y;

  if(new_x != AISnakeHead.x || new_y != AISnakeHead.y){
    isMove = 1;
    AIlastdir = AIdir;
    if(AIgrow > 0){
      AIsize++;
      AInSize++;
      if(AInSize >= 5){
        AIspeed += 0.01;
        AInSize -= 5;
      }
      AISnakeBody.push_front(AISnakeHead);
      AIgrow--;
      MyGame.grid2[AISnakeHead.x][AISnakeHead.y] = MyGame.Block::AIBody;
    }
    else{
      AISnakeBody.push_front(AISnakeHead);
      MyGame.grid2[AISnakeBody.back().x][AISnakeBody.back().y] = MyGame.Block::Empty;
      AISnakeBody.pop_back();
      for(int i = 0; i < (int)AISnakeBody.size(); ++i){
        SDL_Point free = AISnakeBody[i];
        MyGame.grid2[free.x][free.y] = MyGame.Block::AIBody;
        free = AISnakeBody[i];
      }
    }
  }

  AISnakeHead.x = new_x;
  AISnakeHead.y = new_y;
  Mix_Chunk* crunch_sound;

  if(MyGame.type != 2){
    Game::Block &next = MyGame.grid2[AISnakeHead.x][AISnakeHead.y];
    if(MyGame.timecount2 == 0 && MyGame.bigfood2.x != -1){
      MyGame.grid2[MyGame.bigfood2.x][MyGame.bigfood2.y] = MyGame.Block::Empty;
      MyGame.grid2[MyGame.bigfood2.x][MyGame.bigfood2.y + 1] = MyGame.Block::Empty;
      MyGame.grid2[MyGame.bigfood2.x + 1][MyGame.bigfood2.y] = MyGame.Block::Empty;
      MyGame.grid2[MyGame.bigfood2.x + 1][MyGame.bigfood2.y + 1] = MyGame.Block::Empty;
      MyGame.bigfood2 = {-1, -1};
      MyGame.attend2 = 0;
      AIPath.clear();
    }
    else if(next == MyGame.Block::BigFood){
      crunch_sound = Mix_LoadWAV("Sound/crunch.wav");
      Mix_PlayChannel(-1, crunch_sound, 0);
      AIscore += 5;
      GrowBody(1);
      MyGame.grid2[MyGame.bigfood2.x][MyGame.bigfood2.y] = MyGame.Block::Empty;
      MyGame.grid2[MyGame.bigfood2.x][MyGame.bigfood2.y + 1] = MyGame.Block::Empty;
      MyGame.grid2[MyGame.bigfood2.x + 1][MyGame.bigfood2.y] = MyGame.Block::Empty;
      MyGame.grid2[MyGame.bigfood2.x + 1][MyGame.bigfood2.y + 1] = MyGame.Block::Empty;

      MyGame.bigfood2 = {-1, -1};
      MyGame.attend2 = 0;
      MyGame.timecount2 = 0;
    }

    if((MyGame.cnt + 1) % 1000 == 0 && MyGame.bigfood2.x == -1){ MyGame.duplicateBigFood2(); }

    if(next == MyGame.Block::Food){
      AIactualGrow++;
      crunch_sound = Mix_LoadWAV("Sound/crunch.wav");
      Mix_PlayChannel(-1, crunch_sound, 0);
      AIscore++;
      MyGame.duplicateFood2();
      if(AIactualGrow % 10 == 0) GrowBody(1);
    }
    else if(next == MyGame.Block::AIBody){
      AIalive = false;
      return;
    }
    next = MyGame.Block::AIHead;
  }
  else{
    Game::Block &next = MyGame.grid[AISnakeHead.x][AISnakeHead.y];
    Game::Block &next2 = MyGame.grid2[AISnakeHead.x][AISnakeHead.y];
    if(next == MyGame.Block::BigFood){
      crunch_sound = Mix_LoadWAV("Sound/crunch.wav");
      Mix_PlayChannel(-1, crunch_sound, 0);
      AIscore += 5;
      GrowBody(1);
      MyGame.grid[MyGame.bigfood.x][MyGame.bigfood.y] = MyGame.Block::Empty;
      MyGame.grid[MyGame.bigfood.x][MyGame.bigfood.y + 1] = MyGame.Block::Empty;
      MyGame.grid[MyGame.bigfood.x + 1][MyGame.bigfood.y] = MyGame.Block::Empty;
      MyGame.grid[MyGame.bigfood.x + 1][MyGame.bigfood.y + 1] = MyGame.Block::Empty;

      MyGame.bigfood = {-1, -1};
      MyGame.attend = 0;
      MyGame.timecount = 0;
    }

    if(next == MyGame.Block::Food){
      AIactualGrow++;
      crunch_sound = Mix_LoadWAV("Sound/crunch.wav");
      Mix_PlayChannel(-1, crunch_sound, 0);
      AIscore++;
      next = MyGame.Block::Empty;
      MyGame.duplicateFood();
      if(AIactualGrow % 10 == 0) GrowBody(1);
    }
    else if(next2 == MyGame.Block::AIBody){
      AIalive = false;
      AISnakeBody.clear();
      for(int i = 0; i < MyGame.GRID_WIDTH; ++i){
        for(int j = 0; j < MyGame.GRID_HEIGHT; ++j) MyGame.grid2[i][j] = MyGame.Block::Empty;
      }
      return;
    }
    next2 = MyGame.Block::AIHead;
  }
}

void AISnake::AIRender(Game &MyGame, int tmp){
  if(AIalive == false) return;

  SDL_Rect block;
  if(MyGame.type != 3){
    block.w = Game::SCREEN_WIDTH / Game::GRID_WIDTH;
    block.h = Game::SCREEN_HEIGHT / Game::GRID_HEIGHT;
  }
  else{
    block.w = Game::SCREEN_WIDTH1 / Game::GRID_WIDTH;
    block.h = Game::SCREEN_HEIGHT1 / Game::GRID_HEIGHT;
  }

  for(int i = 0; i < (int)AISnakeBody.size(); ++i){
    block.x = AISnakeBody[i].x * block.w + tmp;
    block.y = AISnakeBody[i].y * block.h;
    if(i == (int)AISnakeBody.size() - 1) break;
    SDL_Point next_block, previous_block;
    if(i == 0) next_block = AISnakeHead;
    else next_block = AISnakeBody[i - 1];
    previous_block = AISnakeBody[i + 1];
    if(previous_block.x == next_block.x) DrawingTools.DrawSnakeBody(MyGame.renderer, 0, block, 1);
    else if(previous_block.y == next_block.y) DrawingTools.DrawSnakeBody(MyGame.renderer, 1, block, 1);
    else{
      previous_block.x -= AISnakeBody[i].x; previous_block.y -= AISnakeBody[i].y;
      next_block.x -= AISnakeBody[i].x; next_block.y -= AISnakeBody[i].y;
      if(previous_block.x == -1 && next_block.y == -1 || previous_block.y == -1 && next_block.x == -1) DrawingTools.DrawSnakeBody(MyGame.renderer, 2, block, 1);
      if(previous_block.x == -1 && next_block.y == 1 || previous_block.y == 1 && next_block.x == -1) DrawingTools.DrawSnakeBody(MyGame.renderer, 3, block, 1);
      if(previous_block.x == 1 && next_block.y == -1 || previous_block.y == -1 && next_block.x == 1) DrawingTools.DrawSnakeBody(MyGame.renderer, 4, block, 1);
      if(previous_block.x == 1 && next_block.y == 1 || previous_block.y == 1 && next_block.x == 1) DrawingTools.DrawSnakeBody(MyGame.renderer, 5, block, 1);
    }
  }

  if(AIsize > 1){
    SDL_Point last = AISnakeBody.back();
    SDL_Point Adj_last;
    if((int)AISnakeBody.size() > 1) Adj_last = AISnakeBody[(int)AISnakeBody.size() - 2];
    else Adj_last = AISnakeHead;
    SDL_Point respective = {Adj_last.x - last.x, Adj_last.y - last.y};

    if(respective.x == 1 && respective.y == 0) DrawingTools.DrawSnakeTail(MyGame.renderer, 2, block, 1);
    else if(respective.x == -1 && respective.y == 0) DrawingTools.DrawSnakeTail(MyGame.renderer, 3, block, 1);
    else if(respective.x == 0 && respective.y == 1) DrawingTools.DrawSnakeTail(MyGame.renderer, 1, block, 1);
    else DrawingTools.DrawSnakeTail(MyGame.renderer, 0, block, 1);
  }


  block.x = AISnakeHead.x * block.w + tmp;
  block.y = AISnakeHead.y * block.h;
  if(AIsize > 1){
    SDL_Point First = AISnakeHead;
    SDL_Point Adj_First = AISnakeBody[0];
    SDL_Point respective = {Adj_First.x - First.x, Adj_First.y - First.y};
    if(respective.x == 1 && respective.y == 0) DrawingTools.DrawSnakeHead(MyGame.renderer, 3, block, 1);
    else if(respective.x == -1 && respective.y == 0) DrawingTools.DrawSnakeHead(MyGame.renderer, 2, block, 1);
    else if(respective.x == 0 && respective.y == 1) DrawingTools.DrawSnakeHead(MyGame.renderer, 0, block, 1);
    else DrawingTools.DrawSnakeHead(MyGame.renderer, 1, block, 1);
  }
  else{
    if(AIdir == Game::Move::up) DrawingTools.DrawSnakeHead(MyGame.renderer, 0, block, 1);
    else if(AIdir == Game::Move::down) DrawingTools.DrawSnakeHead(MyGame.renderer, 1, block, 1);
    else if(AIdir == Game::Move::right) DrawingTools.DrawSnakeHead(MyGame.renderer, 2, block, 1);
    else DrawingTools.DrawSnakeHead(MyGame.renderer, 3, block, 1);
  }
  if(MyGame.type != 2) Score().DrawScore1(MyGame.renderer, AIscore, 600);
}
