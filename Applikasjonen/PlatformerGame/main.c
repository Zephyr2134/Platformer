#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <Emscripten.h>
#include "character.h"

SDL_Renderer* renderer;
Character player;

void MainLoop(void)
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);
    DrawCharacter(renderer, player);
    SDL_RenderPresent(renderer);
}

int main()
{
    #ifdef __EMSRIPTEN__
    SDL_SetHint("SDL_HINT_EMSCRIPTEN_CANVAS_ELEMENT_ID", "#canvas");
    #endif

    SDL_Window* window = SDL_CreateWindow("PlatformerGame", 800, 800, 0);
    if(!window)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return 1;
    }
    renderer = SDL_CreateRenderer(window, NULL);
    if(!renderer)
    {
        SDL_Log("Failed to initialize renderer: %s", SDL_GetError());
        return 1;
    }
    CreateCharacter(renderer, &player, 0, 0, 100, 100, 5, "assets/Mario.png");

    emscripten_set_main_loop(MainLoop, 0, 1);

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}