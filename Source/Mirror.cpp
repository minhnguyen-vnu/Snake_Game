#include "Mirror.hpp"
#include "Snake.hpp"
#include "IconManage.hpp"
#include "Score.hpp"
#include "Highscore.hpp"

Snake Draw;
IconManage Icon;
Highscore readdd;

void Mirror::init(){
  for(int i = 0; i < GRID_WIDTH; ++i){
    for(int j = 0; j < GRID_HEIGHT; ++j) grid[i][j] = Block::Empty;
  }
  srand(time(0));
  apple = IMG_Load("res/apple.png");
  board = IMG_Load("background/MyBoard2.jpg");
  line = IMG_Load("background/Linennnn.png");

  window = SDL_CreateWindow("SnakeGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                          SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (TTF_Init() == -1) return;
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) return;
  refresh();

  Icon.init(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
  Draw.init();
  GameLoop();
  SDL_FreeSurface(apple);
  SDL_FreeSurface(board);
  SDL_FreeSurface(line);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
}

void Mirror::GameLoop(){
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
    if(FRAME_RATE > frame_time){ SDL_Delay(FRAME_RATE - frame_time); }

  }
  Icon.free();
  Draw.free();
}

void Mirror::GenerateFood(){
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

void Mirror::refresh(){
  for(int i = 0; i < GRID_WIDTH; ++i){
    for(int j = 0; j < GRID_HEIGHT; ++j) grid[i][j] = Block::Empty;
  }

  speed = 2;
  actualGrow = 0;
  Size = 0;
  Grow = 0;
  alive = true;
  running = true;
  cnt = 0, fps = 0;
  isPause = 0;
  score = 0;

  dir = Move::none;
  last_dir = Move::none;

  body.clear();
  mbody.clear();
  food.clear();
  Size = 4;
  Head = {GRID_WIDTH / 2 - 2, GRID_HEIGHT / 2};
  MirrorHead = {GRID_WIDTH / 2 + 1, GRID_HEIGHT / 2};
  pos.x = Head.x * 10; pos.y = Head.y * 10;
  mpos.x = MirrorHead.x * 10, mpos.y = MirrorHead.y * 10;
  for(int i = 1; i <= 3; ++i){
    body.push_back({Head.x - i, Head.y});
    mbody.push_back({MirrorHead.x + i, MirrorHead.y});
  }
  grid[Head.x][Head.y] = Block::Head;
  grid[MirrorHead.x][MirrorHead.y] = Block::MirrorHead;
  for(SDL_Point p : body) grid[p.x][p.y] = Block::Body;
  for(SDL_Point p : mbody) grid[p.x][p.y] = Block::MirrorBody;
  cnt = 0;
  for(int i = 0; i < 5; ++i) GenerateFood();
}

void Mirror::PollEvents(){
  SDL_Event e;
  while(SDL_PollEvent(&e)){
    if(e.type == SDL_QUIT) running = false;

    if(e.type == SDL_MOUSEBUTTONDOWN){
      if(isPause == 0) break;
      int xm = e.button.x;
      int ym = e.button.y;
      if(Icon.CheckFocusWithRect(xm, ym, Icon.pos[0])){
        isPause = 0;
        break;
      }
      else if(Icon.CheckFocusWithRect(xm, ym, Icon.pos[1])){
        running = false;
        break;
      }
      else if(Icon.CheckFocusWithRect(xm, ym, Icon.pos[3])){
        isPause = 0;
        refresh();
        break;
      }
    }

    if(e.type == SDL_KEYDOWN){
      switch(e.key.keysym.sym){
        case SDLK_UP:
          if(isPause) break;
          if(last_dir != Move ::down){
            dir = Move::up;
            pos.y = Head.y * 10 - 2;
            mpos.y = MirrorHead.y * 10 + 2;
          }
          break;
        case SDLK_DOWN:
          if(isPause) break;
          if(last_dir != Move::up){
            dir = Move::down;
            pos.y = Head.y * 10 + 2;
            mpos.y = MirrorHead.y * 10 - 2;
          }
          break;
        case SDLK_LEFT:
          if(isPause) break;
          if(last_dir != Move::right){
            dir = Move::left;
            pos.x = Head.x * 10 - 2;
            mpos.x = MirrorHead.x * 10 + 2;
          }
          break;
        case SDLK_RIGHT:
          if(isPause) break;
          if(last_dir != Move::left){
            dir = Move::right;
            pos.x = Head.x * 10 + 2;
            mpos.x = MirrorHead.x * 10 - 2;
          }
          break;
        case SDLK_ESCAPE:
          isPause = 1;
          break;
      }
    }
  }
}

void Mirror::Update(){
  if(isPause) return;
  if(alive == false) return;
  if(dir == Move::none) return;
  cnt++;
  switch(dir){
    case Move::up:
      pos.y -= speed;
      mpos.y += speed;
      break;
    case Move::down:
      pos.y += speed;
      mpos.y -= speed;
      break;
    case Move::left:
      pos.x -= speed;
      mpos.x += speed;
      break;
    case Move::right:
      pos.x += speed;
      mpos.x -= speed;
      break;
  }
  ii tmp, _tmp;
  tmp.first = (double)pos.x / 10; tmp.second = (double)pos.y / 10;
  _tmp.first = (double)mpos.x / 10; _tmp.second = (double)mpos.y / 10;
  int new_x, _new_x, new_y, _new_y;


  if(abs(tmp.first - Head.x) >= 1) new_x = tmp.first;
  else new_x = Head.x;
  if(abs(tmp.second - Head.y) >= 1) new_y = tmp.second;
  else new_y = Head.y;

  if(abs(_tmp.first - MirrorHead.x) >= 1) _new_x = _tmp.first;
  else _new_x = MirrorHead.x;
  if(abs(_tmp.second - MirrorHead.y) >= 1) _new_y = _tmp.second;
  else _new_y = MirrorHead.y;

  if(new_x < 0) pos.x = (GRID_WIDTH - 1) * 10;
  else if(new_x >= GRID_WIDTH) pos.x = 0;
  if(new_y < 2) pos.y = (GRID_HEIGHT - 1) * 10;
  else if(new_y >= GRID_HEIGHT) pos.y = 2 * 10;

  if(_new_x < 0) mpos.x = (GRID_WIDTH - 1) * 10;
  else if(_new_x >= GRID_WIDTH) mpos.x = 0;
  if(_new_y < 2) mpos.y = (GRID_HEIGHT - 1) * 10;
  else if(_new_y >= GRID_HEIGHT) mpos.y = 2 * 10;

  tmp.first = (double)pos.x / 10; tmp.second = (double)pos.y / 10;
  _tmp.first = (double)mpos.x / 10; _tmp.second = (double)mpos.y / 10;

  if(abs(tmp.first - Head.x) >= 1) new_x = tmp.first;
  else new_x = Head.x;
  if(abs(tmp.second - Head.y) >= 1) new_y = tmp.second;
  else new_y = Head.y;

  if(abs(_tmp.first - MirrorHead.x) >= 1) _new_x = _tmp.first;
  else _new_x = MirrorHead.x;
  if(abs(_tmp.second - MirrorHead.y) >= 1) _new_y = _tmp.second;
  else _new_y = MirrorHead.y;



  if(Head.x != new_x || Head.y != new_y){
    last_dir = dir;
    if(Grow > 0){
      body.push_front(Head);
      mbody.push_front(MirrorHead);
      Grow--;
      grid[Head.x][Head.y] = Block::Body;
      grid[MirrorHead.x][MirrorHead.y] = Block::MirrorBody;
    }
    else{
      body.push_front(Head);
      mbody.push_front(MirrorHead);
      grid[body.back().x][body.back().y] = Block::Empty;
      grid[mbody.back().x][mbody.back().y] = Block::Empty;
      body.pop_back();
      mbody.pop_back();
      for(int i = 0; i < (int)body.size(); ++i) grid[body[i].x][body[i].y] = Block::Body;
      for(int i = 0; i < (int)mbody.size(); ++i) grid[mbody[i].x][mbody[i].y] = Block::MirrorBody;
    }
  }

  Head.x = new_x, MirrorHead.x = _new_x;
  Head.y = new_y, MirrorHead.y = _new_y;

  Block &next = grid[Head.x][Head.y];
  Block &_next = grid[MirrorHead.x][MirrorHead.y];

  if(next == Block::Food){
    actualGrow++;
    if(actualGrow % 3 == 0) Grow++;
    food.erase({Head.x, Head.y});
    Mix_Chunk *crunch_sound = Mix_LoadWAV("Sound/crunch.wav");
    Mix_PlayChannel(-1, crunch_sound, 0);
    GenerateFood();
    score++;
  }
  else if(next == Block::Body || next == Block::MirrorBody || next == Block::MirrorHead){
    alive = false;
    body.clear();
    mbody.clear();
    running = false;
    readdd.update(2, score);
  }
  if(_next == Block::Food){
    actualGrow++;
    if(actualGrow % 3 == 0) Grow++;
    Mix_Chunk *crunch_sound = Mix_LoadWAV("Sound/crunch.wav");
    Mix_PlayChannel(-1, crunch_sound, 0);
    food.erase(pii(MirrorHead.x, MirrorHead.y));
    GenerateFood();
    score++;
  }
  else if(_next == Block::MirrorBody || _next == Block::Head || _next == Block::Body){
    alive = false;
    body.clear();
    mbody.clear();
    running = false;
    readdd.update(2, score);
  }
  next = Block::Head;
  _next = Block::MirrorHead;
}

void Mirror::DrawSnake(deque<SDL_Point> SnakeBody, SDL_Point head, bool type){
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
    if(previous_block.x == next_block.x) Draw.DrawSnakeBody(renderer, 0, block, type);
    else if(previous_block.y == next_block.y) Draw.DrawSnakeBody(renderer, 1, block, type);
    else{
      previous_block.x -= SnakeBody[i].x; previous_block.y -= SnakeBody[i].y;
      next_block.x -= SnakeBody[i].x; next_block.y -= SnakeBody[i].y;
      if(previous_block.x == -1 && next_block.y == -1 || previous_block.y == -1 && next_block.x == -1) Draw.DrawSnakeBody(renderer, 2, block, type);
      if(previous_block.x == -1 && next_block.y == 1 || previous_block.y == 1 && next_block.x == -1) Draw.DrawSnakeBody(renderer, 3, block, type);
      if(previous_block.x == 1 && next_block.y == -1 || previous_block.y == -1 && next_block.x == 1) Draw.DrawSnakeBody(renderer, 4, block, type);
      if(previous_block.x == 1 && next_block.y == 1 || previous_block.y == 1 && next_block.x == 1) Draw.DrawSnakeBody(renderer, 5, block, type);
    }
  }

  if(Size > 1){
    SDL_Point last = SnakeBody.back();
    SDL_Point Adj_last;
    if((int)SnakeBody.size() > 1) Adj_last = SnakeBody[(int)SnakeBody.size() - 2];
    else Adj_last = head;
    last.x = last.x;
    last.y = last.y;
    Adj_last.x = Adj_last.x;
    Adj_last.y = Adj_last.y;
    SDL_Point respective = {Adj_last.x - last.x, Adj_last.y - last.y};

    if(respective.x == 1 && respective.y == 0) Draw.DrawSnakeTail(renderer, 2, block, type);
    else if(respective.x == -1 && respective.y == 0) Draw.DrawSnakeTail(renderer, 3, block, type);
    else if(respective.x == 0 && respective.y == 1) Draw.DrawSnakeTail(renderer, 1, block, type);
    else Draw.DrawSnakeTail(renderer, 0, block, type);
  }


  block.x = head.x * block.w;
  block.y = head.y * block.h;

  if(Size > 1){
    SDL_Point First = head;
    SDL_Point Adj_First = SnakeBody[0];
    SDL_Point respective = {Adj_First.x - First.x, Adj_First.y - First.y};
    First.x = First.x;
    First.y = First.y;
    Adj_First.x = Adj_First.x;
    Adj_First.y = Adj_First.y;
    if(respective.x == 1 && respective.y == 0) Draw.DrawSnakeHead(renderer, 3, block, type);
    else if(respective.x == -1 && respective.y == 0) Draw.DrawSnakeHead(renderer, 2, block, type);
    else if(respective.x == 0 && respective.y == 1) Draw.DrawSnakeHead(renderer, 0, block, type);
    else Draw.DrawSnakeHead(renderer, 1, block, type);
  }
}

void Mirror::Render(){
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

  DrawSnake(mbody, MirrorHead, 1);
    DrawSnake(body, Head, 0);

  if(isPause) Icon.Pause(renderer);
  Score().DrawScore2(renderer, score, 0);

  SDL_RenderPresent(renderer);
}
