#include <iostream>
#include "game.hpp"
#include "AISnake.hpp"
#include "Score.hpp"
#include "Menu.hpp"
#include "Mirror.hpp"
#include "admin.hpp"
#include "Contender.hpp"
#include "TwoSnake.hpp"
#include "SnakeInMultiverseWorld.hpp"

Game SnakeGame;
Contender Contender;
AISnake AI(SnakeGame);
Menu MyMenu;
Mirror MirrorSnake;
Admin ad;
TwoSnake TS;
Score Pencil;
Multi SM;
Mix_Music *music;

void Game::GameLoop() {
    Uint32 before, second = SDL_GetTicks(), after;
    int frame_time, frames = 0;

    while (SnakeGame.running) {
        before = SDL_GetTicks();

        SnakeGame.PollEvents();
        if(AI_refresh){
          AI.refresh(SnakeGame);
          AI_refresh = 0;
        }
        if(SnakeGame.type == 0 || SnakeGame.type == 4){
          SnakeGame.Update();
          if(!SnakeGame.alive){
            running = false;
          }
        }
        else if(SnakeGame.type == 3){
          AI.AIMovement(SnakeGame);
          SnakeGame.Update();
        }
        else if(SnakeGame.type == 2){
          if(dir != Move::none){
            SnakeGame.Update();
            AI.AIMovement(SnakeGame);
          }
        }
        SnakeGame.Render();
        if(SnakeGame.type == 3) AI.AIRender(SnakeGame, 600);
        else if(SnakeGame.type == 2) AI.AIRender(SnakeGame, 0);

        frames++;
        after = SDL_GetTicks();
        frame_time = after - before;

        if (after - second >= 1000) {
            if((type == 3 || type == 2) && GameTime > 0) GameTime--;
            if (SnakeGame.attend) timecount--;
            fps = frames;
            frames = 0;
            second = after;
            UpdateWindowTitle();
        }

        if(GameTime == 0 && type == 3){
          notice = 1;
          if(AI.AIscore > SnakeGame.score){
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, AIWIN);
            SDL_Rect block = {300, 100, 400, 400};
            SDL_RenderCopy(renderer, texture, NULL, &block);
            SDL_DestroyTexture(texture);
          }
          else if(AI.AIscore <= SnakeGame.score){
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, PLAYERWIN);
            SDL_Rect block = {300, 100, 400, 400};
            SDL_RenderCopy(renderer, texture, NULL, &block);
            SDL_DestroyTexture(texture);
          }
          notice = 1;
        }
        else if(SnakeGame.type == 3){
          if(!SnakeGame.alive && !AI.AIalive){
            notice = 1;
            if(AI.AIscore > SnakeGame.score){
              SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, AIWIN);
              SDL_Rect block = {300, 100, 400, 400};
              SDL_RenderCopy(renderer, texture, NULL, &block);
            }
            else if(AI.AIscore <= SnakeGame.score){
              SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, PLAYERWIN);
              SDL_Rect block = {300, 100, 400, 400};
              SDL_RenderCopy(renderer, texture, NULL, &block);
            }
          }
        }
        else if(SnakeGame.type == 2){
          Pencil.DrawScore3(renderer, SnakeGame.score, AI.AIscore, 0);
          if(!SnakeGame.alive && !AI.AIalive){
            notice = 1;
            if(AI.AIscore > SnakeGame.score){
              SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, AIWIN);
              SDL_Rect block = {270, 250, 300, 250};
              SDL_RenderCopy(renderer, texture, NULL, &block);
            }
            else if(AI.AIscore <= SnakeGame.score){
              SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, PLAYERWIN);
              SDL_Rect block = {270, 250, 300, 250};
              SDL_RenderCopy(renderer, texture, NULL, &block);
            }
          }
          if(GameTime == 0){
            notice = 1;
            if(AI.AIscore > SnakeGame.score){
              SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, AIWIN);
              SDL_Rect block = {270, 250, 300, 250};
              SDL_RenderCopy(renderer, texture, NULL, &block);
            }
            else if(AI.AIscore <= SnakeGame.score){
              SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, PLAYERWIN);
              SDL_Rect block = {270, 250, 300, 250};
              SDL_RenderCopy(renderer, texture, NULL, &block);
            }
          }
        }

        SDL_RenderPresent(SnakeGame.renderer);
        if(FRAME_RATE > frame_time){ SDL_Delay(FRAME_RATE - frame_time); }
    }
}

void run(){
  if(ad.returnValue == 0){
    ad.run();
    MyMenu.Setup(ad);
    MyMenu.showMenu(ad);

    if(ad.running == false){
      ad.free();
      MyMenu.free();
      exit(0);
    }
    if(ad.highscoreButton){
      ad.highscoreButton = 0;
      MyMenu.showHS(ad);
      if(ad.backButton){
        ad.backButton = 0;
        ad.free();
        MyMenu.free();
        return;
      }
    }
    MyMenu.chooseMode(ad);
    if(ad.backButton){
      ad.backButton = 0;
      ad.free();
      MyMenu.free();
      return;
    }
    if(ad.running == false) exit(0);
    if(ad.type == 1){
      MyMenu.nextStep(ad);
      ad.free();
    }
    else ad.free();
    if(ad.running == false){
      MyMenu.free();
      exit(0);
    }
    if(ad.backButton){
      ad.backButton = 0;
      MyMenu.free();
      return;
    }
    MyMenu.free();
  }
  Pencil.init();
  if(ad.cnt_music % 5 == 0){
    music = Mix_LoadMUS("Sound/TLO.mp3");
    Mix_PlayMusic(music, -1);
  }
  else if(ad.cnt_music % 5 == 1){
    music = Mix_LoadMUS("Sound/NOY.mp3");
    Mix_PlayMusic(music, -1);
  }
  else if(ad.cnt_music % 5 == 2){
    music = Mix_LoadMUS("Sound/Minecraft.mp3");
    Mix_PlayMusic(music, -1);
  }
  else if(ad.cnt_music % 5 == 3){
    music = Mix_LoadMUS("Sound/BDSM.mp3");
    Mix_PlayMusic(music, -1);
  }

  if(ad.type == 1){
    if(ad.type_2 == 1) Contender.init();
    else if(ad.type_2 == 2) MirrorSnake.init();
    else if(ad.type_2 == 3) TS.init();
    else if(ad.type_2 == 5) SM.init();
    else{
      SnakeGame.type = 0;
      AI.refresh(SnakeGame);
      SnakeGame.Run();
    }
  }
  else{
    SnakeGame.type = ad.type;
    AI.refresh(SnakeGame);
    SnakeGame.Run();
  }
  if(ad.cnt_music % 5 != 4) Mix_FreeMusic(music);
  ad.run();
  MyMenu.Setup2(ad);
  MyMenu.backMenu(ad);
  ad.free();
}

int main(int argc, char* args[]) {
  while(1) run();
  Mix_CloseAudio();
  TTF_Quit();
  SDL_Quit();
  return 0;
}
