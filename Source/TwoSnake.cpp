#include "Snake.hpp"
#include "IconManage.hpp"
#include "TwoSnake.hpp"
#include "Score.hpp"
#include "Highscore.hpp"

Snake Drawww;
IconManage Iconnn;
Highscore readd;

void TwoSnake::init(){
  for(int i = 0; i < GRID_WIDTH; ++i){
    for(int j = 0; j < GRID_HEIGHT; ++j) grid[i][j] = Block::Empty;
  }
  srand(time(NULL));
  apple = IMG_Load("res/apple.png");
  board = IMG_Load("background/MyBoard2.jpg");
  line = IMG_Load("background/Linennnn.png");

  window = SDL_CreateWindow("SnakeGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                          SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  refresh();

  Iconnn.init(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
  Drawww.init();
  GameLoop();
  SDL_FreeSurface(apple);
  SDL_FreeSurface(board);
  SDL_FreeSurface(line);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
}

void TwoSnake::refresh(){
  speed = 2;
  actualGrow = 0;
  Size = 0;
  Grow = 0;
  alive = true;
  cnt = 0, fps = 0;
  isPause = 0;
  score = 0;
  dir = Move::none;
  last_dir = Move::none;

  for(int i = 0; i < GRID_WIDTH; ++i){
    for(int j = 0; j < GRID_HEIGHT; ++j) grid[i][j] = Block::Empty;
  }

  body.clear();
  food.clear();
  Size = 4;
  Head = {GRID_WIDTH / 2 - 2, GRID_HEIGHT / 2};
  pos.x = Head.x * 10; pos.y = Head.y * 10;
  for(int i = 1; i <= 3; ++i) body.push_back({Head.x - i, Head.y});
  grid[Head.x][Head.y] = Block::Head;
  for(SDL_Point p : body) grid[p.x][p.y] = Block::Body;
  cnt = 0;
  for(int i = 0; i < 5; ++i) GenerateFood();
}

void TwoSnake::GameLoop(){
  Uint32 before, second = SDL_GetTicks(), after;
  int frame_time, frames = 0;
  while(running){
    before = SDL_GetTicks();
    PollEvents();
    Update();
    Render();
    frames++;
    after = SDL_GetTicks();
    frame_time = after - before;

    if (after - second >= 1000) {
        fps = frames;
        frames = 0;
        second = after;
    }
//    SDL_Delay(30);
    if(FRAME_RATE > frame_time){ SDL_Delay(FRAME_RATE - frame_time); }

  }
  Iconnn.free();
  Drawww.free();
}

void TwoSnake::GenerateFood(){
  int x, y;
  while(1){
    x = rand() % (GRID_WIDTH);
    y = rand() % (GRID_HEIGHT);

    if(y < 2) continue;

    if(grid[x][y] == Block::Empty){
      grid[x][y] = Block::Food;
      food.insert(pii(x, y));
      break;
    }
  }
}

void TwoSnake::PollEvents(){
  SDL_Event e;
  while(SDL_PollEvent(&e)){
    if(e.type == SDL_QUIT) running = false;

    if(e.type == SDL_MOUSEBUTTONDOWN){
      if(isPause == 0) break;
      int xm = e.button.x;
      int ym = e.button.y;
      if(Iconnn.CheckFocusWithRect(xm, ym, Iconnn.pos[0])){
        isPause = 0;
        break;
      }
      else if(Iconnn.CheckFocusWithRect(xm, ym, Iconnn.pos[1])){
        running = false;
        break;
      }
      else if(Iconnn.CheckFocusWithRect(xm, ym, Iconnn.pos[3])){
        isPause = 0;
        refresh();
        break;
      }
    }

    if(e.type == SDL_KEYDOWN){
      switch(e.key.keysym.sym){
        case SDLK_UP:
          if(isPause) break;
          if(last_dir != Move::down){
            dir = Move::up;
            pos.y = Head.y * 10 - 2;
          }
          break;
        case SDLK_DOWN:
          if(isPause) break;
          if(last_dir != Move::up){
            dir = Move::down;
            pos.y = Head.y * 10 + 2;
          }
          break;
        case SDLK_LEFT:
          if(isPause) break;
          if(last_dir != Move::right){
            dir = Move::left;
            pos.x = Head.x * 10 - 2;
          }
          break;
        case SDLK_RIGHT:
          if(isPause) break;
          if(last_dir != Move::left){
            dir = Move::right;
            pos.x = Head.x * 10 + 2;
          }
          break;
        case SDLK_ESCAPE:
          isPause = 1;
          break;
      }
    }
  }
}

void TwoSnake::Update(){
  if(isPause) return;
  if(alive == false) return;
  if(dir == Move::none) return;
  cnt++;
  switch(dir){
    case Move::up:
      pos.y -= speed;
      break;
    case Move::down:
      pos.y += speed;
      break;
    case Move::left:
      pos.x -= speed;
      break;
    case Move::right:
      pos.x += speed;
      break;
  }
  ii tmp;
  tmp.first = (double)pos.x / 10; tmp.second = (double)pos.y / 10;
  int new_x, new_y;

  if(abs(tmp.first - Head.x) >= 1) new_x = tmp.first;
  else new_x = Head.x;
  if(abs(tmp.second - Head.y) >= 1) new_y = tmp.second;
  else new_y = Head.y;

  if(new_x < 0) pos.x = (GRID_WIDTH - 1) * 10;
  else if(new_x >= GRID_WIDTH) pos.x = 0;
  if(new_y < 2) pos.y = (GRID_HEIGHT - 1) * 10;
  else if(new_y >= GRID_HEIGHT) pos.y = 2 * 10;

  tmp.first = (double)pos.x / 10; tmp.second = (double)pos.y / 10;

  if(abs(tmp.first - Head.x) >= 1) new_x = tmp.first;
  else new_x = Head.x;
  if(abs(tmp.second - Head.y) >= 1) new_y = tmp.second;
  else new_y = Head.y;

  if(Head.x != new_x || Head.y != new_y){
    last_dir = dir;
    if(Grow > 0){
      body.push_front(Head);
      Grow--;
      grid[Head.x][Head.y] = Block::Body;
    }
    else{
      body.push_front(Head);
      grid[body.back().x][body.back().y] = Block::Empty;
      body.pop_back();
      for(int i = 0; i < (int)body.size(); ++i) grid[body[i].x][body[i].y] = Block::Body;
    }
  }

  Head.x = new_x;
  Head.y = new_y;

  Block &next = grid[Head.x][Head.y];

  if(next == Block::Food){
    actualGrow++;
    score++;
    if(actualGrow % 3 == 0) Grow++;
    food.erase({Head.x, Head.y});
    GenerateFood();
    Move new_dir;
    SDL_Point last = body.back();
    SDL_Point Adj_last;
    if((int)body.size() > 1) Adj_last = body[(int)body.size() - 2];
    else Adj_last = Head;
    SDL_Point respective = {Adj_last.x - last.x, Adj_last.y - last.y};

    if(respective.x == 1 && respective.y == 0) new_dir = Move::left;
    else if(respective.x == -1 && respective.y == 0) new_dir = Move::right;
    else if(respective.x == 0 && respective.y == 1) new_dir = Move::up;
    else new_dir = Move::down;

    dir = new_dir;
    last_dir = dir;
    next = Block::Body;
    SDL_Point tail = body.back(); body.pop_back();
    SDL_Point temp = Head;
    Head = tail;
    tail = temp;

    int L = 0, R = (int)body.size() - 1;
    while(L < R){
      swap(body[L], body[R]);
      L++;
      R--;
    }

    body.push_back(tail);
    pos.x = Head.x * 10;
    pos.y = Head.y * 10;
    grid[Head.x][Head.y] = Block::Head;
  }
  else if(next == Block::Body){
    alive = false;
    body.clear();
    readd.update(1, score);
    running = false;
  }
  else next = Block::Head;
}

void TwoSnake::DrawSnake(deque<SDL_Point> SnakeBody, SDL_Point head, bool type){
  if(alive == false) return;

  SDL_Rect block;
  block.w = SCREEN_WIDTH / GRID_WIDTH;
  block.h = SCREEN_HEIGHT / GRID_HEIGHT;

  for(int i = 0; i < (int)SnakeBody.size(); ++i){
    block.x = SnakeBody[i].x * block.w;
    block.y = SnakeBody[i].y * block.h;
    if(i == (int)SnakeBody.size() - 1) break;
    SDL_Point next_block, previous_block;
    if(i == 0) next_block = head;
    else next_block = SnakeBody[i - 1];
    previous_block = SnakeBody[i + 1];
    next_block.x = next_block.x;
    next_block.y = next_block.y;
    previous_block.x = previous_block.x;
    previous_block.y = previous_block.y;
    if(previous_block.x == next_block.x) Drawww.DrawSnakeBody(renderer, 0, block, type);
    else if(previous_block.y == next_block.y) Drawww.DrawSnakeBody(renderer, 1, block, type);
    else{
      previous_block.x -= SnakeBody[i].x; previous_block.y -= SnakeBody[i].y;
      next_block.x -= SnakeBody[i].x; next_block.y -= SnakeBody[i].y;
      if(previous_block.x == -1 && next_block.y == -1 || previous_block.y == -1 && next_block.x == -1) Drawww.DrawSnakeBody(renderer, 2, block, type);
      if(previous_block.x == -1 && next_block.y == 1 || previous_block.y == 1 && next_block.x == -1) Drawww.DrawSnakeBody(renderer, 3, block, type);
      if(previous_block.x == 1 && next_block.y == -1 || previous_block.y == -1 && next_block.x == 1) Drawww.DrawSnakeBody(renderer, 4, block, type);
      if(previous_block.x == 1 && next_block.y == 1 || previous_block.y == 1 && next_block.x == 1) Drawww.DrawSnakeBody(renderer, 5, block, type);
    }
  }

  if(Size > 1){
    SDL_Point last = SnakeBody.back();
    SDL_Point Adj_last;
    if((int)SnakeBody.size() > 1) Adj_last = SnakeBody[(int)SnakeBody.size() - 2];
    else Adj_last = head;
    SDL_Point respective = {Adj_last.x - last.x, Adj_last.y - last.y};

    if(respective.x == 1 && respective.y == 0) Drawww.DrawSnakeTail(renderer, 2, block, type);
    else if(respective.x == -1 && respective.y == 0) Drawww.DrawSnakeTail(renderer, 3, block, type);
    else if(respective.x == 0 && respective.y == 1) Drawww.DrawSnakeTail(renderer, 1, block, type);
    else Drawww.DrawSnakeTail(renderer, 0, block, type);
  }


  block.x = head.x * block.w;
  block.y = head.y * block.h;

  if(Size > 1){
    SDL_Point First = head;
    SDL_Point Adj_First = SnakeBody[0];
    SDL_Point respective = {Adj_First.x - First.x, Adj_First.y - First.y};
    if(respective.x == 1 && respective.y == 0) Drawww.DrawSnakeHead(renderer, 3, block, type);
    else if(respective.x == -1 && respective.y == 0) Drawww.DrawSnakeHead(renderer, 2, block, type);
    else if(respective.x == 0 && respective.y == 1) Drawww.DrawSnakeHead(renderer, 0, block, type);
    else Drawww.DrawSnakeHead(renderer, 1, block, type);
  }
}

void TwoSnake::Render(){
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);
  SDL_Rect block;
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, board);
  SDL_RenderCopy(renderer, texture, NULL, NULL);

  texture = SDL_CreateTextureFromSurface(renderer, line);
  block.x = block.y = 0;
  block.w = SCREEN_WIDTH;
  block.h =  2 * (SCREEN_HEIGHT / GRID_HEIGHT);
  SDL_RenderCopy(renderer, texture, NULL, &block);

  texture = SDL_CreateTextureFromSurface(renderer, apple);
  SDL_SetTextureColorMod(texture, 255, 0, 0);

  block.w = SCREEN_WIDTH / GRID_WIDTH;
  block.h = SCREEN_HEIGHT / GRID_HEIGHT;
  SDL_RenderCopy(renderer, texture, NULL, &block);

  for(auto p : food){
    block.w = SCREEN_WIDTH / GRID_WIDTH;
    block.h = SCREEN_HEIGHT / GRID_HEIGHT;
    block.x = p.first * block.w + Add[cnt % 20].first;
    block.y = p.second * block.h + Add[cnt % 20].first;
    block.w = SCREEN_WIDTH / GRID_WIDTH + Add[cnt % 20].second;
    block.h = SCREEN_HEIGHT / GRID_HEIGHT + Add[cnt % 20].second;
    SDL_RenderCopy(renderer, texture, NULL, &block);
  }
  DrawSnake(body, Head, 0);

  if(isPause) Iconnn.Pause(renderer);
  Score().DrawScore2(renderer, score, 0);

  SDL_RenderPresent(renderer);
  SDL_DestroyTexture(texture);
}


