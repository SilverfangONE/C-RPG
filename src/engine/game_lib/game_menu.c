// https://www.youtube.com/watch?v=jde1Jq5dF0E&t=1359s
#include "game_menu.h"
#include "log.h"
#include <stdlib.h>
#include <string.h>

static int compare_Node_mobj (const void *a, const void *b, void *udata);
static uint64_t hash_Node_mobj (const void *item, uint64_t seed0,
                                uint64_t seed1);
static bool iter_Node_mobj (const void *item, void *udata);
static int maxValue (int a, int b);

const int nPatch = 8;

// &&&& KONST. &&&&
/**
 * MenuObject default.
 */
static MenuObject *
init_mobj ()
{
  MenuObject *mobj = (MenuObject *)malloc (sizeof (MenuObject));
  mobj->bEnable = true;
  mobj->nID = -1;
  mobj->nTotalRows = 0;
  mobj->vCellTable = (Vec2D){ 1, 0 };
  mobj->vCellSize = (Vec2D){ 0, 0 };
  mobj->vCellPadding = (Vec2D){ 2, 0 };
  mobj->vPatchSize = (Vec2D){ nPatch, nPatch };
  mobj->vSizeInPatches = (Vec2D){ 0, 0 };
  mobj->items = hashmap_new (sizeof (struct MenuObject), 0, 0, 0,
                             hash_Node_mobj, compare_Node_mobj, NULL, NULL);
  return mobj;
}

/**
 * MenuObject Konst.
 * def = 0: calls default create_mobj (void, 0);
 * else: creates mobj with (name, 1);
 */
MenuObject *
create_mobj (char *name, int mod)
{
  MenuObject *mobj;
  switch (mod)
    {
    case 0:
      mobj = init_mobj ();
      mobj->sName = "root";
      return mobj;
    case 1:
      MenuObject *mobj = init_mobj ();
      mobj->sName = name;
      return mobj;
    default:
      log_warn (
          "Mode %d is not supported for create_mobj(char* name, int mod)!",
          mod);
      return NULL;
    }
}

/**
 * MenuObject Desctructor
 */
void
destroy_mobj (MenuObject *mobj)
{
  free (mobj->items);
  free (mobj);
}

// &&&& SETTER &&&&
MenuObject *
setTable_mobj (MenuObject *mobj, int nColumns, int nRows)
{
  mobj->vCellTable = (Vec2D){ .x = nColumns, .y = nRows };
  return mobj;
}
MenuObject *
setID_mobj (MenuObject *mobj, int ID)
{
  mobj->nID = ID;
  return mobj;
}
MenuObject *
enable_mobj (MenuObject *mobj, bool b)
{
  mobj->bEnable = b;
  return mobj;
}

// &&&& GETTER &&&&
int
getID_mobj (const MenuObject *mobj)
{
  return mobj->nID;
}
char *
getName_mobj (const MenuObject *mobj)
{
  return mobj->sName;
}
/**
 * For now, cells are simply one line strings
 */
Vec2D
getSize_mobj (const MenuObject *mobj)
{
  return (Vec2D){ (int)strlen (mobj->sName), 1 };
}

bool
hasChildren_mobj (const MenuObject *mobj)
{
  return (bool)hashmap_count (mobj->items);
}

/**
 * Add Child MenuObject
 * @param mobjP MenuObject Parent
 * @param mobjC MenuObject Child
 */
MenuObject *
addChild_mobj (MenuObject *mobjP, MenuObject *mobjC)
{
  if (hashmap_set (mobjP->items,
                   &(struct Node_mobj){ .key = mobjC->sName, .value = mobjC })
      != NULL)
    {
      log_warn ("Replaced element with same key %s!", mobjC->sName);
    }
  return mobjC;
}

/**
 * Access MenuObject Child
 */
MenuObject *
accessChild_mobj (MenuObject *mobj, char *sName)
{
  const struct Node_mobj *node
      = hashmap_get (mobj->items, &(struct Node_mobj){ .key = mobj->sName });
  return node->value;
}

// only gets executed if MenuObject is a panel
void
DrawSelf_mobj (SDL_Renderer *renderer, SDL_Texture *menuTilesheet,
               MenuObject *mobj)
{
  // Draw Panel and Border
  Vec2D vPatchPos = { 0, 0 };
  for (vPatchPos.x = 0; vPatchPos.x < mobj->vSizeInPatches.x; vPatchPos.x++)
  {
    for (vPatchPos.y = 0; vPatchPos.y < mobj->vSizeInPatches.y; vPatchPos.y++) 
    {
      // Determine position in screen space.
      
    }
  }
}

void
Build_mobj (MenuObject *mobj)
{
  // Recursiv build all children, so they can determine their size, use
  // that size to indicate cell sizes if this object contains more than
  // one item
  size_t iter = 0;
  void *item;
  while (hashmap_iter (mobj->items, &iter, &item))
    {
      MenuObject *mobj_Child = ((const struct Node_mobj *)item)->value;
      if (hasChildren_mobj (mobj_Child))
        {
          Build_mobj (mobj_Child);
        }

      // Longest child name determines cell width
      mobj->vCellSize.x
          = maxValue (getSize_mobj (mobj_Child).x, mobj->vCellSize.x);
      mobj->vCellSize.y
          = maxValue (getSize_mobj (mobj_Child).y, mobj->vCellSize.y);
    }

  // Adjust size of object (in patches) if it were rendered as a panel
  mobj->vSizeInPatches.x = mobj->vCellTable.x * mobj->vCellSize.x
                           + (mobj->vCellSize.x - 1) * mobj->vCellPadding.x
                           + 2;
  mobj->vSizeInPatches.y = mobj->vCellTable.y * mobj->vCellSize.y
                           + (mobj->vCellSize.y - 1) * mobj->vCellPadding.y
                           + 2;

  // Calculate how many rows this item has to hold
  int itemsSize = hashmap_count (mobj->items);
  mobj->nTotalRows = (itemsSize / mobj->vCellTable.x)
                     + (((itemsSize % mobj->vCellTable.x) > 0) ? 1 : 0);
}

static int
maxValue (int a, int b)
{
  return a > b ? a : b;
}

// &&&& mmHashmap functions. &&&&
/**
 * Compare Function for MenuManger Nodes Hashmap
 */
static int
compare_Node_mobj (const void *a, const void *b, void *udata)
{
  const struct Node_mobj *a_mobj = a;
  const struct Node_mobj *b_mobj = b;
  return strcmp (a_mobj->key, b_mobj->key);
}

/**
 * Hash Function for MenuMangerNodes Hashmap
 */
static uint64_t
hash_Node_mobj (const void *item, uint64_t seed0, uint64_t seed1)
{
  const struct Node_mobj *mobj = item;
  return hashmap_sip (mobj->key, strlen (mobj->key), seed0, seed1);
}
