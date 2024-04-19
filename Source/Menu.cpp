#include "Menu.hpp"
#include "TextManager.hpp"
#include "Highscore.hpp"

//Highscore ballpoint;

Menu::Menu() {}

void Menu::free(){
  TTF_CloseFont(font);
}

void Menu::Setup(Admin &MyGame){
  menu = TextureManager::LoadTexture(MyGame, "background/MenuBackground.jpg");
  font = TTF_OpenFont("font/segoesc.ttf", 20);

  TextureManager::SetPos(pos[PLAY_GAME], Vector2D(290, 220), Vector2D(250, 75));
  TextureManager::SetPos(pos[EXIT], Vector2D(360, 320), Vector2D(100, 75));
  TextureManager::SetPos(pos[PLAYER], Vector2D(100, 170), Vector2D(250, 75));
  TextureManager::SetPos(pos[VS_AI], Vector2D(160, 270), Vector2D(100, 75));
  TextureManager::SetPos(pos[ENDLESS_MODE], Vector2D(100, 370), Vector2D(250, 75));
  TextureManager::SetPos(pos[COMPETITIVE], Vector2D(80, 470), Vector2D(400, 100));

  TextureManager::SetPos(pos[OBSTACLE], Vector2D(100, 170), Vector2D(250, 75));
  TextureManager::SetPos(pos[MIRROR], Vector2D(100, 270), Vector2D(250, 75));
  TextureManager::SetPos(pos[REVERSE], Vector2D(100, 370), Vector2D(250, 75));
  TextureManager::SetPos(pos[BACK], Vector2D(50, 50), Vector2D(50, 50));
  TextureManager::SetPos(pos[LIST], Vector2D(850, 50), Vector2D(50, 50));
  TextureManager::SetPos(pos[CLASSIC], Vector2D(80, 470), Vector2D(400, 100));
  TextureManager::SetPos(pos[MUSIC], Vector2D(430, 40), Vector2D(80, 80));
  TextureManager::SetPos(pos[CHALLENGE], Vector2D(80, 580), Vector2D(400, 100));

  playWhite = TextureManager::LoadTexture(MyGame, "button/PlayWhite.png");
  playRed = TextureManager::LoadTexture(MyGame, "button/PlayRed.png");
	exitWhite = TextureManager::LoadTexture(MyGame, "button/ExitWhite.png");
	exitRed = TextureManager::LoadTexture(MyGame, "button/ExitRed.png");
  playerWhite = TextureManager::LoadTexture(MyGame, "button/1PlayerWhite.png");
  playerRed = TextureManager::LoadTexture(MyGame, "button/1PlayerRed.png");
  aiWhite = TextureManager::LoadTexture(MyGame, "button/VSAIwhite.png");
  aiRed = TextureManager::LoadTexture(MyGame, "button/VSAIRed.png");
  endlessWhite = TextureManager::LoadTexture(MyGame, "button/EndlessModeWhite.png");
  endlessRed = TextureManager::LoadTexture(MyGame, "button/EndlessModeRed.png");
  competitiveWhite = TextureManager::LoadTexture(MyGame, "button/CompeWhite.png");
  competitiveRed = TextureManager::LoadTexture(MyGame, "button/CompeRed.png");
  OR = TextureManager::LoadTexture(MyGame, "button/obred.png");
  OB = TextureManager::LoadTexture(MyGame, "button/obblack.png");
  CR = TextureManager::LoadTexture(MyGame, "button/cared.png");
  CB = TextureManager::LoadTexture(MyGame, "button/cablack.png");
  RR = TextureManager::LoadTexture(MyGame, "button/rered.png");
  RB = TextureManager::LoadTexture(MyGame, "button/reblack.png");
  MR = TextureManager::LoadTexture(MyGame, "button/mired.png");
  MB = TextureManager::LoadTexture(MyGame, "button/miblack.png");
  Back = TextureManager::LoadTexture(MyGame, "button/BackIcon.png");
  List = TextureManager::LoadTexture(MyGame, "button/ListIcon.png");
  HSB = TextureManager::LoadTexture(MyGame, "background/diemcao.png");
  MS = TextureManager::LoadTexture(MyGame, "button/MusicButton.png");
  CMR = TextureManager::LoadTexture(MyGame, "button/CMR.png");
  CM = TextureManager::LoadTexture(MyGame, "button/CM.png");
}

