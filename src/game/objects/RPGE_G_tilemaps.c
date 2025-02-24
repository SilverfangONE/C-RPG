#include "RPGE_G_tilemap.h"
#include "log.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>
/*
    Tilemap_RPGE *create_Tilemap_G_RPGE(Assetsheet_RPGE *asset, Vec2D vTableSize, char *ID, int *m_indices, bool
   *m_solid)
    {
        Tilemap_RPGE *tilemap = (Tilemap_RPGE *)malloc(sizeof(Tilemap_RPGE));
        if (tilemap == NULL)
        {
            return NULL;
        }
        // set ID.
        if (ID == NULL || strlen(ID) == 0)
        {
            log_error("create_Tilemap_G_RPGE: ID is invalid");
            errno = EINVAL;
            return NULL;
        }
        tilemap->ID = (char *)malloc(sizeof(tilemap));
        strncpy(tilemap->ID, ID, sizeof(tilemap->ID));

        // set vTableSize.
        if (vTableSize.x == 0 || vTableSize.x == 0)
        {
            log_error("create_Tilemap_G_RPGE: vTableSize is invalid");
            errno = EINVAL;
            return NULL;
        }
        tilemap->vTableSize = vTableSize;

        // set Asset.
        if (asset == NULL)
        {
            log_error("create_Tilemap_G_RPGE: asset is invalid");
            errno = EINVAL;
            return NULL;
        }
        tilemap->asset = asset;

        // set m_indices.
        if (m_indices == NULL)
        {
            log_error("create_Tilemap_G_RPGE: m_indices is invalid");
            errno = EINVAL;
            return NULL;
        }
        setIndices_Tilemap_G_RPGE(tilemap, m_indices);

        // set m_solid.
        if (m_solid == NULL)
        {
            log_error("create_Tilemap_G_RPGE: m_solid is invalid");
            errno = EINVAL;
            return NULL;
        }
        setSolids_Tilemap_G_RPGE(tilemap, m_solid);

        return tilemap;
    }

    void destroy_Tilemap_G_RPGE(Tilemap_RPGE *tilemap)
    {
        free(tilemap->asset);
        free(tilemap->ID);
        free(tilemap);
    }

    void setIndices_Tilemap_G_RPGE(Tilemap_RPGE *map, int *m_indices)
    {
        map->m_indices = (int *)malloc(sizeof(int) * (map->vTableSize.x * map->vTableSize.y));
        // copy
        for (int i = 0; i < (map->vTableSize.x * map->vTableSize.y); i++)
        {
            map->m_indices[i] = m_indices[i];
        }
    }

    void setSolids_Tilemap_G_RPGE(Tilemap_RPGE *map, bool *m_solid)
    {
        map->m_solid = (bool *)malloc(sizeof(bool) * (map->vTableSize.x * map->vTableSize.y));
        // copy
        for (int i = 0; i < (map->vTableSize.x * map->vTableSize.y); i++)
        {
            map->m_solid[i] = m_solid[i];
        }
    }

    int getIndex_Tilemap_G_RPGE(Tilemap_RPGE *map, int x, int y)
    {
        if (x > -1 && x < map->vTableSize.x && y > -1 && y < map->vTableSize.y)
        {
            return map->m_indices[y * map->vTableSize.x + x];
        }
        return -1;
    }

    bool getSolid_Tilemap_G_RPGE(Tilemap_RPGE *map, int x, int y)
    {
        if (x > -1 && x < map->vTableSize.x && y > -1 && y < map->vTableSize.y)
        {
            return map->m_solid[y * map->vTableSize.x + x];
        }
        return -1;
    }
*/