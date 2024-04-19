#include "Snake.hpp"
#include "IconManage.hpp"
#include "SnakeInMultiverseWorld.hpp"
#include "Score.hpp"
#include "Highscore.hpp"

Snake DR;
IconManage IC;
Highscore read;

void Multi::init(){

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "failed" << '\n';
        return;
    }
    if (!SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl")) {
        std::cerr << "Warning: Could not set render driver hint!" << std::endl;
        return;
    }
    if (TTF_Init() == -1) {
        return;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        return;
    }
  for(int i = 0; i < GRID_WIDTH; ++i){
    for(int j = 0; j < GRID_HEIGHT; ++j) grid[i][j] = Block::Empty;
  }
  srand(time(NULL));
  apple = IMG_Load("res/apple.png");
  board = IMG_Load("background/MyBoard2.jpg");
  brick = IMG_Load("background/barrier.png");
  line = IMG_Load("background/Linennnn.png");

  window = SDL_CreateWindow("SnakeGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                          SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  Level = 1;
  barrier = 1;
  play();
  SDL_FreeSurface(apple);
  SDL_FreeSurface(board);
  SDL_FreeSurface(brick);
  SDL_FreeSurface(line);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
}

void Multi::play(){
  while(1){
    refresh();
    genMap();
//    cout << 1 << '\n';
    if(success == 0) return;  /// player win
    GameLoop();
    if(escape) return; /// player press x button
    if(!win) return; /// player lose
    read.update(5, Level);
    Level++;
    barrier += ((Level / 3) + 1);
  }
}

void Multi::refresh(){
  for(int i = 0; i < GRID_WIDTH; ++i){
    for(int j = 0; j < GRID_HEIGHT; ++j) grid[i][j] = Block::Empty;
  }
  IC.init(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
  DR.init();

  dir = Move::none;
  last_dir = Move::none;

  memset(comp, -1, sizeof comp);
  speed = 2;
  actualGrow = 0;
  Size = 0;
  Grow = 0;
  alive = true;
  running = true;
  cnt = 0, fps = 0;
  isPause = 0;
  score = 0;
  cp = 0;
  success = 1;
  ap = 0;
  win = 0;

  body.clear();
  food.clear();
  brick_list.clear();
  Size = 4;
  Head = {GRID_WIDTH / 2 - 2, GRID_HEIGHT / 2};
  pos.x = Head.x * 10; pos.y = Head.y * 10;
  for(int i = 1; i <= 3; ++i) body.push_back({Head.x - i, Head.y});
  grid[Head.x][Head.y] = Block::Head;
  for(SDL_Point p : body) grid[p.x][p.y] = Block::Body;
  cnt = 0;
}

void Multi::GenerateBarrier(){
  int x, y;
  for(int i = 1; i <= barrier; ++i){
    while(1){
      x = rand() % (GRID_WIDTH);
      y = rand() % (GRID_HEIGHT);

      if(y < 2) continue;
      if(grid[x][y] == Block::Empty){
        grid[x][y] = Block::brick;
        brick_list.push_back({x, y});
        break;
      }
    }
  }
}

void Multi::dfs(int u, int v, int num){
  comp[u][v] = num;
  for(int i = 0; i <= 3; ++i){
    int nu = u + dx[i];
    int nv = v + dy[i];
    if(nu >= 0 && nu < GRID_WIDTH && nv >= 0 && nv < GRID_HEIGHT){
      if(grid[nu][nv] == Block::brick) continue;
      if(comp[nu][nv] == -1) dfs(nu, nv, num);
    }
  }
}

void Multi::makeGraph(){
  for(int i = 0; i < GRID_WIDTH; ++i){
    for(int j = 0; j < GRID_HEIGHT; ++j){
      if(comp[i][j] == -1 && grid[i][j] != Block::brick) dfs(i, j, ++cp);
    }
  }
}

void Multi::genMap(){
  GenerateBarrier();
  makeGraph();
  int snakeComp = comp[Head.x][Head.y];
  for(int i = 0; i < barrier; ++i){
    int times = 0;
    while(1){
      times++;
      if(times > 200){
        success = 0;
        break;
      }
      int x = rand() % (GRID_WIDTH);
      int y = rand() % (GRID_HEIGHT);

      if(y < 2) continue;
      if(grid[x][y] == Block::Empty && comp[x][y] == snakeComp){
        grid[x][y] = Block::Food;
        food.insert({x, y});
        break;
      }
    }
    if(success == 0) return;
  }
}

void Multi::GameLoop(){
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
//        cout << fps << '\n';
    }
    if(FRAME_RATE > frame_time){ SDL_Delay(FRAME_RATE - frame_time); }

  }
  IC.free();
  DR.free();
}

