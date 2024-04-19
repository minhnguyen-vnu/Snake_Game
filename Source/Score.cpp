#include "Score.hpp"

void Score::init(){
  fontt = TTF_OpenFont("font/PoetsenOne-Regular.ttf", 25);
}

void Score::DrawScore(SDL_Renderer* gRenderer, int score, int tmp){
  TTF_Font* font = TTF_OpenFont("font/PoetsenOne-Regular.ttf", 25);
  string score_text = to_string(score);
  SDL_Surface* textSurface = TTF_RenderText_Solid(font, score_text.c_str(), {56, 74, 12, 255});
  SDL_Texture* gTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
  SDL_Rect r = {90 + tmp, 43, 50, 50};
  SDL_RenderCopy(gRenderer, gTexture, NULL, &r);

  SDL_FreeSurface(textSurface);
  SDL_DestroyTexture(gTexture);

  string declare = "Score : ";
  textSurface = TTF_RenderText_Solid(font, declare.c_str(), {56, 74, 12, 255});
  gTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
  r = {20 + tmp, 30, 70, 70};
  SDL_RenderCopy(gRenderer, gTexture, NULL, &r);

  SDL_FreeSurface(textSurface);
  SDL_DestroyTexture(gTexture);
  TTF_CloseFont(font);
}

void Score::DrawScore1(SDL_Renderer* gRenderer, int score, int tmp){
  TTF_Font* font = TTF_OpenFont("font/PoetsenOne-Regular.ttf", 25);
  string score_text = to_string(score);
  SDL_Surface* textSurface = TTF_RenderText_Solid(font, score_text.c_str(), {56, 74, 12, 255});
  SDL_Texture* gTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
  SDL_Rect r = {69 + tmp, 43, 30, 30};
  SDL_RenderCopy(gRenderer, gTexture, NULL, &r);

  SDL_FreeSurface(textSurface);
  SDL_DestroyTexture(gTexture);

  string declare = "Score : ";
  textSurface = TTF_RenderText_Solid(font, declare.c_str(), {56, 74, 12, 255});
  gTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
  r = {20 + tmp, 30, 50, 50};
  SDL_RenderCopy(gRenderer, gTexture, NULL, &r);

  SDL_FreeSurface(textSurface);
  SDL_DestroyTexture(gTexture);
  TTF_CloseFont(font);
}

void Score::DrawScore2(SDL_Renderer* gRenderer, int score, int tmp){
  TTF_Font* font = TTF_OpenFont("font/PoetsenOne-Regular.ttf", 25);
  string score_text = to_string(score);
  SDL_Surface* textSurface = TTF_RenderText_Solid(font, score_text.c_str(), {56, 74, 12, 255});
  SDL_Texture* gTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
  SDL_Rect r = {42 + tmp, 10, 30, 30};
  SDL_RenderCopy(gRenderer, gTexture, NULL, &r);

  SDL_FreeSurface(textSurface);
  SDL_DestroyTexture(gTexture);
  TTF_CloseFont(font);
}

void Score::DrawTime1(SDL_Renderer* gRenderer, int cst, int tm, int tmp){
  TTF_Font* font = TTF_OpenFont("font/PoetsenOne-Regular.ttf", 25);
  string tm_text = "00:" + to_string(tm);
  SDL_Surface* textSurface = TTF_RenderText_Solid(font, tm_text.c_str(), {56, 74, 12, 255});
  SDL_Texture* gTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
  SDL_Rect r = {cst + tmp, 43, 35, 35};
  SDL_RenderCopy(gRenderer, gTexture, NULL, &r);

  SDL_FreeSurface(textSurface);
  SDL_DestroyTexture(gTexture);
  TTF_CloseFont(font);
}

void Score::DrawTime(SDL_Renderer* gRenderer, int cst, int tm, int tmp){
  TTF_Font* font = TTF_OpenFont("font/PoetsenOne-Regular.ttf", 25);
  string tm_text = "00:" + to_string(tm);
  SDL_Surface* textSurface = TTF_RenderText_Solid(font, tm_text.c_str(), {56, 74, 12, 255});
  SDL_Texture* gTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
  SDL_Rect r = {cst + tmp, 43, 70, 70};
  SDL_RenderCopy(gRenderer, gTexture, NULL, &r);

  SDL_FreeSurface(textSurface);
  SDL_DestroyTexture(gTexture);
  TTF_CloseFont(font);
}

void Score::DrawScore3(SDL_Renderer* gRenderer, int score1, int score2, int tmp){
//  TTF_Font* font = TTF_OpenFont("font/PoetsenOne-Regular.ttf", 25);
//  cout << 1 << '\n';
  string score_text = to_string(score1);
  SDL_Surface* textSurface = TTF_RenderText_Solid(fontt, score_text.c_str(), {56, 74, 12, 255});
  SDL_Texture* gTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
  SDL_Rect r = {90 + tmp, 90, 35, 35};
  SDL_RenderCopy(gRenderer, gTexture, NULL, &r);

  SDL_DestroyTexture(gTexture);
  SDL_FreeSurface(textSurface);

  score_text = to_string(score2);
  textSurface = TTF_RenderText_Solid(fontt, score_text.c_str(), {56, 74, 12, 255});
  gTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
  r = {90 + tmp, 40, 35, 35};
  SDL_RenderCopy(gRenderer, gTexture, NULL, &r);

    SDL_DestroyTexture(gTexture);
  SDL_FreeSurface(textSurface);

  string declare = "Your Score : ";
  textSurface = TTF_RenderText_Solid(fontt, declare.c_str(), {56, 74, 12, 255});
  gTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
  r = {20 + tmp, 75, 60, 55};
  SDL_RenderCopy(gRenderer, gTexture, NULL, &r);

    SDL_DestroyTexture(gTexture);
  SDL_FreeSurface(textSurface);

  declare = "AI Score : ";
  textSurface = TTF_RenderText_Solid(fontt, declare.c_str(), {56, 74, 12, 255});
  gTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
  r = {20 + tmp, 35, 60, 55};
  SDL_RenderCopy(gRenderer, gTexture, NULL, &r);

  SDL_FreeSurface(textSurface);
  SDL_DestroyTexture(gTexture);
//  TTF_CloseFont(font);
}

void Score::free(){
  TTF_CloseFont(fontt);
}