void Menu::Setup2(Admin &MyGame){
  menu = TextureManager::LoadTexture(MyGame, "background/MenuBackground.jpg");

  TextureManager::SetPos(pos[HOME], Vector2D(290, 220), Vector2D(280, 85));
  TextureManager::SetPos(pos[PLAY_AGAIN], Vector2D(300, 320), Vector2D(280, 85));

  HB = TextureManager::LoadTexture(MyGame, "button/hb.png");
  HR = TextureManager::LoadTexture(MyGame, "button/hr.png");
  PAB = TextureManager::LoadTexture(MyGame, "button/pab.png");
  PAR = TextureManager::LoadTexture(MyGame, "button/par.png");
}

bool Menu::CheckFocusWithRect(int x, int y, SDL_Rect rect) {
	return (x >= rect.x && x <= rect.x + rect.w
		   	&& y >= rect.y && y <= rect.y + rect.h);
}

void Menu::DrawHighScore(Admin &MyGame, int sc, int xL, int yR){
  string score_text = to_string(sc);
  SDL_Surface* textSurface = TTF_RenderText_Solid(font, score_text.c_str(), {255, 0, 0, 255});
  SDL_Texture* gTexture = SDL_CreateTextureFromSurface(MyGame.renderer, textSurface);
  SDL_Rect r = {xL, yR, 35, 50};
  SDL_RenderCopy(MyGame.renderer, gTexture, NULL, &r);
  SDL_FreeSurface(textSurface);
  SDL_DestroyTexture(gTexture);
}

void Menu::showMenu(Admin &MyGame){
  bool run = true;
  while(run){
    SDL_SetRenderDrawColor(MyGame.renderer, 255, 255, 255, 255);
    SDL_RenderClear(MyGame.renderer);
    SDL_RenderCopy(MyGame.renderer, menu, NULL, NULL);
    SDL_RenderCopy(MyGame.renderer, Back, NULL, &pos[BACK]);
    SDL_RenderCopy(MyGame.renderer, List, NULL, &pos[LIST]);
    SDL_RenderCopy(MyGame.renderer, MS, NULL, &pos[MUSIC]);
    SDL_GetMouseState(&xm, &ym);
    if(CheckFocusWithRect(xm, ym, pos[PLAY_GAME])) SDL_RenderCopy(MyGame.renderer, playRed, NULL, &pos[PLAY_GAME]);
    else SDL_RenderCopy(MyGame.renderer, playWhite, NULL, &pos[PLAY_GAME]);
    if(CheckFocusWithRect(xm, ym, pos[EXIT])) SDL_RenderCopy(MyGame.renderer, exitRed, NULL, &pos[EXIT]);
    else SDL_RenderCopy(MyGame.renderer, exitWhite, NULL, &pos[EXIT]);
    while(SDL_PollEvent(&e)){
      if(e.type == SDL_QUIT){
        MyGame.running = false;
        run = false;
      }
      SDL_RenderCopy(MyGame.renderer, menu, NULL, NULL);
      SDL_RenderCopy(MyGame.renderer, Back, NULL, &pos[BACK]);
      SDL_RenderCopy(MyGame.renderer, List, NULL, &pos[LIST]);
      SDL_RenderCopy(MyGame.renderer, MS, NULL, &pos[MUSIC]);
      if(e.type == SDL_MOUSEMOTION){
        xm = e.motion.x;
        ym = e.motion.y;
        if(CheckFocusWithRect(xm, ym, pos[PLAY_GAME])) SDL_RenderCopy(MyGame.renderer, playRed, NULL, &pos[PLAY_GAME]);
        else SDL_RenderCopy(MyGame.renderer, playWhite, NULL, &pos[PLAY_GAME]);
        if(CheckFocusWithRect(xm, ym, pos[EXIT])) SDL_RenderCopy(MyGame.renderer, exitRed, NULL, &pos[EXIT]);
        else SDL_RenderCopy(MyGame.renderer, exitWhite, NULL, &pos[EXIT]);
      }
      if(e.type == SDL_MOUSEBUTTONDOWN){
        xm = e.button.x;
        ym = e.button.y;
        if(CheckFocusWithRect(xm, ym, pos[LIST])){
          MyGame.highscoreButton = 1;
          run = false;
        }
        if(CheckFocusWithRect(xm, ym, pos[PLAY_GAME])){
          MyGame.running = true;
          run = false;
        }
        else if(CheckFocusWithRect(xm, ym, pos[EXIT])){
          MyGame.running = false;
          run = false;
        }
        else if(CheckFocusWithRect(xm, ym, pos[MUSIC])){
          MyGame.cnt_music++;
        }
      }
    }
    SDL_RenderPresent(MyGame.renderer);
  }
  SDL_DestroyTexture(playWhite);
  SDL_DestroyTexture(playRed);
	SDL_DestroyTexture(exitWhite);
	SDL_DestroyTexture(exitRed);
	SDL_DestroyTexture(List);
	SDL_DestroyTexture(MS);
}