void Multi::PollEvents(){
  SDL_Event e;
  while(SDL_PollEvent(&e)){
    if(e.type == SDL_QUIT) escape = 1;

    if(e.type == SDL_MOUSEBUTTONDOWN){
      if(isPause == 0) break;
      int xm = e.button.x;
      int ym = e.button.y;
      if(IC.CheckFocusWithRect(xm, ym, IC.pos[0])){
        isPause = 0;
        break;
      }
      else if(IC.CheckFocusWithRect(xm, ym, IC.pos[1])){
        running = false;
        break;
      }
      else if(IC.CheckFocusWithRect(xm, ym, IC.pos[3])){
        isPause = 0;
        refresh();
        genMap();
//        if(success == 0) return;
        break;
      }
    }

    if(e.type == SDL_KEYDOWN){
      switch(e.key.keysym.sym){
        case SDLK_UP:
          if(isPause) break;
          if(last_dir != Move::down)
          {
            dir = Move::up;
            pos.y = Head.y * 10 - 4;
          }
          break;
        case SDLK_DOWN:
          if(isPause) break;
          if(last_dir != Move::up){

            dir = Move::down;
            pos.y = Head.y * 10 + 4;
          }
          break;
        case SDLK_LEFT:
          if(isPause) break;
          if(last_dir != Move::right && last_dir != Move::none)
          {
            dir = Move::left;

            pos.x = Head.x * 10 - 4;
          }
          break;
        case SDLK_RIGHT:
          if(isPause) break;
          if(last_dir != Move::left)
          {
            dir = Move::right;
            pos.x = Head.x * 10 + 4;
          }
          break;
        case SDLK_ESCAPE:
          isPause = 1;
          break;
      }
    }
  }
}

void Multi::Update(){
  if(isPause) return;
  if(alive == false) return;
  if(dir == Move::none) return;
  if(ap == barrier){
    win = 1;
    running = false;
    return;
  }
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
  else if(new_y >= GRID_HEIGHT) pos.y = 20;

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
      if(grid[body.back().x][body.back().y] == Block::Body) grid[body.back().x][body.back().y] = Block::Empty;
      body.pop_back();
      for(int i = 0; i < (int)body.size(); ++i){
        if(grid[body[i].x][body[i].y] == Block::Empty) grid[body[i].x][body[i].y] = Block::Body;
      }
    }
  }

  Head.x = new_x;
  Head.y = new_y;

  Block &next = grid[Head.x][Head.y];

  if(next == Block::Food){
    score++;
    ap++;
    actualGrow++;
    if(actualGrow % 3 == 0) Grow++;
    Mix_Chunk *crunch_sound = Mix_LoadWAV("Sound/crunch.wav");
    Mix_PlayChannel(-1, crunch_sound, 0);
    food.erase({Head.x, Head.y});
  }
  else if(next == Block::Body || next == Block::brick){
    alive = false;
    body.clear();
    running = false;
  }
  next = Block::Head;
}

