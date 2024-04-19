#pragma once
#include "admin.hpp"

#define PLAY_GAME 0
#define EXIT 1
#define PLAYER 2
#define VS_AI 3
#define ENDLESS_MODE 4
#define COMPETITIVE 5
#define HOME 6
#define PLAY_AGAIN 7
#define OBSTACLE 8
#define MIRROR 9
#define REVERSE 10
#define CLASSIC 11
#define HIGH_SCORE 12
#define BACK 13
#define LIST 14
#define MUSIC 15
#define CHALLENGE 16

class Menu{
private:
  SDL_Rect pos[18];
	SDL_Texture* menu;
	SDL_Texture* playWhite;
	SDL_Texture* playRed;
	SDL_Texture* exitWhite;
	SDL_Texture* exitRed;
	SDL_Texture* playerWhite;
	SDL_Texture* playerRed;
	SDL_Texture* aiWhite;
	SDL_Texture* aiRed;
	SDL_Texture* endlessWhite;
	SDL_Texture* endlessRed;
	SDL_Texture* competitiveWhite;
	SDL_Texture* competitiveRed;
	SDL_Texture* HB, *HR, *PAB, *PAR;
	SDL_Texture* OR, *OB, *CR, *CB, *MR, *MB, *RR, *RB;
	SDL_Texture* Back;
  SDL_Texture* List;
  SDL_Texture* HSB;
  SDL_Texture* MS;
  SDL_Texture* CMR, *CM;
  TTF_Font* font;

	SDL_Event e;

	int xm, ym;
public:
	Menu();

	void Setup(Admin &MyGame);
	void Setup2(Admin &MyGame);
	bool CheckFocusWithRect(int x, int y, SDL_Rect rect);
	void showMenu(Admin &MyGame);
	void showHS(Admin &MyGame);
	void chooseMode(Admin &MyGame);
	void nextStep(Admin &MyGame);
	void backMenu(Admin &MyGame);
	void DrawHighScore(Admin &MyGame, int sc, int xL, int yR);
	void free();
};