void Menu::showHS(Admin &MyGame){
  ifstream inp("Highscore.txt");
  vector<int> score_list;
  for(int i = 1; i <= 5; ++i){
    int x; inp >> x;
    score_list.push_back(x);
  }

  bool run = true;
  while(run){
    SDL_SetRenderDrawColor(MyGame.renderer, 255, 255, 255, 255);
    SDL_RenderClear(MyGame.renderer);
    SDL_RenderCopy(MyGame.renderer, HSB, NULL, NULL);
    SDL_RenderCopy(MyGame.renderer, Back, NULL, &pos[BACK]);
    DrawHighScore(MyGame, score_list[0], 360, 215);
    DrawHighScore(MyGame, score_list[1], 360, 300);
    DrawHighScore(MyGame, score_list[2], 380, 380);
    DrawHighScore(MyGame, score_list[3], 850, 215);
    DrawHighScore(MyGame, score_list[4], 890, 300);
    while(SDL_PollEvent(&e)){
      if(e.type == SDL_QUIT){
        MyGame.running = false;
        run = false;
      }
      SDL_RenderCopy(MyGame.renderer, HSB, NULL, NULL);
      SDL_RenderCopy(MyGame.renderer, Back, NULL, &pos[BACK]);
      DrawHighScore(MyGame, score_list[0], 360, 215);
      DrawHighScore(MyGame, score_list[1], 360, 300);
      DrawHighScore(MyGame, score_list[2], 380, 380);
      DrawHighScore(MyGame, score_list[3], 850, 215);
      DrawHighScore(MyGame, score_list[4], 890, 300);
      if(e.type == SDL_MOUSEBUTTONDOWN){
        xm = e.button.x;
        ym = e.button.y;
        if(CheckFocusWithRect(xm, ym, pos[BACK])){
          MyGame.backButton = 1;
          run = false;
        }
      }
    }
    SDL_RenderPresent(MyGame.renderer);
  }
  SDL_DestroyTexture(HSB);
  inp.close();
  score_list.clear();
}

