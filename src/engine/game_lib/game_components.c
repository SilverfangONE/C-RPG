#include "game_components.h"
#include "game_core.h"
#include "game_to_string.h"
#include "game_util.h"
#include "hashmap.h"
#include "log.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <stdlib.h>
#include <string.h>

// ---- Sub functions ----
static int
compare_subRoomIDNode (const void *a, const void *b, void *udata)
{
  const struct SubRoomIDNode *sa = a;
  const struct SubRoomIDNode *sb = b;
  return strcmp (sa->id, sb->id);
}

static bool
iter_subRoomIDNode (const void *item, void *udata)
{
  const struct SubRoomIDNode *subRoomIDNode = item;
  printf ("%s (path=%s)\n", subRoomIDNode->id, subRoomIDNode->path);
  return true;
}

static uint64_t
hash_subRoomIDNode (const void *item, uint64_t seed0, uint64_t seed1)
{
  const struct SubRoomIDNode *subRoomIDNode = item;
  return hashmap_sip (subRoomIDNode->id, strlen (subRoomIDNode->id), seed0,
                      seed1);
}

// ---- CONSTANTS ----
const int WINDOW_HEIGHT = 1200;
const int WINDOW_WIDTH = 1200;
const int SNES_PIXEL_WIDTH = 256;
const int SNES_PIXEL_HEIGHT = 224;
const int TARGET_FPS = 60;
const char NAME_OF_GAME[40] = "C_RPG";

// ---- LOAD & DESTROY Game Components ----
void
load_Player (GameState *game, int x, int y, int width, int height, int speed,
             int textureAtlasIndex)
{
  Player *player = malloc (sizeof (Player));
  player->textureAtlasIndex = textureAtlasIndex;
  player->x = x;
  player->y = y;
  player->hitBoxHeight = height;
  player->hitBoxWidth = width;
  player->speed = speed;
  game->player = player;
}

void
destroy_Player (Player *player)
{
  free (player);
}

void
reset_KeymapExceptPressed (Keymap *keymap)
{
  keymap->down = false;
  keymap->up = false;
  keymap->left = false;
  keymap->right = false;
  keymap->esc = false;
  keymap->enter = false;
}

void
reset_Keymap (Keymap *keymap)
{
  keymap->down = false;
  keymap->pressedDOWN = false;
  keymap->up = false;
  keymap->pressedUP = false;
  keymap->left = false;
  keymap->pressedLEFT = false;
  keymap->right = false;
  keymap->pressedRIGHT = false;
  keymap->esc = false;
  keymap->enter = false;
}

void
load_Keymap (GameState *game)
{
  Keymap *keymap = malloc (sizeof (Keymap));
  reset_Keymap (keymap);
  game->keymap = keymap;
}

void
destroy_Keymap (Keymap *keymap)
{
  free (keymap);
}

Display *
create_Display (SDL_Renderer *renderer, int pixelWidth, int pixelHeight,
                int windowWith, int windowHeight)
{
  log_trace ("Create Display!");
  Display *disp = (Display *)malloc (sizeof (Display));
  disp->texture
      = SDL_CreateTexture (renderer, SDL_PIXELFORMAT_RGBA8888,
                           SDL_TEXTUREACCESS_TARGET, pixelWidth, pixelHeight);
  // Setze die Textur auf "Nearest Neighbor" (pixelgenaue Skalierung)
  if (!SDL_SetTextureScaleMode (disp->texture, SDL_SCALEMODE_NEAREST))
    {
      log_error ("%s", SDL_GetError ());
    }
  // scaling.
  disp->height = pixelHeight;
  disp->width = pixelWidth;
  // quadrtic scale;
  int scaleXInt = windowWith / pixelWidth;
  int scaleYInt = windowHeight / pixelHeight;
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
  printDisplay (disp, LOG_TRACE);
  return disp;
}

