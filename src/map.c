

#define MAP_SIZE 4

#include "map.h"
#include <SFML/Graphics.h>

#define MAP_ICE_TILE_FILE  "./resources/ice.png"
#define MAP_HOLE_TILE_FILE "./resources/hole.png"
#define MAP_HERO_TILE_FILE "./resources/hero.png"
#define MAP_GOAL_TILE_FILE "./resources/goal.png"


struct tagMap {
    char* mapstr;
    uint8_t size;
    size_t maxidx;
    size_t maplen;
    tPos goalPos;
    tPos startPos;

    sfTexture* texIce;
    sfTexture* texHole;
    sfTexture* texGoal;

    sfSprite** spritesBuf;

};
typedef struct tagMap tMap, *hMap;


const char* TileType2Str(tTileType tile) {
    switch (tile)
    {
    case TILE_TYPE_NO:     { return "TILE_TYPE_NO";     }
    case TILE_TYPE_START:  { return "TILE_TYPE_START";  }
    case TILE_TYPE_GOAL:   { return "TILE_TYPE_GOAL";   }
    case TILE_TYPE_FROZEN: { return "TILE_TYPE_FROZEN"; }
    case TILE_TYPE_HOLE:   { return "TILE_TYPE_HOLE";   }
    default:
        return NULL;
    }
}

int TileTypeIsSteppable(tTileType tile) {
    return (tile == TILE_TYPE_FROZEN || tile == TILE_TYPE_GOAL || tile == TILE_TYPE_START);
}



static sfTexture* _GetTextureForTileType(hMap map, tTileType tileType) {
    switch (tileType)
    {
    case TILE_TYPE_NO:     { return NULL;         }
    case TILE_TYPE_START:  { return map->texIce;  }
    case TILE_TYPE_GOAL:   { return map->texIce;  }
    case TILE_TYPE_FROZEN: { return map->texIce;  }
    case TILE_TYPE_HOLE:   { return map->texHole; }
    default:
        return NULL;
    }
}



hMap MapCreate(char * mapstr, uint8_t size) {

    hMap map = malloc(sizeof(tMap));
    if (!map) {
        return NULL;
    }
    memset(map, 0, sizeof(tMap));

    map->mapstr = mapstr;
    map->size = size;
    //map->maplen = strlen(mapstr); // ???
    map->maplen = strnlen(mapstr, size * size);


    // allocate array of pointers to sprites
    map->spritesBuf = malloc(sizeof(sfSprite*) * map->maplen);
    if (!map->spritesBuf) {
        free(map);
        return NULL;
    }

    map->texIce = sfTexture_createFromFile(MAP_ICE_TILE_FILE, NULL);
    map->texHole = sfTexture_createFromFile(MAP_HOLE_TILE_FILE, NULL);

    if (!(map->texIce && map->texHole)) {
        free(map->spritesBuf);
        free(map);
        return NULL;
    }


    for (int i = 0; i < map->maplen; ++i) {
        tTileType tileType = (tTileType)map->mapstr[i];
        map->spritesBuf[i] = sfSprite_create();

        sfTexture* tex = _GetTextureForTileType(map, tileType);
        sfSprite_setTexture(map->spritesBuf[i], tex, sfTrue);

        sfVector2f spriteScale = {ENV_SCREEN_SCALE, ENV_SCREEN_SCALE};
        sfSprite_setScale(map->spritesBuf[i], spriteScale);

        tPos pos = PosGetFromLinear(i, map->size);
        if (tileType == TILE_TYPE_GOAL)  { map->goalPos = pos;  }
        if (tileType == TILE_TYPE_START) { map->startPos = pos; }
        float x = ENV_SCREEN_SCALE * MAP_TILE_SIZE * pos.x;
        float y = ENV_SCREEN_SCALE * MAP_TILE_SIZE * pos.y;
        sfVector2f spritePosition = {x, y};
        printf("Tile type: %s @ x=%.2f y=%.2f\n", TileType2Str(tileType), x, y);
        sfSprite_setPosition(map->spritesBuf[i], spritePosition);
    }


    return map;
}


void MapDraw(hMap map, sfRenderWindow* renderWindow) {
    assert(map != NULL && renderWindow != NULL);
    for (int i = 0; i < map->maplen; ++i) {
        sfSprite* sprite = map->spritesBuf[i];
        sfRenderWindow_drawSprite(renderWindow, sprite, NULL);
    }
}

void MapDestroy(hMap map) {

    for (int i = 0; i < map->maplen; ++i) {
        sfSprite_destroy(map->spritesBuf[i]);
        map->spritesBuf[i] = NULL;
    }
    sfTexture_destroy(map->texIce);
    sfTexture_destroy(map->texHole);

    free(map);
    map = NULL; // ??
}



tTileType MapGetTile(hMap map, tPos pos) {
    if (pos.x >= map->size || pos.y >= map->size) {
        return TILE_TYPE_NO;
    }
    int lPos = PosGetLinear(pos, map->size);
    if (lPos < 0 || lPos > (map->maplen - 1)) {
        return TILE_TYPE_NO;
    }
    return (tTileType)map->mapstr[lPos];
}


tPos MapGetStartPosition(hMap map) {
    return map->startPos;
}

tPos MapGetGoalPosition(hMap map) {
    return map->goalPos;
}