void Menu::chooseMode(Admin &MyGame){
  bool run = true;
  while(run){
    SDL_SetRenderDrawColor(MyGame.renderer, 255, 255, 255, 255);
    SDL_RenderClear(MyGame.renderer);
    SDL_RenderCopy(MyGame.renderer, menu, NULL, NULL);
    SDL_RenderCopy(MyGame.renderer, Back, NULL, &pos[BACK]);
    SDL_GetMouseState(&xm, &ym);
    if(CheckFocusWithRect(xm, ym, pos[PLAYER])) SDL_RenderCopy(MyGame.renderer, playerRed, NULL, &pos[PLAYER]);
    else SDL_RenderCopy(MyGame.renderer, playerWhite, NULL, &pos[PLAYER]);
    if(CheckFocusWithRect(xm, ym, pos[VS_AI])) SDL_RenderCopy(MyGame.renderer, aiRed, NULL, &pos[VS_AI]);
    else SDL_RenderCopy(MyGame.renderer, aiWhite, NULL, &pos[VS_AI]);
    if(CheckFocusWithRect(xm, ym, pos[ENDLESS_MODE])) SDL_RenderCopy(MyGame.renderer, endlessRed, NULL, &pos[ENDLESS_MODE]);
    else SDL_RenderCopy(MyGame.renderer, endlessWhite, NULL, &pos[ENDLESS_MODE]);
    if(CheckFocusWithRect(xm, ym, pos[COMPETITIVE])) SDL_RenderCopy(MyGame.renderer, competitiveRed, NULL, &pos[COMPETITIVE]);
    else SDL_RenderCopy(MyGame.renderer, competitiveWhite, NULL, &pos[COMPETITIVE]);
    while(SDL_PollEvent(&e)){
      if(e.type == SDL_QUIT){
        MyGame.running = false;
        run = false;
      }
      SDL_RenderCopy(MyGame.renderer, menu, NULL, NULL);
      SDL_RenderCopy(MyGame.renderer, Back, NULL, &pos[BACK]);
      if(e.type == SDL_MOUSEMOTION){
        xm = e.motion.x;
        ym = e.motion.y;
        if(CheckFocusWithRect(xm, ym, pos[PLAYER])) SDL_RenderCopy(MyGame.renderer, playerRed, NULL, &pos[PLAYER]);
        else SDL_RenderCopy(MyGame.renderer, playerWhite, NULL, &pos[PLAYER]);
        if(CheckFocusWithRect(xm, ym, pos[VS_AI])) SDL_RenderCopy(MyGame.renderer, aiRed, NULL, &pos[VS_AI]);
        else SDL_RenderCopy(MyGame.renderer, aiWhite, NULL, &pos[VS_AI]);
        if(CheckFocusWithRect(xm, ym, pos[ENDLESS_MODE])) SDL_RenderCopy(MyGame.renderer, endlessRed, NULL, &pos[ENDLESS_MODE]);
        else SDL_RenderCopy(MyGame.renderer, endlessWhite, NULL, &pos[ENDLESS_MODE]);
        if(CheckFocusWithRect(xm, ym, pos[COMPETITIVE])) SDL_RenderCopy(MyGame.renderer, competitiveRed, NULL, &pos[COMPETITIVE]);
        else SDL_RenderCopy(MyGame.renderer, competitiveWhite, NULL, &pos[COMPETITIVE]);
      }
      if(e.type == SDL_MOUSEBUTTONDOWN){
        xm = e.button.x;
        ym = e.button.y;
        if(CheckFocusWithRect(xm, ym, pos[BACK])){
          MyGame.backButton = 1;
          run = false;
        }
        if(CheckFocusWithRect(xm, ym, pos[PLAYER])){
          MyGame.type = 1;
          run = false;
        }
        else if(CheckFocusWithRect(xm, ym, pos[COMPETITIVE])){
          MyGame.type = 2;
          run = false;
        }
        else if(CheckFocusWithRect(xm, ym, pos[VS_AI])){
          MyGame.type = 3;
          run = false;
        }
        else if(CheckFocusWithRect(xm, ym, pos[ENDLESS_MODE])){
          MyGame.type = 4;
          run = false;
        }
      }
    }
    SDL_RenderPresent(MyGame.renderer);
  }
  SDL_DestroyTexture(playerWhite);
  SDL_DestroyTexture(playerRed);
  SDL_DestroyTexture(aiWhite);
  SDL_DestroyTexture(aiRed);
  SDL_DestroyTexture(endlessWhite);
  SDL_DestroyTexture(endlessRed);
  SDL_DestroyTexture(competitiveRed);
  SDL_DestroyTexture(competitiveWhite);
}

