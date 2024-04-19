#include "IconManage.hpp"
#include "TextManager.hpp"

bool IconManage::CheckFocusWithRect(int x, int y, SDL_Rect rect) {
	return (x >= rect.x && x <= rect.x + rect.w
		   	&& y >= rect.y && y <= rect.y + rect.h);
}

SDL_Texture* IconManage::LoadTexture(SDL_Renderer* &renderer, string path){
  SDL_Surface* sf = IMG_Load(path.c_str());
  SDL_Texture* tx = SDL_CreateTextureFromSurface(renderer, sf);
  SDL_FreeSurface(sf);
  return tx;
}

void IconManage::init(SDL_Renderer* &renderer, int w, int h){
  TextureManager::SetPos(pos[PLAY], Vector2D(w / 2 - 100, h / 2 - 1), Vector2D(50, 50));
  TextureManager::SetPos(pos[EXIT], Vector2D(w / 2 + 100, h / 2 - 1), Vector2D(50, 50));
  TextureManager::SetPos(pos[PAUSE], Vector2D(w / 2 - 150, h / 2 - 50), Vector2D(335, 125));
  TextureManager::SetPos(pos[AGAIN], Vector2D(w / 2 - 15, h / 2 - 10), Vector2D(62, 62));

  playIcon = LoadTexture(renderer, "button/playIcon.png");
  exitIcon = LoadTexture(renderer, "button/ExitIcon.png");
  pauseMenu = LoadTexture(renderer, "button/scoreboard.png");
  again = LoadTexture(renderer, "button/AGAIN.png");
}

void IconManage::Pause(SDL_Renderer* &renderer){
  SDL_RenderCopy(renderer, pauseMenu, NULL, &pos[PAUSE]);
  SDL_RenderCopy(renderer, playIcon, NULL, &pos[PLAY]);
  SDL_RenderCopy(renderer, exitIcon, NULL, &pos[EXIT]);
  SDL_RenderCopy(renderer, again, NULL, &pos[AGAIN]);
}

void IconManage::free(){
  SDL_DestroyTexture(pauseMenu);
  SDL_DestroyTexture(playIcon);
  SDL_DestroyTexture(exitIcon);
  SDL_DestroyTexture(again);
}
