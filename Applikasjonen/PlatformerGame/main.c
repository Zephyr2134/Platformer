#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <Emscripten.h>

SDL_Renderer* renderer;
SDL_Texture* texture;

void MainLoop(void)
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderTexture(renderer, texture, NULL, NULL);
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
    SDL_Surface* image = IMG_Load("assets/image2.png");
    if(!image){
        SDL_Log("Failed to load image: %s", SDL_GetError());
        return 1;
    }
    texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_DestroySurface(image);

    emscripten_set_main_loop(MainLoop, 0, 1);

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}