void
load_Display (GameState *game)
{
  Display disp;
  disp.texture = SDL_CreateTexture (game->renderer, SDL_PIXELFORMAT_RGBA8888,
                                    SDL_TEXTUREACCESS_TARGET, SNES_PIXEL_WIDTH,
                                    SNES_PIXEL_HEIGHT);
  // Setze die Textur auf "Nearest Neighbor" (pixelgenaue Skalierung)
  if (!SDL_SetTextureScaleMode (disp.texture, SDL_SCALEMODE_NEAREST))
    {
      log_error ("%s", SDL_GetError ());
      exitGame (game);
    }
  // scaling.
  disp.height = SNES_PIXEL_HEIGHT;
  disp.width = SNES_PIXEL_WIDTH;
  // quadrtic scale;
  int scaleXInt = WINDOW_WIDTH / SNES_PIXEL_WIDTH;
  int scaleYInt = WINDOW_HEIGHT / SNES_PIXEL_HEIGHT;
  if (scaleXInt < scaleYInt)
    {
      scaleYInt = scaleXInt;
    }
  else
    {
      scaleXInt = scaleYInt;
    }

  disp.scaleX = (float)scaleXInt;
  disp.scaleY = (float)scaleYInt;
  // placement from display in window
  SDL_FRect destR;
  destR.w = (float)disp.width * disp.scaleX;
  destR.h = (float)disp.height * disp.scaleY;
  destR.x = (float)(WINDOW_WIDTH - destR.w) / 2;
  destR.y = (float)(WINDOW_HEIGHT - destR.h) / 2;
  disp.destRect = destR;
  game->display = disp;
  printDisplay (&disp, LOG_TRACE);
}

void
destroy_Display (Display *display)
{
  SDL_DestroyTexture (display->texture);
  free (display);
}

// TODO: später steht das alles in einer json datei. => dan nur pfad zur json
// datei und zur texture
TextureAtlas *
load_TextureAtlasJSON (GameState *game, char *pathJSON)
{
  struct TextureAtlas *textureAtlas = malloc (sizeof (struct TextureAtlas));
  // load TextureAtlas from json.
  char *jsonString = readFile (pathJSON);
  if (!jsonString)
    {
      log_error ("JSON-Datei=%s konnte nicht gelesen werden!", pathJSON);
      exitGame (game);
    }
  cJSON *textureAtlasJSON = cJSON_Parse (jsonString);
  free (jsonString);
  validateValueJSON (game, textureAtlasJSON);

  const cJSON *ID = NULL;
  const cJSON *cols = NULL;
  const cJSON *rows = NULL;
  const cJSON *tileSizeX = NULL;
  const cJSON *tileSizeY = NULL;
  const cJSON *texturePath = NULL;
  const cJSON *textureType = NULL;

  ID = cJSON_GetObjectItemCaseSensitive (textureAtlasJSON, "ID");
  validateValueConstJSON (game, ID, "ID", pathJSON);
  validateTypeValueJSON (game, ID, cJSON_IsString);
  strncpy (textureAtlas->ID, ID->valuestring, sizeof (textureAtlas->ID) - 1);
  textureAtlas->ID[sizeof (textureAtlas->ID) - 1] = '\0';

  texturePath
      = cJSON_GetObjectItemCaseSensitive (textureAtlasJSON, "texturePath");
  validateValueConstJSON (game, texturePath, "texturePath", pathJSON);
  validateTypeValueJSON (game, texturePath, cJSON_IsString);
  strncpy (textureAtlas->textPath, texturePath->valuestring,
           sizeof (textureAtlas->textPath) - 1);
  textureAtlas->textPath[sizeof (textureAtlas->textPath) - 1] = '\0';

  textureType
      = cJSON_GetObjectItemCaseSensitive (textureAtlasJSON, "textureType");
  validateValueConstJSON (game, textureType, "textureType", pathJSON);
  validateTypeValueJSON (game, textureType, cJSON_IsString);
  log_debug ("TextureType: %s", textureType->valuestring);
  textureAtlas->textureType = toTextureType (game, textureType->valuestring);

  cols = cJSON_GetObjectItemCaseSensitive (textureAtlasJSON, "cols");
  validateValueConstJSON (game, cols, "cols", pathJSON);
  textureAtlas->cols = cols->valueint;

  rows = cJSON_GetObjectItemCaseSensitive (textureAtlasJSON, "rows");
  validateValueConstJSON (game, rows, "rows", pathJSON);
  textureAtlas->rows = rows->valueint;

  tileSizeX = cJSON_GetObjectItemCaseSensitive (textureAtlasJSON, "tileSizeX");
  validateValueConstJSON (game, tileSizeX, "tileSizeX", pathJSON);
  textureAtlas->tileSizeX = tileSizeX->valueint;

  tileSizeY = cJSON_GetObjectItemCaseSensitive (textureAtlasJSON, "tileSizeY");
  validateValueConstJSON (game, tileSizeY, "tileSizeY", pathJSON);
  textureAtlas->tileSizeY = tileSizeY->valueint;

  // load texture.
  SDL_Texture *texture
      = IMG_LoadTexture (game->renderer, textureAtlas->textPath);
  if (!texture)
    {
      log_error ("%s", SDL_GetError ());
      exitGame (game);
    }

  // Setze die Textur auf "Nearest Neighbor" (pixelgenaue Skalierung)
  if (!SDL_SetTextureScaleMode (texture, SDL_SCALEMODE_NEAREST))
    {
      log_error ("%s", SDL_GetError ());
      exitGame (game);
    }

  textureAtlas->texture = texture;
  cJSON_Delete (textureAtlasJSON);
  printTextureAtlas (textureAtlas, LOG_DEBUG);
  return textureAtlas;
}

