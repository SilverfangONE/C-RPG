#include "RPGE_E_display.h"
#include "RPGE_E_system_infos.h"
#include "log.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <stdlib.h>

Display_RPGE *create_Display_RPGE(SDL_Renderer *renderer, enum SYSTEM_RPGE system, const int WINDOW_WIDTH,
                                  const int WINDOW_HEIGHT)
{
    Display_RPGE *disp = (Display_RPGE *)malloc(sizeof(Display_RPGE));
    Vec2D res_system = getSystemResolution_RPGE(system);
    if (res_system.x == 0 || res_system.y == 0)
    {
        return NULL;
    }
    disp->texture =
        SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, res_system.x, res_system.y);
    // Setze die Textur auf "Nearest Neighbor" (pixelgenaue Skalierung)
    if (!SDL_SetTextureScaleMode(disp->texture, SDL_SCALEMODE_NEAREST))
    {
        log_error("%s", SDL_GetError());
        return NULL;
    }
    // scaling.
    disp->width = res_system.x;
    disp->height = res_system.y;
    // quadrtic scale;
    int scaleYInt = WINDOW_HEIGHT / res_system.y;
    int scaleXInt = WINDOW_WIDTH / res_system.x;
    if (scaleXInt < scaleYInt)
    {
        scaleYInt = scaleXInt;
    }
    else
    {
        scaleXInt = scaleYInt;
    }

    disp->scaleX = (float)scaleXInt;
    disp->scaleY = (float)scaleYInt;

    // placement from display in window
    SDL_FRect destR;
    destR.w = (float)disp->width * disp->scaleX;
    destR.h = (float)disp->height * disp->scaleY;
    destR.x = (float)(WINDOW_WIDTH - destR.w) / 2;
    destR.y = (float)(WINDOW_HEIGHT - destR.h) / 2;
    disp->destRect = destR;
    return disp;
}

void destroy_Display_RPGE(Display_RPGE *display)
{
    SDL_DestroyTexture(display->texture);
    free(display);
}
