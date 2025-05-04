#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <Emscripten.h>
#include "character.h"
#include "soundManager.h"
#include "ground.h"
#include "camera.h"
#include "coin.h"

SDL_Renderer* renderer;
SDL_Event event;

coinManager coins;
ground field;
camera cam;

sound music;
soundManager sounds;

Character player;
int direction = 0;

void Reset(Character* c, coinManager* coins)
{
    setX(&c->worldPos, 100);
    setY(&c->worldPos, 400);
    c->velocityY = 0;
    c->alive = true;
    ResetCoins(coins);

    EM_ASM({
        if(window.dispatchReactEvent){
            window.dispatchReactEvent("ResetScore");
        }
    });
}

void MainLoop(void)
{
    if(!player.alive)
    {
        Reset(&player, &coins);
    }
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_EVENT_QUIT)
        {
            emscripten_cancel_main_loop();
        }
        if(event.type == SDL_EVENT_KEY_DOWN)
        {
            switch(event.key.key)
            {
                case SDLK_D:
                    direction = 1;
                    break;
                case SDLK_A:
                    direction = -1;
                    break;
                case SDLK_SPACE:
                    if(CharacterJump(&player))
                    {
                    pushBack(&sounds, "assets/jump.wav");
                    }
                    break;
            }
        }
        if(event.type == SDL_EVENT_KEY_UP)
        {
            switch(event.key.key)
            {
                case SDLK_D:
                    if(direction > 0)
                    {
                    direction = 0;
                    }
                    break;

                case SDLK_A:
                    if(direction < 0)
                    {
                    direction = 0;
                    }
                    break;
            }
        }
        }
        

    UpdateCharacter(&player, direction);
    UpdateCamPos(&cam, player.worldPos);
    UpdateViewPos(&player, cam);
    int colResult = CollideCoins(coins, player.dstRect, cam);
    for(int i = 0; i<colResult; i++)
    {
        pushBack(&sounds, "assets/pickupCoin.wav");
        EM_ASM({
            if(window.dispatchReactEvent){
                window.dispatchReactEvent("GotCoin");
            }
        });
    }

    Play_Sound(&music);
    playSounds(&sounds);

    SDL_SetRenderDrawColor(renderer, 174, 243, 231, 255);
    SDL_RenderClear(renderer);
    DrawCharacter(renderer, player);
    RenderCoins(renderer, &coins, cam);
    DrawGround(renderer, &field, &player, cam);
    SDL_RenderPresent(renderer);
}

int main()
{
    #ifdef __EMSRIPTEN__
    SDL_SetHint("SDL_HINT_EMSCRIPTEN_CANVAS_ELEMENT_ID", "#canvas");
    #endif

    if(!SDL_Init(SDL_INIT_EVENTS | SDL_INIT_AUDIO))
    {
        SDL_Log("Could'nt initialize: %s", SDL_GetError());
    }

    SDL_Window* window = SDL_CreateWindow("PlatformerGame", 1200, 550, 0);
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

    music = Create_Sound("assets/GameBackgroundMusic.wav");
    initSoundManager(&sounds);

    CreateCharacter(renderer, &player, 0, 0, 50, 50, 2, "assets/Mario.png");

    int map[100] = {
        1,1,1,1,1,0,0,1,1,1,
        1,1,0,1,1,1,1,0,1,1,
        1,1,1,1,0,0,1,1,1,1,
        1,0,1,1,1,1,0,1,1,0,
        1,1,1,1,1,1,0,0,1,1,
        1,0,1,1,1,1,1,1,1,0,
        1,1,1,1,0,1,1,1,0,1,
        1,1,1,1,1,0,1,1,1,1,
        0,0,1,1,1,1,1,0,1,1,
        1,1,1,0,1,1,1,1,1,1
    };
    MakeGround(renderer, &field, 100, map, 80, "assets/Ground.png");

    InitCamera(&cam, 1200, 550, 6000);

    InitCoinManager(renderer, &coins, "assets/Coin.png");

    int coinMap[400] = {
        1,0,1,1,1,0,1,0,1,0,1,0,1,0,0,1,1,1,1,0,
        1,1,0,0,1,1,0,0,1,1,1,0,0,0,1,0,1,1,1,1,
        0,0,1,0,0,1,0,1,1,1,1,1,1,0,0,1,0,0,1,1,
        1,1,0,1,0,1,0,1,0,1,0,0,1,1,1,0,0,0,1,0,
    
        1,0,1,1,1,1,0,1,0,0,1,0,1,1,0,0,1,1,1,0,
        1,1,1,0,0,1,1,0,1,0,1,0,1,1,0,1,0,1,1,1,
        1,1,0,1,0,1,1,0,1,0,1,1,1,0,0,1,1,0,1,1,
        0,1,1,0,1,0,1,1,0,1,0,1,1,1,0,1,0,1,1,1,
    
        1,0,1,1,1,1,0,0,1,1,1,1,1,0,0,1,0,1,1,1,
        1,1,0,1,0,0,1,1,0,0,1,1,1,0,1,1,1,1,0,0,
        1,0,1,1,1,1,0,1,0,1,1,1,1,0,1,1,1,0,1,0,
        1,1,1,0,1,0,0,1,0,1,1,1,0,1,1,1,0,1,0,1,
    
        1,0,1,0,1,1,1,1,0,1,1,1,0,0,1,1,1,0,1,1,
        1,0,1,1,1,0,1,0,0,1,1,1,0,1,1,0,1,1,0,1,
        0,1,1,1,1,0,1,1,0,1,1,0,1,1,0,1,1,1,0,0,
        1,1,1,1,0,1,0,1,1,0,1,1,1,0,1,0,1,1,1,1
    };
    MakeCoinMap(&coins, 500, 300, coinMap, 4, 100);

    emscripten_set_main_loop(MainLoop, 0, 1);

    freeSound(&sounds);
    FreeCharacter(&player);
    FreeGround(&field);
    FreeCoins(&coins);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}