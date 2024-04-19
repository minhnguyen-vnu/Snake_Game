#include "map.hpp"

bool MAP::initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }

    gWindow = SDL_CreateWindow("Caro Board", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
        cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == NULL) {
        cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << endl;
        return false;
    }

    return true;
}

void MAP::drawBoard() {
    bool isDark = false;

    int cnt = 0;

    SDL_RenderClear(gRenderer);

    for (int y = 0; y < BOARD_SIZE; ++y) {
        for (int x = 0; x < BOARD_SIZE; ++x) {
            SDL_Rect rect = {y * CELL_SIZE, x * CELL_SIZE, CELL_SIZE, CELL_SIZE};
            if (cnt % 2) {
                SDL_SetRenderDrawColor(gRenderer, 126, 166, 4, 255);
                SDL_RenderFillRect(gRenderer, &rect);
            } else {
                SDL_SetRenderDrawColor(gRenderer, 107,142,35, 255);
                SDL_RenderFillRect(gRenderer, &rect);
            }
            cnt++;
        }
        cnt++;
    }
}

void MAP::CreateMap(){
    if (!initSDL()) {
        cout << "Failed to initialize!" << endl;
        return;
    }

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
        SDL_RenderClear(gRenderer);

        drawBoard();
    }

    return;
}
