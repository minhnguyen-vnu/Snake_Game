#include "Snake.hpp"
#include "game.hpp"

using namespace std;

void Snake::free(){
  SDL_FreeSurface(head_up);
  SDL_FreeSurface(head_down);
  SDL_FreeSurface(head_left);
  SDL_FreeSurface(head_right);

  SDL_FreeSurface(tail_up);
  SDL_FreeSurface(tail_down);
  SDL_FreeSurface(tail_left);
  SDL_FreeSurface(tail_right);

  SDL_FreeSurface(body_vertical);
  SDL_FreeSurface(body_horizontal);
  SDL_FreeSurface(body_topleft);
  SDL_FreeSurface(body_bottomleft);
  SDL_FreeSurface(body_topright);
  SDL_FreeSurface(body_bottomright);
}

void Snake::init(){
  head_up = IMG_Load("res/head_up.png");
  head_down = IMG_Load("res/head_down.png");
  head_left = IMG_Load("res/head_left.png");
  head_right = IMG_Load("res/head_right.png");

  tail_up = IMG_Load("res/tail_up.png");
  tail_down = IMG_Load("res/tail_down.png");
  tail_left = IMG_Load("res/tail_left.png");
  tail_right = IMG_Load("res/tail_right.png");

  body_vertical      = IMG_Load("res/body_vertical.png");
  body_horizontal      = IMG_Load("res/body_horizontal.png");
  body_topleft      = IMG_Load("res/body_topleft.png");
  body_bottomleft      = IMG_Load("res/body_bottomleft.png");
  body_topright      = IMG_Load("res/body_topright.png");
  body_bottomright      = IMG_Load("res/body_bottomright.png");
}

void Snake::Draw(SDL_Renderer* gRenderer, SDL_Texture* gTexture, SDL_Rect r){
  SDL_RenderCopy(gRenderer, gTexture, nullptr, &r);
}

void Snake::DrawSnakeHead(SDL_Renderer* gRenderer, int dir, SDL_Rect r, bool type){
  SDL_Texture* gTexture;
  if(dir == 0){
    gTexture = SDL_CreateTextureFromSurface(gRenderer, head_up);
    if(type) SDL_SetTextureColorMod(gTexture, 249, 244, 0);
    Draw(gRenderer, gTexture, r);
  }
  else if(dir == 1){
    gTexture = SDL_CreateTextureFromSurface(gRenderer, head_down);
    if(type) SDL_SetTextureColorMod(gTexture, 249, 244, 0);
    Draw(gRenderer, gTexture, r);
  }
  else if(dir == 2){
    gTexture = SDL_CreateTextureFromSurface(gRenderer, head_right);
    if(type) SDL_SetTextureColorMod(gTexture, 249, 244, 0);
    Draw(gRenderer, gTexture, r);
  }
  else{
    gTexture = SDL_CreateTextureFromSurface(gRenderer, head_left);
    if(type) SDL_SetTextureColorMod(gTexture, 249, 244, 0);
    Draw(gRenderer, gTexture, r);
  }
  SDL_DestroyTexture(gTexture);
}

void Snake::DrawSnakeBody(SDL_Renderer* gRenderer, int dir, SDL_Rect r, bool type){
  SDL_Texture* gTexture;
  if(dir == 0){
    gTexture = SDL_CreateTextureFromSurface(gRenderer, body_vertical);
    if(type) SDL_SetTextureColorMod(gTexture, 249, 244, 0);
    Draw(gRenderer, gTexture, r);
  }
  else if(dir == 1){
    gTexture = SDL_CreateTextureFromSurface(gRenderer, body_horizontal);
    if(type) SDL_SetTextureColorMod(gTexture, 249, 244, 0);
    Draw(gRenderer, gTexture, r);
  }
  else if(dir == 2){
    gTexture = SDL_CreateTextureFromSurface(gRenderer, body_topleft);
    if(type) SDL_SetTextureColorMod(gTexture, 249, 244, 0);
    Draw(gRenderer, gTexture, r);
  }
  else if(dir == 3){
    gTexture = SDL_CreateTextureFromSurface(gRenderer, body_bottomleft);
    if(type) SDL_SetTextureColorMod(gTexture, 249, 244, 0);
    Draw(gRenderer, gTexture, r);
  }
  else if(dir == 4){
    gTexture = SDL_CreateTextureFromSurface(gRenderer, body_topright);
    if(type) SDL_SetTextureColorMod(gTexture, 249, 244, 0);
    Draw(gRenderer, gTexture, r);
  }
  else{
    gTexture = SDL_CreateTextureFromSurface(gRenderer, body_bottomright);
    if(type) SDL_SetTextureColorMod(gTexture, 249, 244, 0);
    Draw(gRenderer, gTexture, r);
  }
  SDL_DestroyTexture(gTexture);
}

void Snake::DrawSnakeTail(SDL_Renderer* gRenderer, int dir, SDL_Rect r, bool type){
  SDL_Texture* gTexture;
  if(dir == 0){
    gTexture = SDL_CreateTextureFromSurface(gRenderer, tail_down);
    if(type) SDL_SetTextureColorMod(gTexture, 249, 244, 0);
    Draw(gRenderer, gTexture, r);
  }
  else if(dir == 1){
    gTexture = SDL_CreateTextureFromSurface(gRenderer, tail_up);
    if(type) SDL_SetTextureColorMod(gTexture, 249, 244, 0);
    Draw(gRenderer, gTexture, r);
  }
  else if(dir == 2){
    gTexture = SDL_CreateTextureFromSurface(gRenderer, tail_left);
    if(type) SDL_SetTextureColorMod(gTexture, 249, 244, 0);
    Draw(gRenderer, gTexture, r);
  }
  else{
    gTexture = SDL_CreateTextureFromSurface(gRenderer, tail_right);
    if(type) SDL_SetTextureColorMod(gTexture, 249, 244, 0);
    Draw(gRenderer, gTexture, r);
  }
  SDL_DestroyTexture(gTexture);
}
