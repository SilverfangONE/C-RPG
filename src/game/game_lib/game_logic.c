#include "game_logic.h"
#include "game_core.h"
#include "game_components.h"
#include "log.h"
#include "game_util.h"

void updatePlayer(GameState* game) {    
    if(game->player == NULL) {
        log_warn("No Player refrence was set to GameState context yet!");
        return;
    }
    if(game->keymap->up || game->keymap->pressedUP) {
        game->player->y -= game->player->speed;
    }
    if(game->keymap->down || game->keymap->pressedDOWN) {
        game->player->y += game->player->speed;
    }
    if(game->keymap->left || game->keymap->pressedLEFT) {
        game->player->x -= game->player->speed;
    }
    if(game->keymap->right || game->keymap->pressedRIGHT) {
        game->player->x += game->player->speed;
    }
}

void updateGame(GameState* game) 
{
    updatePlayer(game);
}

// ---- GAME SYSTEM ----
void processEventsSDL(GameState* game) 
{
    resetKeymapExceptPressed(game->keymap);
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
            {
                exitGame(game);
            }
            break;
            case SDL_EVENT_KEY_UP: 
            {
                switch (event.key.scancode)
                {
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                    log_trace("KEY:UP");
                    game->keymap->pressedUP = false;
                    break;
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    log_trace("KEY:DOWN");
                    game->keymap->pressedDOWN = false;
                    break;
                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    log_trace("KEY:LEFT");
                    game->keymap->pressedLEFT = false;
                    break;
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    log_trace("KEY:RIGHT");
                    game->keymap->pressedRIGHT = false;
                }
            }
            break;
            case SDL_EVENT_KEY_DOWN:
            {
                switch (event.key.scancode)
                {
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                    log_trace("KEY:UP");
                    game->keymap->up = true;
                    break;
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    log_trace("KEY:DOWN");
                    game->keymap->down = true;
                    break;
                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    log_trace("KEY:LEFT");
                    game->keymap->left = true;
                    break;
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    log_trace("KEY:RIGHT");
                    game->keymap->right = true;
                    break;
                case SDL_SCANCODE_RETURN:
                    log_trace("KEY:ENTER");
                    game->keymap->enter = true;
                    break;
                case SDL_SCANCODE_ESCAPE:
                    log_trace("KEY:ESCAPE");
                    game->keymap->esc = true;
                }
            }
        }
    }
}