void Multi::DrawSnake(deque<SDL_Point> SnakeBody, SDL_Point head, bool type){
  if(alive == false) return;

  SDL_Rect block;
  block.w = SCREEN_WIDTH / GRID_WIDTH;
  block.h = SCREEN_HEIGHT / GRID_HEIGHT;

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
    if(respective.x == 1 && respective.y == 0){

      DR.DrawSnakeHead(renderer, 3, block, type); /// turn left
    }
    else if(respective.x == -1 && respective.y == 0){

      DR.DrawSnakeHead(renderer, 2, block, type); /// turn right
    }
    else if(respective.x == 0 && respective.y == 1){

      DR.DrawSnakeHead(renderer, 0, block, type); /// turn up
    }
    else{

      DR.DrawSnakeHead(renderer, 1, block, type); /// turn down
    }
  }


  for(int i = 0; i < (int)SnakeBody.size(); ++i){
    if(grid[SnakeBody[i].x][SnakeBody[i].y] == Block::brick) continue;
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
    if(previous_block.x == next_block.x) DR.DrawSnakeBody(renderer, 0, block, type); /// vertical
    else if(previous_block.y == next_block.y) DR.DrawSnakeBody(renderer, 1, block, type);
    else{
      previous_block.x -= SnakeBody[i].x; previous_block.y -= SnakeBody[i].y;
      next_block.x -= SnakeBody[i].x; next_block.y -= SnakeBody[i].y;
      if(previous_block.x == -1 && next_block.y == -1 || previous_block.y == -1 && next_block.x == -1) DR.DrawSnakeBody(renderer, 2, block, type);
      if(previous_block.x == -1 && next_block.y == 1 || previous_block.y == 1 && next_block.x == -1) DR.DrawSnakeBody(renderer, 3, block, type);
      if(previous_block.x == 1 && next_block.y == -1 || previous_block.y == -1 && next_block.x == 1) DR.DrawSnakeBody(renderer, 4, block, type);
      if(previous_block.x == 1 && next_block.y == 1 || previous_block.y == 1 && next_block.x == 1) DR.DrawSnakeBody(renderer, 5, block, type);
    }
  }

  if(Size > 1){
    SDL_Point last = SnakeBody.back();
    if(grid[last.x][last.y] != Block::brick){
      SDL_Point Adj_last;
      if((int)SnakeBody.size() > 1) Adj_last = SnakeBody[(int)SnakeBody.size() - 2];
      else Adj_last = head;
      last.x = last.x;
      last.y = last.y;
      Adj_last.x = Adj_last.x;
      Adj_last.y = Adj_last.y;
      SDL_Point respective = {Adj_last.x - last.x, Adj_last.y - last.y};

      if(respective.x == 1 && respective.y == 0){
//        block.x += abs(diff.second);
        DR.DrawSnakeTail(renderer, 2, block, type); /// left
      }
      else if(respective.x == -1 && respective.y == 0){
//        block.x -= abs(diff.second);
        DR.DrawSnakeTail(renderer, 3, block, type); /// right
      }
      else if(respective.x == 0 && respective.y == 1){
//        block.y += abs(diff.second);
        DR.DrawSnakeTail(renderer, 1, block, type); /// up
      }
      else{
//        block.y -= abs(diff.second);
        DR.DrawSnakeTail(renderer, 0, block, type); /// down
      }
    }
  }
}

void Multi::Render(){
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);
  SDL_Rect block;
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, board);
  SDL_RenderCopy(renderer, texture, NULL, NULL);

  SDL_DestroyTexture(texture);

  texture = SDL_CreateTextureFromSurface(renderer, line);
  block.x = block.y = 0;
  block.w = SCREEN_WIDTH;
  block.h =  2 * (SCREEN_HEIGHT / GRID_HEIGHT);
  SDL_RenderCopy(renderer, texture, NULL, &block);

  SDL_DestroyTexture(texture);

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

  SDL_Texture* Brick = SDL_CreateTextureFromSurface(renderer, brick);
  for(auto p : brick_list){
    block.w = SCREEN_WIDTH / GRID_WIDTH;
    block.h = SCREEN_HEIGHT / GRID_HEIGHT;
    block.x = p.first * block.w;
    block.y = p.second * block.h;
    SDL_RenderCopy(renderer, Brick, NULL, &block);
  }

  DrawSnake(body, Head, 0);

  if(isPause) IC.Pause(renderer);
  Score().DrawScore2(renderer, score, 0);
//  SDL_Rect T = {((double)pos.x / 10) * (SCREEN_WIDTH / GRID_WIDTH), ((double)pos.y / 10) * (SCREEN_HEIGHT / GRID_HEIGHT),(SCREEN_HEIGHT / GRID_HEIGHT),(SCREEN_HEIGHT / GRID_HEIGHT)};
//  SDL_RenderDrawRect(renderer, &T);
  SDL_RenderPresent(renderer);
  SDL_DestroyTexture(texture);
  SDL_DestroyTexture(Brick);
}