void
destroy_TextureAtlas (TextureAtlas *atlas)
{
  SDL_DestroyTexture (atlas->texture);
  free (atlas);
}

struct Map *
load_Map (GameState *game, int cols, int rows, const cJSON *backgroundMap,
          const cJSON *middelgroudMap, const cJSON *spriteMap,
          const cJSON *logicMap)
{
  struct Map *map = malloc (sizeof (struct Map));
  map->cols = cols;
  map->rows = rows;
  map->backgroundMap = createMatrixJSON (game, rows, cols, backgroundMap);
  map->middelgroudMap = createMatrixJSON (game, rows, cols, middelgroudMap);
  map->spriteMap = createMatrixJSON (game, rows, cols, spriteMap);
  map->logicMap = createMatrixJSON (game, rows, cols, logicMap);
  printMap (map, LOG_TRACE);
  return map;
}

struct Sub *
load_Sub (GameState *game, char *pathJSON)
{
  struct Sub *sub = malloc (sizeof (struct Sub));

  char *jsonString = readFile (pathJSON);
  if (!jsonString)
    {
      log_error ("JSON-Datei=%s konnte nicht gelesen werden!", pathJSON);
      exitGame (game);
    }
  cJSON *subJSON = cJSON_Parse (jsonString);
  free (jsonString);
  validateValueJSON (game, subJSON);

  const cJSON *subID = NULL;
  const cJSON *cols = NULL;
  const cJSON *rows = NULL;
  const cJSON *backgroundMap = NULL;
  const cJSON *middelgroudMap = NULL;
  const cJSON *spriteMap = NULL;
  const cJSON *logicMap = NULL;

  subID = cJSON_GetObjectItemCaseSensitive (subJSON, "subID");
  validateValueConstJSON (game, subID, "subID", pathJSON);
  cols = cJSON_GetObjectItemCaseSensitive (subJSON, "cols");
  validateValueConstJSON (game, cols, "cols", pathJSON);
  rows = cJSON_GetObjectItemCaseSensitive (subJSON, "rows");
  validateValueConstJSON (game, rows, "rows", pathJSON);

  // in LoadMap gets validated the json;
  backgroundMap = cJSON_GetObjectItemCaseSensitive (subJSON, "backgroundMap");
  validateValueConstJSON (game, backgroundMap, "backgroundMap", pathJSON);
  middelgroudMap
      = cJSON_GetObjectItemCaseSensitive (subJSON, "middelgroudMap");
  validateValueConstJSON (game, middelgroudMap, "middelgroudMap", pathJSON);
  spriteMap = cJSON_GetObjectItemCaseSensitive (subJSON, "spriteMap");
  validateValueConstJSON (game, spriteMap, "spriteMap", pathJSON);
  logicMap = cJSON_GetObjectItemCaseSensitive (subJSON, "logicMap");
  validateValueConstJSON (game, logicMap, "logicMap", pathJSON);

  strncpy (sub->ID, subID->valuestring, sizeof (sub->ID) - 1);
  sub->ID[sizeof (sub->ID) - 1] = '\0';

  sub->map = load_Map (game, cols->valueint, rows->valueint, backgroundMap,
                       middelgroudMap, spriteMap, logicMap);
  cJSON_Delete (subJSON);
  printSub (sub, LOG_TRACE);
  return sub;
}