void Menu::nextStep(Admin &MyGame){
  bool run = true;
  while(run){
    SDL_SetRenderDrawColor(MyGame.renderer, 255, 255, 255, 255);
    SDL_RenderClear(MyGame.renderer);
    SDL_RenderCopy(MyGame.renderer, menu, NULL, NULL);
    SDL_RenderCopy(MyGame.renderer, Back, NULL, &pos[BACK]);
    SDL_GetMouseState(&xm, &ym);
    if(CheckFocusWithRect(xm, ym, pos[OBSTACLE])) SDL_RenderCopy(MyGame.renderer, OR, NULL, &pos[OBSTACLE]);
    else SDL_RenderCopy(MyGame.renderer, OB, NULL, &pos[OBSTACLE]);
    if(CheckFocusWithRect(xm, ym, pos[MIRROR])) SDL_RenderCopy(MyGame.renderer, MR, NULL, &pos[MIRROR]);
    else SDL_RenderCopy(MyGame.renderer, MB, NULL, &pos[MIRROR]);
    if(CheckFocusWithRect(xm, ym, pos[REVERSE])) SDL_RenderCopy(MyGame.renderer, RR, NULL, &pos[REVERSE]);
    else SDL_RenderCopy(MyGame.renderer, RB, NULL, &pos[REVERSE]);
    if(CheckFocusWithRect(xm, ym, pos[CLASSIC])) SDL_RenderCopy(MyGame.renderer, CR, NULL, &pos[CLASSIC]);
    else SDL_RenderCopy(MyGame.renderer, CB, NULL, &pos[CLASSIC]);
    if(CheckFocusWithRect(xm, ym, pos[CHALLENGE])) SDL_RenderCopy(MyGame.renderer, CMR, NULL, &pos[CHALLENGE]);
    else SDL_RenderCopy(MyGame.renderer, CM, NULL, &pos[CHALLENGE]);
    while(SDL_PollEvent(&e)){
      if(e.type == SDL_QUIT){
        MyGame.running = false;
        run = false;
      }
      SDL_RenderCopy(MyGame.renderer, menu, NULL, NULL);
      SDL_RenderCopy(MyGame.renderer, Back, NULL, &pos[BACK]);
      if(e.type == SDL_MOUSEMOTION){
        xm = e.motion.x;
        ym = e.motion.y;
        if(CheckFocusWithRect(xm, ym, pos[OBSTACLE])) SDL_RenderCopy(MyGame.renderer, OR, NULL, &pos[OBSTACLE]);
        else SDL_RenderCopy(MyGame.renderer, OB, NULL, &pos[OBSTACLE]);
        if(CheckFocusWithRect(xm, ym, pos[MIRROR])) SDL_RenderCopy(MyGame.renderer, MR, NULL, &pos[MIRROR]);
        else SDL_RenderCopy(MyGame.renderer, MB, NULL, &pos[MIRROR]);
        if(CheckFocusWithRect(xm, ym, pos[REVERSE])) SDL_RenderCopy(MyGame.renderer, RR, NULL, &pos[REVERSE]);
        else SDL_RenderCopy(MyGame.renderer, RB, NULL, &pos[REVERSE]);
        if(CheckFocusWithRect(xm, ym, pos[CLASSIC])) SDL_RenderCopy(MyGame.renderer, CR, NULL, &pos[CLASSIC]);
        else SDL_RenderCopy(MyGame.renderer, CB, NULL, &pos[CLASSIC]);
        if(CheckFocusWithRect(xm, ym, pos[CHALLENGE])) SDL_RenderCopy(MyGame.renderer, CMR, NULL, &pos[CHALLENGE]);
        else SDL_RenderCopy(MyGame.renderer, CM, NULL, &pos[CHALLENGE]);
      }
      if(e.type == SDL_MOUSEBUTTONDOWN){
        xm = e.button.x;
        ym = e.button.y;
        if(CheckFocusWithRect(xm, ym, pos[BACK])){
          MyGame.backButton = 1;
          run = false;
        }
        if(CheckFocusWithRect(xm, ym, pos[OBSTACLE])){
          MyGame.type_2 = 1;
          run = false;
        }
        else if(CheckFocusWithRect(xm, ym, pos[MIRROR])){
          MyGame.type_2 = 2;
          run = false;
        }
        else if(CheckFocusWithRect(xm, ym, pos[REVERSE])){
          MyGame.type_2 = 3;
          run = false;
        }
        else if(CheckFocusWithRect(xm, ym, pos[CLASSIC])){
          MyGame.type_2 = 4;
          run = false;
        }
        else if(CheckFocusWithRect(xm, ym, pos[CHALLENGE])){
          MyGame.type_2 = 5;
          run = false;
        }
      }
    }
    SDL_RenderPresent(MyGame.renderer);
  }
  SDL_DestroyTexture(OR);
  SDL_DestroyTexture(OB);
  SDL_DestroyTexture(MR);
  SDL_DestroyTexture(MB);
  SDL_DestroyTexture(CR);
  SDL_DestroyTexture(CB);
  SDL_DestroyTexture(RR);
  SDL_DestroyTexture(RB);
  SDL_DestroyTexture(Back);
  SDL_DestroyTexture(CMR);
  SDL_DestroyTexture(CM);
}

