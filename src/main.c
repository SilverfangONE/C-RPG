#include <SDL3/SDL.h>
#include <stdio.h>
#include <windows.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    // SDL initialisieren
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Fehler beim Initialisieren von SDL: %s\n", SDL_GetError());
        return 1;
    }

    // Fenster erstellen
    SDL_Window *window = SDL_CreateWindow("SDL 3 Fenster", 800, 600, 0);
    if (!window) {
        printf("Fehler beim Erstellen des Fensters: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    
    printf("Eppy Sleepy");
    Sleep(3000);

    // Aufräumen
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