void
destroy_Sub (struct Sub *sub)
{
  destroy_Map (sub->map);
  free (sub);
}

void
destroy_Map (struct Map *map)
{
  free (map->backgroundMap);
  free (map->logicMap);
  free (map->middelgroudMap);
  free (map->spriteMap);
  free (map);
}

GameState *
init_GameState ()
{
  GameState *game = (GameState *)malloc (sizeof (GameState));
  // setup window and renderer context SDL3.
  if (!SDL_CreateWindowAndRenderer (NAME_OF_GAME, WINDOW_WIDTH, WINDOW_HEIGHT,
                                    0, &game->window, &game->renderer))
    {
      log_error ("%s", SDL_GetError ());
      exitGame (game);
    }
  // load game components.
  load_Display (game);
  load_Keymap (game);
  init_ENVStack (game);
  printGameState (game, LOG_TRACE);
  return game;
}

void
destroy_GameState (GameState *game)
{
  destroy_Display (&game->display);
  destroy_ENVStack (&game->envStack);
  destroy_Keymap (game->keymap);
  destroy_Player (game->player);
  free (game);
}

void
destroyUIElement (struct UIElement *uiEl)
{
  // TODO
  free (uiEl);
}

struct ENV *
load_ENV (GameState *game, char *pathJSON)
{
  // create env from JSON.
  log_trace ("Loading Enviroment from %s ...", pathJSON);
  struct ENV *env = malloc (sizeof (struct ENV));
  char *jsonString = readFile (pathJSON);
  if (!jsonString)
    {
      log_warn ("JSON-Datei konnte nicht gelesen werden!");
      return NULL;
    }
  cJSON *envJSON = cJSON_Parse (jsonString);
  free (jsonString);
  if (envJSON == NULL)
    {
      log_warn ("JSON File with path %s was not found!", pathJSON);
    }
  validateValueJSON (game, envJSON);
  const cJSON *ID = NULL;
  const cJSON *enableGlobalUI = NULL;
  const cJSON *tilesheetPath = NULL;
  const cJSON *spritesheetPath = NULL;
  const cJSON *subIDs = NULL;
  const cJSON *subID = NULL;
  const cJSON *initSubID = NULL;
  const cJSON *type = NULL;

  ID = cJSON_GetObjectItemCaseSensitive (envJSON, "ID");
  validateValueConstJSON (game, ID, "ID", pathJSON);
  validateTypeValueJSON (game, ID, cJSON_IsString);

  // ceck if gloable ui is not enabled.
  enableGlobalUI
      = cJSON_GetObjectItemCaseSensitive (envJSON, "enableGlobalUI");
  if (enableGlobalUI == NULL)
    {
      env->enableGlobalUI = true;
    }
  else
    {
      validateTypeValueJSON (game, enableGlobalUI, cJSON_IsBool);
      env->enableGlobalUI = cJSON_IsTrue (enableGlobalUI);
    }

  // TextureAtlas Paths.
  tilesheetPath = cJSON_GetObjectItemCaseSensitive (envJSON, "tilesheetPath");
  validateValueConstJSON (game, tilesheetPath, "tilesheetPath", pathJSON);
  validateTypeValueJSON (game, tilesheetPath, cJSON_IsString);

  spritesheetPath
      = cJSON_GetObjectItemCaseSensitive (envJSON, "spritesheetPath");
  validateValueConstJSON (game, tilesheetPath, "spritesheetPath", pathJSON);
  validateTypeValueJSON (game, tilesheetPath, cJSON_IsString);

  // switch case for enum
  type = cJSON_GetObjectItemCaseSensitive (envJSON, "type");
  validateValueConstJSON (game, type, "type", pathJSON);
  validateTypeValueJSON (game, type, cJSON_IsString);
  ;
  env->type = toENVType (game, type->valuestring);

  initSubID = cJSON_GetObjectItemCaseSensitive (envJSON, "initSubID");
  validateValueConstJSON (game, initSubID, "initSubID", pathJSON);
  validateTypeValueJSON (game, initSubID, cJSON_IsString);

  // Hash Map sub IDs
  struct hashmap *subRoomIDMap
      = hashmap_new (sizeof (struct SubRoomIDNode), 0, 0, 0,
                     hash_subRoomIDNode, compare_subRoomIDNode, NULL, NULL);
  subIDs = cJSON_GetObjectItemCaseSensitive (envJSON, "subIDs");
  validateValueConstJSON (game, subIDs, "subIDs", pathJSON);
  cJSON *item = NULL;
  cJSON_ArrayForEach (item, subIDs)
  {
    cJSON *idJSON = cJSON_GetObjectItemCaseSensitive (item, "ID");
    validateValueJSON (game, idJSON);
    cJSON *pathJSON = cJSON_GetObjectItemCaseSensitive (item, "path");
    validateValueJSON (game, pathJSON);
    struct SubRoomIDNode sub;
    sub.id = idJSON->valuestring;
    sub.path = pathJSON->valuestring;
    if (hashmap_set (subRoomIDMap, &sub) == NULL)
      {
        log_trace ("Item was added to hashmap:\n{\n\tID=%s;\n\tpath=%s\n}",
                   sub.id, sub.path);
      }
    else
      {
        log_warn ("Item in hashmap was repaced:\n{\n\tID=%s;\n\tpath=%s\n}",
                  sub.id, sub.path);
      }
  }

  struct SubRoomIDNode searchKey;
  searchKey.id = initSubID->valuestring;
  const struct SubRoomIDNode *node = hashmap_get (subRoomIDMap, &searchKey);
  if (node == NULL)
    {
      log_error ("'initSubIDs'(%s) path isn't present in subIDs!",
                 initSubID->valuestring);
      exitGame (game);
    }
  // TODO
  strncpy (env->ID, ID->valuestring, sizeof (env->ID) - 1);
  env->ID[sizeof (env->ID) - 1] = '\0';
  env->sub = load_Sub (game, node->path);
  env->subRoomIDMap = subRoomIDMap;
  env->tilesheet = load_TextureAtlasJSON (game, tilesheetPath->valuestring);
  env->spritesheet
      = load_TextureAtlasJSON (game, spritesheetPath->valuestring);
  env->isLocalUIActive = false;
  // deciedes EnvStack.
  env->toRender = true;

  // TODO UI for Envoiment not implemented.
  env->uiElementCount = 0;
  cJSON_Delete (envJSON);
  printEnviroment (env, LOG_DEBUG);
  return env;
}

