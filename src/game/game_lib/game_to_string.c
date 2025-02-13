#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "log.h"
#include "game_components.h"

#define BUFFER_SIZE 4096


char* constantsToString () {
    char* buffer = (char*)malloc(BUFFER_SIZE);
    snprintf(buffer, BUFFER_SIZE,
    "\nGLOBAL_CONSTANTS:\n\tWINDOW_HEIGHT=%d\n\tWINDOW_WIDTH=%d\n\tSNES_PIXEL_WIDTH=%d\n\tSNES_PIXEL_HEIGHT=%d"
    "\n\tTARGET_FPS=%d\n\tNAME_OF_GAME=%s",
        WINDOW_HEIGHT,
        WINDOW_WIDTH,
        SNES_PIXEL_WIDTH,
        SNES_PIXEL_HEIGHT,
        TARGET_FPS,
        NAME_OF_GAME
    );
    return buffer;
}

char* textureTypeToString (enum TextureType type) {
    switch(type) {
        case TEXT_STATIC:
            return "TEXT_STATIC";
        case TEXT_ANIMATED:
            return "TEXT_ANIMATED";
    };
    log_warn("Type is not from TextureType!");
    return "";
}

char* enviromentTypeToString (enum EnviromentType type) {
    switch(type) {
        case ENV_MENU:
            return "ENV_MENU";
        case ENV_WORLD:
            return "ENV_WORLD";
        case ENV_COMBAT:
            return "ENV_COMBAT";
    };
    log_warn("Type is not from EnviromentType!");
    return "";
}

char* textureAtlasToString(TextureAtlas* textureAtlas) {
    if (!textureAtlas) return strdup("TextureAtlas: NULL");
    
    char* buffer = (char*)malloc(BUFFER_SIZE);
    snprintf(buffer, BUFFER_SIZE,
        "TextureAtlas {\n"
        "\tID: %s\n"
        "\tTextureType: %s\n"
        "\tTexture Path: %s\n"
        "\tColumns: %d, Rows: %d\n"
        "\tTileSize: %dx%d\n"
        "}",
        textureAtlas->ID,
        textureTypeToString(textureAtlas->textureType),
        textureAtlas->textPath,
        textureAtlas->cols, textureAtlas->rows,
        textureAtlas->tileSizeX, textureAtlas->tileSizeY
    );
    return buffer;
}


char* displayToString(Display* display) {
    if (!display) return strdup("Display: NULL");
    
    char* buffer = (char*)malloc(BUFFER_SIZE);
    snprintf(buffer, BUFFER_SIZE,
        "Display {\n"
        "\tWidth: %d, Height: %d\n"
        "\tScaleX: %.2f, ScaleY: %.2f\n"
        "}",
        display->width, display->height,
        display->scaleX, display->scaleY
    );
    return buffer;
}


char* mapToString(struct Map* map) {
    if (!map) return strdup("Map: NULL");
    
    char* buffer = (char*)malloc(BUFFER_SIZE);
    snprintf(buffer, BUFFER_SIZE,
        "Map {\n"
        "\tColumns: %d, Rows: %d\n"
        "}",
        map->cols, map->rows
    );
    return buffer;
}

char* subToString(struct Sub* sub) {
    if (!sub) return strdup("Sub: NULL");
    
    char* mapStr = mapToString(sub->map);
    char* buffer = (char*)malloc(BUFFER_SIZE);
    snprintf(buffer, BUFFER_SIZE,
        "Sub {\n"
        "\tID: %s\n"
        "%s\n"
        "}",
        sub->ID,
        mapStr
    );
    free(mapStr);
    return buffer;
}

char* enviromentToString(struct Enviroment* env) {
    if (!env) return strdup("Enviroment: NULL");
    
    char* subStr = subToString(env->sub);
    char* buffer = (char*)malloc(BUFFER_SIZE);
    snprintf(buffer, BUFFER_SIZE,
        "Enviroment {\n"
        "\tID: %s\n"
        "\tType: %s\n"
        "\tEnableGlobalUI: %d\n"
        "%s\n"
        "}",
        env->ID,
        enviromentTypeToString(env->type),
        env->enableGlobalUI,
        subStr
    );
    free(subStr);
    return buffer;
}

char* enviromentStackToString(struct EnviromentStack* stack) {
    if (!stack || !stack->top) return strdup("EnviromentStack: Empty");
    
    char* buffer = (char*)malloc(BUFFER_SIZE);
    struct EnviromentStackItem* current = stack->top;
    size_t offset = 0;
    offset += snprintf(buffer + offset, BUFFER_SIZE - offset, "EnviromentStack {\n  Size: %d\n", stack->size);
    
    while (current && offset < BUFFER_SIZE) {
        char* envStr = enviromentToString(current->env);
        offset += snprintf(buffer + offset, BUFFER_SIZE - offset, "  %s\n", envStr);
        free(envStr);
        current = current->next;
    }
    snprintf(buffer + offset, BUFFER_SIZE - offset, "}");
    return buffer;
}


char* gameStateToString(GameState* gameState) {
    if (!gameState) return strdup("GameState: NULL");
    
    char* buffer = (char*)malloc(BUFFER_SIZE);
    char* displayStr = displayToString(&gameState->display);
    char* stackStr = enviromentStackToString(&gameState->envStack);
    
    snprintf(buffer, BUFFER_SIZE,
        "GameState {\n"
        "%s\n"
        "\tWindow: %p, Renderer: %p\n"
        "%s\n"
        "}",
        displayStr,
        (void*)gameState->window, (void*)gameState->renderer,
        stackStr
    );
    
    free(displayStr);
    free(stackStr);
    return buffer;
}

// ___________ PRINT ___________
static void printStrLOG(char* str, int LOG_LEVEL) {
    switch (LOG_LEVEL)
    {
        case LOG_TRACE:
            log_trace("\n%s", str);
            break;
        case LOG_DEBUG:
            log_debug("\n%s", str);
            break;
        default:
            log_info("\n%s", str);
    }
}

void printGameState(GameState* gameState, int LOG_LEVEL) {
    char* str = gameStateToString(gameState);
    printStrLOG(str, LOG_LEVEL);
    free(str);
}

void printConstants(int LOG_LEVEL) {
    char* str = constantsToString();
    printStrLOG(str, LOG_LEVEL);
    free(str);
}

void printEnviromentStack(struct EnviromentStack* stack, int LOG_LEVEL) {
    char* str = enviromentStackToString(stack);
    printStrLOG(str, LOG_LEVEL);
    free(str);
}
 
void printEnviroment(struct Enviroment* env, int LOG_LEVEL) {
    char* str = enviromentToString(env);
    printStrLOG(str, LOG_LEVEL);
    free(str);
}

void printSub(struct Sub* sub, int LOG_LEVEL) {
    char* str = subToString(sub);
    printStrLOG(str, LOG_LEVEL);
    free(str);
}

void printMap(struct Map* map, int LOG_LEVEL) {
    char* str = mapToString(map);
    printStrLOG(str, LOG_LEVEL);
    free(str);
}

void printDisplay(Display* display, int LOG_LEVEL) {
    char* str = displayToString(display);
    printStrLOG(str, LOG_LEVEL);
    free(str);
}

void printTextureAtlas(TextureAtlas* textureAtlas, int LOG_LEVEL) {
    char* str = textureAtlasToString(textureAtlas);
    printStrLOG(str, LOG_LEVEL);
    free(str);
}