void Menu::backMenu(Admin &MyGame){
  bool run = true;
  while(run){
    SDL_SetRenderDrawColor(MyGame.renderer, 255, 255, 255, 255);
    SDL_RenderClear(MyGame.renderer);
    SDL_RenderCopy(MyGame.renderer, menu, NULL, NULL);
    SDL_GetMouseState(&xm, &ym);
    if(CheckFocusWithRect(xm, ym, pos[HOME])) SDL_RenderCopy(MyGame.renderer, HR, NULL, &pos[HOME]);
    else SDL_RenderCopy(MyGame.renderer, HB, NULL, &pos[HOME]);
    if(CheckFocusWithRect(xm, ym, pos[PLAY_AGAIN])) SDL_RenderCopy(MyGame.renderer, PAR, NULL, &pos[PLAY_AGAIN]);
    else SDL_RenderCopy(MyGame.renderer, PAB, NULL, &pos[PLAY_AGAIN]);
    while(SDL_PollEvent(&e)){
      if(e.type == SDL_QUIT){
        MyGame.running = false;
        run = false;
      }
      SDL_RenderCopy(MyGame.renderer, menu, NULL, NULL);
      if(e.type == SDL_MOUSEMOTION){
        xm = e.motion.x;
        ym = e.motion.y;
        if(CheckFocusWithRect(xm, ym, pos[HOME])) SDL_RenderCopy(MyGame.renderer, HR, NULL, &pos[HOME]);
        else SDL_RenderCopy(MyGame.renderer, HB, NULL, &pos[HOME]);
        if(CheckFocusWithRect(xm, ym, pos[PLAY_AGAIN])) SDL_RenderCopy(MyGame.renderer, PAR, NULL, &pos[PLAY_AGAIN]);
        else SDL_RenderCopy(MyGame.renderer, PAB, NULL, &pos[PLAY_AGAIN]);
      }
      if(e.type == SDL_MOUSEBUTTONDOWN){
        xm = e.button.x;
        ym = e.button.y;
        if(CheckFocusWithRect(xm, ym, pos[HOME])){
          MyGame.returnValue = 0;
          run = false;
        }
        else if(CheckFocusWithRect(xm, ym, pos[PLAY_AGAIN])){
          MyGame.returnValue = 1;
          run = false;
        }
      }
    }
    SDL_RenderPresent(MyGame.renderer);
  }
  SDL_DestroyTexture(HB);
  SDL_DestroyTexture(HR);
  SDL_DestroyTexture(PAR);
  SDL_DestroyTexture(PAB);
}