void
destroy_ENV (struct ENV *env)
{
  for (int i = 0; i < env->uiElementCount; i++)
    {
      struct UIElement *el = env->uiElements[i];
      destroyUIElement (env->uiElements[i]);
    }
  destroy_TextureAtlas (env->spritesheet);
  destroy_TextureAtlas (env->tilesheet);
  destroy_Sub (env->sub);
  hashmap_free (env->subRoomIDMap);
  free (env);
}

struct ENV_StackItem *
create_ENV_StackItem (struct ENV_StackItem *next, struct ENV *env)
{
  struct ENV_StackItem *item = malloc (sizeof (struct ENV_StackItem));
  item->env = env;
  item->next = next;
  return item;
}

void
destroy_ENV_StackItem (struct ENV_StackItem *stackItem)
{
  // pointer next won't be destoryed here.
  destroy_ENV (stackItem->env);
  free (stackItem->env);
}

void
init_ENVStack (GameState *game)
{
  game->envStack.size = 0;
  game->envStack.top = NULL;
  printEnviromentStack (&game->envStack, LOG_TRACE);
}

void
destroy_ENVStack (ENV_Stack *envStack)
{
  struct ENV_StackItem *item = envStack->top;
  while (item != NULL)
    {
      struct ENV_StackItem *temp = item;
      item = item->next;
      destroy_ENV_StackItem (temp);
    }
  free (envStack);
}

