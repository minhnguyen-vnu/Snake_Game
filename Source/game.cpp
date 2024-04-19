#include "game.hpp"
#include "AISnake.hpp"
#include "Score.hpp"
#include "Snake.hpp"
#include "InfinityMap.hpp"
#include "IconManage.hpp"
#include "Highscore.hpp"

using namespace std;

InfinityMap IM;
Snake Draws;
IconManage ICs;
Highscore __read;

void Game::Run() {
    if(type == 3){
      window = SDL_CreateWindow("SnakeGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                1100, 600, SDL_WINDOW_SHOWN);
    }
    else{
      window = SDL_CreateWindow("SnakeGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
//    Mix_Music *music = Mix_LoadMUS("Sound/Minecraft.mp3");
//    Mix_PlayMusic(music, -1);
    backGround = IMG_Load("background/snakeboard6.png");
    Blur = IMG_Load("background/KTT.jpg");
    imageSurface = IMG_Load("res/apple.png");
    Type4 = IMG_Load("background/type44.jpeg");
    AIWIN = IMG_Load("background/AIWIN.png");
    PLAYERWIN = IMG_Load("background/PLAYERWIN.png");

    refresh();
    Draws.init();
    if(type == 3) ICs.init(renderer, 1100, 600);
    else ICs.init(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    GameLoop();
    Draws.free();
    ICs.free();


    SDL_FreeSurface(backGround);
    SDL_FreeSurface(Blur);
    SDL_FreeSurface(imageSurface);
    SDL_FreeSurface(AIWIN);
    SDL_FreeSurface(PLAYERWIN);
//    Mix_FreeMusic(music);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void Game::refresh(){
  srand(time(0));

  body.clear();
  speed = 0.2;
  grow = 0;
  score = 0;
  size = 1;
  nSize = 1;
  actualGrow = 0;
  cnt = 0;
  attend = 0, attend2 = 0;
  timecount = 0, timecount2 = 0;
  GameTime = 59;
  isMove = 0;

  pos.x = GRID_WIDTH / 2; pos.y = GRID_HEIGHT / 2;
  head = {pos.x, pos.y};

  SDL_Point temp = {head.x, head.y + 1};
  size = nSize = 3;
  body.push_back(temp);
  temp = {head.x, head.y + 2};
  body.push_back(temp);
  for(int i = 0; i < GRID_WIDTH; ++i){
    for(int j = 0; j < GRID_HEIGHT; ++j){
      grid[i][j] = Block::Empty;
      if(i == head.x && j == head.y + 1 || i == head.x && j == head.y + 2) grid[i][j] = Block::Body;
    }
  }
  for(int i = 0; i < GRID_WIDTH; ++i){
    for(int j = 0; j < GRID_HEIGHT; ++j) grid2[i][j] = Block::Empty;
  }
  last_dir = Move::none;
  dir  = Move::none;
  bigfood = {-1, -1}, bigfood2 = {-1, -1};
  alive = true;
  running = true;
  fps = 0;
  IM.init();
  duplicateFood();
}

void Game::duplicateFood(){
  int x, y;
  while(1){
    x = rand() % (GRID_WIDTH);
    y = rand() % (GRID_HEIGHT);
    if(y < 5) continue;

    if(grid[x][y] == Block::Empty){
      if(type == 2 && grid2[x][y] != Block::Empty) continue;
      grid[x][y] = Block::Food;
      food.x = x;
      food.y = y;
      break;
    }
  }
}

void Game::duplicateFood2(){
  int x, y;
  while(1){
    x = rand() % (GRID_WIDTH);
    y = rand() % (GRID_HEIGHT);
    if(y < 5) continue;

    if(grid2[x][y] == Block::Empty){
      grid2[x][y] = Block::Food;
      food2.x = x;
      food2.y = y;
      break;
    }
  }
}

bool Game::ok(int x, int y){
  return (y >= 5 && grid[x][y] == Block::Empty && x < GRID_WIDTH && y < GRID_HEIGHT && x >= 0 && y >= 0);
}

bool Game::ok2(int x, int y){
  return (y >= 5 && grid2[x][y] == Block::Empty && x < GRID_WIDTH && y < GRID_HEIGHT && x >= 0 && y >= 0);
}

void Game::duplicateBigFood(){
  int x, y;
  while(1){
    x = rand() % (GRID_WIDTH);
    y = rand() % (GRID_HEIGHT);
    if(y < 5) continue;

    if(ok(x, y) && ok(x, y + 1) && ok(x + 1, y) && ok(x + 1, y + 1)){
      grid[x][y] = Block::BigFood;
      grid[x][y + 1] = Block::BigFood;
      grid[x + 1][y] = Block::BigFood;
      grid[x + 1][y + 1] = Block::BigFood;
      bigfood = {x, y};
      attend = 1;
      timecount = 3;
      break;
    }
  }
}

void Game::duplicateBigFood2(){
  int x, y;
  while(1){
    x = rand() % (GRID_WIDTH);
    y = rand() % (GRID_HEIGHT);
    if(y < 5) continue;

    if(ok2(x, y) && ok2(x, y + 1) && ok2(x + 1, y) && ok2(x + 1, y + 1)){
      grid2[x][y] = Block::BigFood;
      grid2[x][y + 1] = Block::BigFood;
      grid2[x + 1][y] = Block::BigFood;
      grid2[x + 1][y + 1] = Block::BigFood;
      bigfood2 = {x, y};
      attend2 = 1;
      timecount2 = 3;
      break;
    }
  }
}


void Game::PollEvents(){
  SDL_Event e;
  while(SDL_PollEvent(&e)){
    if(e.type == SDL_QUIT) running = false;

    if(e.type == SDL_MOUSEBUTTONDOWN){
      if(isPause == 0) break;
      int xm = e.button.x;
      int ym = e.button.y;
      if(ICs.CheckFocusWithRect(xm, ym, ICs.pos[0])){
        isPause = 0;
        break;
      }
      else if(ICs.CheckFocusWithRect(xm, ym, ICs.pos[1])){
        running = false;
        break;
      }
      else if(ICs.CheckFocusWithRect(xm, ym, ICs.pos[3])){
        isPause = 0;
        refresh();
        AI_refresh = 1;
        break;
      }
    }

    if(e.type == SDL_KEYDOWN){
      switch(e.key.keysym.sym){
        case SDLK_UP:
          if(isPause) break;
          if(last_dir != Move::down || size == 1) dir = Move::up;
          break;
        case SDLK_DOWN:
          if(isPause) break;
          if(last_dir != Move::up || size == 1) dir = Move::down;
          break;
        case SDLK_LEFT:
          if(isPause) break;
          if(last_dir != Move::right || size == 1) dir = Move::left;
          break;
        case SDLK_RIGHT:
          if(isPause) break;
          if(last_dir != Move::left || size == 1) dir = Move::right;
          break;
        case SDLK_RETURN:
          if(isPause) break;
          if(notice == 1) running = false;
          break;
        case SDLK_ESCAPE:
          isPause = 1;
          break;
      }
    }
  }
}

int Game::GetSize(){return size;}

void Game::GrowBody(int q){grow += q;}

void Game::Update(){
  if(isPause) return;
  if(alive == false || GameTime == 0){
    attend = 0;
    return;
  }
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

  int new_x = pos.x;
  int new_y = pos.y;

  if(type == 4){
    if(new_x < 0) pos.x = GRID_WIDTH - 1;
    else if(new_x > GRID_WIDTH - 1) pos.x = 0;

    if(new_y < 0) pos.y = GRID_HEIGHT - 1;
    else if(new_y > GRID_HEIGHT - 1) pos.y = 0;
  }
  else{
    if(new_x < 0) pos.x = GRID_WIDTH - 1;
    else if(new_x > GRID_WIDTH - 1) pos.x = 0;

    if(new_y < 5) pos.y = GRID_HEIGHT - 1;
    else if(new_y > GRID_HEIGHT - 1) pos.y = 5;
  }

  new_x = pos.x;
  new_y = pos.y;

  if(new_x != head.x || new_y != head.y){
    isMove = 1;
    last_dir = dir;
    if(grow > 0){
      size++;
      nSize++;
      if(nSize >= 5){
        speed += 0.01;
        nSize -= 5;
      }
      body.push_front(head);
      grow--;
      grid[head.x][head.y] = Block::Body;
    }
    else{
      body.push_front(head);
      grid[body.back().x][body.back().y] = Block::Empty;
      body.pop_back();
      for(int i = 0; i < (int)body.size(); ++i){
        SDL_Point free = body[i];
        grid[free.x][free.y] = Block::Body;
        free = body[i];
      }
    }
  }
  if(type == 4 && isMove){
    if(dir == Move::up) IM.Move(0);
    else if(dir == Move::down) IM.Move(1);
    else if(dir == Move::right) IM.Move(2);
    else if(dir == Move::left) IM.Move(3);
    isMove = 0;
  }

  head.x = new_x;
  head.y = new_y;
  Mix_Chunk* crunch_sound;

  Block &next = grid[head.x][head.y];

  if(timecount == 0 && bigfood.x != -1){
    grid[bigfood.x][bigfood.y] = Block::Empty;
    grid[bigfood.x][bigfood.y + 1] = Block::Empty;
    grid[bigfood.x + 1][bigfood.y] = Block::Empty;
    grid[bigfood.x + 1][bigfood.y + 1] = Block::Empty;
    bigfood = {-1, -1};
    attend = 0;
  }
  else if(next == Block::BigFood){
    crunch_sound = Mix_LoadWAV("Sound/crunch.wav");
    Mix_PlayChannel(-1, crunch_sound, 0);
    score += 5;
    GrowBody(1);
    grid[bigfood.x][bigfood.y] = Block::Empty;
    grid[bigfood.x][bigfood.y + 1] = Block::Empty;
    grid[bigfood.x + 1][bigfood.y] = Block::Empty;
    grid[bigfood.x + 1][bigfood.y + 1] = Block::Empty;

    bigfood = {-1, -1};
    attend = 0;
    timecount = 0;
  }

  if((cnt + 1) % 500 == 0 && bigfood.x == -1) duplicateBigFood();

  if(next == Block::Food){
    actualGrow++;
    crunch_sound = Mix_LoadWAV("Sound/crunch.wav");
    Mix_PlayChannel(-1, crunch_sound, 0);
    score++;
    duplicateFood();
    if(actualGrow % 2 == 0) GrowBody(1);
  }
  else if(next == Block::Body){
    alive = false;
    crunch_sound = Mix_LoadWAV("Sound/fail.wav");
    if(type == 0) __read.update(4, score);
    return;
  }
  next = Block::Head;
}

void Game::UpdateWindowTitle(){
  string title = "Score : " + to_string(score) + " FPS: " + to_string(fps);
  SDL_SetWindowTitle(window, title.c_str());
}

void Game::DrawSnake(){
  if(alive == false) return;

  SDL_Rect block;
  if(type != 3){
    block.w = SCREEN_WIDTH / GRID_WIDTH;
    block.h = SCREEN_HEIGHT / GRID_HEIGHT;
  }
  else{
    block.w = SCREEN_WIDTH1 / GRID_WIDTH;
    block.h = SCREEN_HEIGHT1 / GRID_HEIGHT;
  }


  for(int i = 0; i < (int)body.size(); ++i){
    block.x = IM.virtualCol[body[i].x] * block.w;
    block.y = IM.virtualRow[body[i].y] * block.h;
    if(i == (int)body.size() - 1) break;
    SDL_Point next_block, previous_block;
    if(i == 0) next_block = head;
    else next_block = body[i - 1];
    previous_block = body[i + 1];
    next_block.x = IM.virtualCol[next_block.x];
    next_block.y = IM.virtualRow[next_block.y];
    previous_block.x = IM.virtualCol[previous_block.x];
    previous_block.y = IM.virtualRow[previous_block.y];
    if(previous_block.x == next_block.x) Draws.DrawSnakeBody(renderer, 0, block, 0);
    else if(previous_block.y == next_block.y) Draws.DrawSnakeBody(renderer, 1, block, 0);
    else{
      previous_block.x -= IM.virtualCol[body[i].x]; previous_block.y -= IM.virtualRow[body[i].y];
      next_block.x -= IM.virtualCol[body[i].x]; next_block.y -= IM.virtualRow[body[i].y];
      if(previous_block.x == -1 && next_block.y == -1 || previous_block.y == -1 && next_block.x == -1) Draws.DrawSnakeBody(renderer, 2, block, 0);
      if(previous_block.x == -1 && next_block.y == 1 || previous_block.y == 1 && next_block.x == -1) Draws.DrawSnakeBody(renderer, 3, block, 0);
      if(previous_block.x == 1 && next_block.y == -1 || previous_block.y == -1 && next_block.x == 1) Draws.DrawSnakeBody(renderer, 4, block, 0);
      if(previous_block.x == 1 && next_block.y == 1 || previous_block.y == 1 && next_block.x == 1) Draws.DrawSnakeBody(renderer, 5, block, 0);
    }
  }

  if(size > 1){
    SDL_Point last = body.back();
    SDL_Point Adj_last;
    if((int)body.size() > 1) Adj_last = body[(int)body.size() - 2];
    else Adj_last = head;
    last.x = IM.virtualCol[last.x];
    last.y = IM.virtualRow[last.y];
    Adj_last.x = IM.virtualCol[Adj_last.x];
    Adj_last.y = IM.virtualRow[Adj_last.y];
    SDL_Point respective = {Adj_last.x - last.x, Adj_last.y - last.y};

    if(respective.x == 1 && respective.y == 0) Draws.DrawSnakeTail(renderer, 2, block, 0);
    else if(respective.x == -1 && respective.y == 0) Draws.DrawSnakeTail(renderer, 3, block, 0);
    else if(respective.x == 0 && respective.y == 1) Draws.DrawSnakeTail(renderer, 1, block, 0);
    else Draws.DrawSnakeTail(renderer, 0, block, 0);
  }


  block.x = IM.virtualCol[head.x] * block.w;
  block.y = IM.virtualRow[head.y] * block.h;


  if(size > 1){
    SDL_Point First = head;
    SDL_Point Adj_First = body[0];
    SDL_Point respective = {Adj_First.x - First.x, Adj_First.y - First.y};
    First.x = IM.virtualCol[First.x];
    First.y = IM.virtualRow[First.y];
    Adj_First.x = IM.virtualCol[Adj_First.x];
    Adj_First.y = IM.virtualRow[Adj_First.y];
    if(respective.x == 1 && respective.y == 0) Draws.DrawSnakeHead(renderer, 3, block, 0);
    else if(respective.x == -1 && respective.y == 0) Draws.DrawSnakeHead(renderer, 2, block, 0);
    else if(respective.x == 0 && respective.y == 1) Draws.DrawSnakeHead(renderer, 0, block, 0);
    else Draws.DrawSnakeHead(renderer, 1, block, 0);
  }
  else{
    if(dir == Move::up) Draws.DrawSnakeHead(renderer, 0, block, 0);
    else if(dir == Move::down) Draws.DrawSnakeHead(renderer, 1, block, 0);
    else if(dir == Move::right) Draws.DrawSnakeHead(renderer, 2, block, 0);
    else Draws.DrawSnakeHead(renderer, 3, block, 0);
  }
}

void Game::Render(){
  SDL_Rect block;
  if(type != 3){
    block.w = SCREEN_WIDTH / GRID_WIDTH;
    block.h = SCREEN_HEIGHT / GRID_HEIGHT;
  }
  else{
    block.w = SCREEN_WIDTH1 / GRID_WIDTH;
    block.h = SCREEN_HEIGHT1 / GRID_HEIGHT;
  }

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);

  if(type == 4){
    SDL_Texture* gTexture = SDL_CreateTextureFromSurface(renderer, Type4);
    SDL_RenderCopy(renderer, gTexture, NULL, NULL);
    SDL_DestroyTexture(gTexture);
  }
  else if(type == 3){
    SDL_Texture* gTexture = SDL_CreateTextureFromSurface(renderer, Blur);
    SDL_RenderCopy(renderer, gTexture, NULL, NULL);
    SDL_DestroyTexture(gTexture);
  }

  if(type == 0 || type == 2){
    SDL_Texture* Texture = SDL_CreateTextureFromSurface(renderer, backGround);
    SDL_Rect dstrect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderCopy(renderer, Texture, NULL, &dstrect);
    SDL_DestroyTexture(Texture);
  }
  else if(type == 3){
    SDL_Texture* Texture = SDL_CreateTextureFromSurface(renderer, backGround);
    SDL_Rect dstrect = {0, 0, SCREEN_WIDTH1, SCREEN_HEIGHT1};
    SDL_RenderCopy(renderer, Texture, NULL, &dstrect);
    SDL_DestroyTexture(Texture);

    SDL_Texture* ggTexture = SDL_CreateTextureFromSurface(renderer, backGround);
    SDL_Rect ddstrect = {600, 0, SCREEN_WIDTH1, SCREEN_HEIGHT1};
    SDL_RenderCopy(renderer, ggTexture, NULL, &ddstrect);
    SDL_DestroyTexture(ggTexture);
  }

  cnt++;

  if(!type) Score().DrawScore(renderer, score, 0);
  else if(type == 3) Score().DrawScore1(renderer, score, 0);
  if(attend && type != 4){
    if(type != 3) Score().DrawTime(renderer, 630, timecount, 0);
    else Score().DrawTime1(renderer, 430, timecount, 0);
  }
  if(attend2 && type != 4) Score().DrawTime1(renderer, 430, timecount2, 600);
  if(type == 3){
    Score().DrawTime1(renderer, 250, GameTime, 0);
    Score().DrawTime1(renderer, 250, GameTime, 600);
  }
  if(type == 2) Score().DrawTime(renderer, 350, GameTime, 0);

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
  SDL_SetTextureColorMod(texture, 255, 0, 0);

  SDL_SetRenderDrawColor(renderer, 194, 178, 128, 255);

  if(type == 3){
    for (int i = 0; i < 10; i++) {
      SDL_Rect borderRect;
      borderRect.x = 0;
      borderRect.y = 0;
      borderRect.w = SCREEN_WIDTH1 + i;
      borderRect.h = SCREEN_HEIGHT1 + i;

      SDL_RenderDrawRect(renderer, &borderRect);
    }
  }

  /// render big food

  if(bigfood.x != -1 && bigfood.y != -1){
    block.x = IM.virtualCol[bigfood.x] * block.w + Add[cnt % 20].first;
    block.y = IM.virtualRow[bigfood.y] * block.h + Add[cnt % 20].first;
    block.w *= 2;
    block.h *= 2;
    block.w += Add[cnt % 20].second;
    block.h +=  Add[cnt % 20].second;
    SDL_RenderCopy(renderer, texture, nullptr, &block);
  }
  if(type == 3){
    if(bigfood2.x != -1 && bigfood2.y != -1){
      block.w = SCREEN_WIDTH1 / GRID_WIDTH;
      block.h = SCREEN_HEIGHT1 / GRID_HEIGHT;
      block.x = bigfood2.x * block.w + Add[cnt % 20].first + 600;
      block.y = bigfood2.y * block.h + Add[cnt % 20].first;
      block.w *= 2;
      block.h *= 2;
      block.w += Add[cnt % 20].second;
      block.h += Add[cnt % 20].second;
      SDL_RenderCopy(renderer, texture, nullptr, &block);
    }
  }

  if(type != 3){
    block.w = SCREEN_WIDTH / GRID_WIDTH;
    block.h = SCREEN_HEIGHT / GRID_HEIGHT;
  }
  else{
    block.w = SCREEN_WIDTH1 / GRID_WIDTH;
    block.h = SCREEN_HEIGHT1 / GRID_HEIGHT;
  }

  block.x = IM.virtualCol[food.x] * block.w + Add[cnt % 20].first;
  block.y = IM.virtualRow[food.y] * block.h + Add[cnt % 20].first;
  if(type != 3){
    block.w = SCREEN_WIDTH / GRID_WIDTH + Add[cnt % 20].second;
    block.h = SCREEN_HEIGHT / GRID_HEIGHT + Add[cnt % 20].second;
  }
  else{
    block.w = SCREEN_WIDTH1 / GRID_WIDTH + Add[cnt % 20].second;
    block.h = SCREEN_HEIGHT1 / GRID_HEIGHT + Add[cnt % 20].second;
  }
  SDL_RenderCopy(renderer, texture, nullptr, &block);

  if(type == 3){
    block.w = SCREEN_WIDTH1 / GRID_WIDTH;
    block.h = SCREEN_HEIGHT1 / GRID_HEIGHT;

    block.x = food2.x * block.w + Add[cnt % 20].first + 600;
    block.y = food2.y * block.h + Add[cnt % 20].first;
    block.w = SCREEN_WIDTH1 / GRID_WIDTH + Add[cnt % 20].second;
    block.h = SCREEN_HEIGHT1 / GRID_HEIGHT + Add[cnt % 20].second;
    SDL_RenderCopy(renderer, texture, nullptr, &block);
  }

  DrawSnake();
  if(isPause) ICs.Pause(renderer);

  SDL_DestroyTexture(texture);
}
