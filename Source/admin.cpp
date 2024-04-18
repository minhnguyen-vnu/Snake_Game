#include "admin.hpp"
#include "Menu.hpp"

void Admin::free(){
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
}

void Admin::run(){
    running = 1;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "failed" << '\n';
        return;
    }
    if (!SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl")) {
        std::cerr << "Warning: Could not set render driver hint!" << std::endl;
    }
    window = SDL_CreateWindow("SnakeGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, MENU_WIDTH, MENU_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (TTF_Init() == -1) {
        return;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        return;
    }
}