// ---- EnviromentStack functions ----
void
push_ENV (GameState *game, char *pathJSON)
{
  struct ENV *env = load_ENV (game, pathJSON);
  struct ENV_StackItem *stackItem = create_ENV_StackItem (NULL, env);
  // push env to EnvStack.
  stackItem->next = game->envStack.top;
  game->envStack.top = stackItem;
  game->envStack.size++;
  updateToRenderFlagsFromStackEnvs (game->envStack.top);
  printEnviromentStack (&game->envStack, LOG_TRACE);
}

void
pop_ENV (GameState *game)
{
  struct ENV_StackItem *stackItem = game->envStack.top;
  if (stackItem->next == NULL)
    {
      log_warn (
          "\nLast Element from ENV-Stack was poped.\nGame will close now!");
      exitGame (game);
    }
  game->envStack.top = stackItem->next;
  destroy_ENV_StackItem (stackItem);
  game->envStack.size--;
  updateToRenderFlagsFromStackEnvs (game->envStack.top);
  printEnviromentStack (&game->envStack, LOG_TRACE);
}

/**
 * Implements render hierary for EnviromentStack in terms of which envs get
 * rendered.
 */
void
updateToRenderFlagsFromStackEnvs (struct ENV_StackItem *item)
{
  if (item == NULL || item->next == NULL)
    {
      return;
    }
  setToRenderFlagFromLowerENV (item->env, item->next->env);
  return updateToRenderFlagsFromStackEnvs (item->next);
}

void
setToRenderFlagFromLowerENV (struct ENV *top, struct ENV *next)
{
  if (next != NULL)
    {
      if (top->toRender)
        {
          switch (top->type)
            {
            case ENV_MENU:
              next->toRender = true;
              return;
            case ENV_WORLD:
              next->toRender = false;
              return;
            case ENV_COMBAT:
              next->toRender = false;
              return;
            }
        }
      else
        {
          next->toRender = false;
        }
    }
}

// ---- Convert String to ENUM ----
enum ENV_Type
toENVType (GameState *game, char *string)
{
#ifdef _WIN32
  if (_stricmp ("ENV_COMBAT", string) == 0)
    {
      log_trace ("toEnviromentType: %s to ENV_COMBAT", string);
      return ENV_COMBAT;
    }
  if (_stricmp ("ENV_WORLD", string) == 0)
    {
      log_trace ("toEnviromentType: %s to ENV_WORLD", string);
      return ENV_WORLD;
    }
  if (_stricmp ("ENV_MENU", string) == 0)
    {
      log_trace ("toEnviromentType: %s to ENV_MENU", string);
      return ENV_MENU;
    }
#elif defined(__linux__) || defined(__APPLE__)
  if (strcasecmp ("ENV_COMBAT", string) == 0)
    {
      return ENV_COMBAT;
    }
  if (strcasecmp ("ENV_WORLD", string) == 0)
    {
      return ENV_WORLD;
    }
  if (strcasecmp ("ENV_MENU", string) == =)
    {
      return ENV_MENU;
    }
#endif
  log_error ("No EnviromentType matches with %s", string);
  exitGame (game);
}

enum TextureType
toTextureType (GameState *game, char *string)
{
#ifdef _WIN32
  if (_stricmp ("TEXT_STATIC", string) == 0)
    {
      log_trace ("toTextureType: %s to TEXT_STATIC", string);
      return TEXT_STATIC;
    }
  if (_stricmp ("TEXT_ANIMATED", string) == 0)
    {
      log_trace ("toTextureType: %s to TEXT_ANIMATED", string);
      return TEXT_ANIMATED;
    }
#elif defined(__linux__) || defined(__APPLE__)
  if (strcasecmp ("TEXT_STATIC", string) == 0)
    {
      return TEXT_STATIC;
    }
  if (strcasecmp ("TEXT_ANIMATED", string) == 0)
    {
      return TEXT_ANIMATED;
    }
#endif
  log_error ("No TextureType matches with %s", string);
  exitGame (game);
}
