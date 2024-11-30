

#include "hero.h"


#define HERO_FILE  "./resources/hero.png"

#define HERO_TILE_SIZE      32
#define HERO_POSITION_SCALE ENV_SCREEN_SCALE * HERO_TILE_SIZE;

#define HERO_TEXTURE_RECT(i, j) ((sfIntRect){(j) * HERO_TILE_SIZE, (i) * HERO_TILE_SIZE, HERO_TILE_SIZE, HERO_TILE_SIZE})


typedef enum tagHeroBitmapColOffset {
    HERO_BITMAP_COL_OFFSET_0,
    HERO_BITMAP_COL_OFFSET_1,
    HERO_BITMAP_COL_OFFSET_TEXT,
    HERO_BITMAP_COL_OFFSET_LENGTH,
} tHeroBitmapColOffset;

typedef enum tagHeroBitmapRowOffset {
    HERO_BITMAP_ROW_OFFSET_FRONT,
    HERO_BITMAP_ROW_OFFSET_BACK,
    HERO_BITMAP_ROW_OFFSET_RIGHT,
    HERO_BITMAP_ROW_OFFSET_LEFT,
    HERO_BITMAP_ROW_OFFSET_LENGTH,
} tHeroBitmapRowOffset;



struct tagHero {
    tPos pos;
    hMap map;

    sfTexture* bitmap;
    sfSprite* sprites[HERO_BITMAP_ROW_OFFSET_LENGTH][HERO_BITMAP_COL_OFFSET_LENGTH];

    sfSprite* sprite;

};


static int _HeroSetPosition(hHero hero, tPos pos);
static int _HeroSetSpriteForDirection(hHero hero, tDirection dir, tHeroBitmapColOffset bank);





static inline sfVector2f _HeroGetSpritePosition(tPos pos) {
    return (sfVector2f) {
        ENV_SCREEN_SCALE * HERO_TILE_SIZE * pos.x,
        ENV_SCREEN_SCALE * HERO_TILE_SIZE * pos.y
    };
}

static inline int _HeroSpriteUpdatePosition(hHero hero) {
    assert(hero);
    sfSprite_setPosition(hero->sprite, _HeroGetSpritePosition(hero->pos));
    return 1;
}

static int _HeroSetPosition(hHero hero, tPos pos) {
    assert(hero);
    if (MapGetTile(hero->map, pos) == TILE_TYPE_NO) {
        return 0;
    }
    hero->pos = pos;
    _HeroSpriteUpdatePosition(hero);
    return 1;
}

static int _HeroSetSpriteForDirection(hHero hero, tDirection dir, tHeroBitmapColOffset bank) {
    sfSprite* sprite = hero->sprite;
    switch (dir)
    {
    case DIRECTION_L : { sprite = hero->sprites[HERO_BITMAP_ROW_OFFSET_LEFT ][bank]; break; }
    case DIRECTION_D : { sprite = hero->sprites[HERO_BITMAP_ROW_OFFSET_FRONT][bank]; break; }
    case DIRECTION_R : { sprite = hero->sprites[HERO_BITMAP_ROW_OFFSET_RIGHT][bank]; break; }
    case DIRECTION_U : { sprite = hero->sprites[HERO_BITMAP_ROW_OFFSET_BACK ][bank]; break; }
    default:
        break;
    }
    hero->sprite = sprite;
    return 1;
}









hHero HeroCreate(hMap map) {
    assert(map != NULL);

    hHero hero = (hHero)malloc(sizeof(tHero));
    if (!hero) {
        return NULL;
    }
    hero->map = map;

    hero->pos = MapGetStartPosition(hero->map);

    hero->bitmap = sfTexture_createFromFile(HERO_FILE, NULL);
    for (int i = 0; i < HERO_BITMAP_ROW_OFFSET_LENGTH; ++i) {
        for (int j = 0; j < HERO_BITMAP_COL_OFFSET_LENGTH; ++j) {
            sfSprite** sprite = &hero->sprites[i][j];
            *sprite = sfSprite_create();
            sfSprite_setTexture(    *sprite, hero->bitmap, sfTrue);
            sfSprite_setTextureRect(*sprite, HERO_TEXTURE_RECT(i, j));
            sfSprite_setScale(      *sprite, ENV_SPRITE_SCALE);
        }
    }

    hero->sprite = hero->sprites[HERO_BITMAP_ROW_OFFSET_FRONT][HERO_BITMAP_COL_OFFSET_0];

    _HeroSpriteUpdatePosition(hero);

    return hero;
}

int HeroDraw(hHero hero, sfRenderWindow* renderWindow) {
    assert(hero != NULL);
    _HeroSpriteUpdatePosition(hero);
    sfRenderWindow_drawSprite(renderWindow, hero->sprite, NULL);
    return 1;
}


int HeroMove(hHero hero, tDirection dir) {
    assert(hero);

    tTileType tile = HeroLook(hero, dir);
    if (tile == TILE_TYPE_NO) {
        return 0;
    }

    _HeroSetSpriteForDirection(hero, dir, HERO_BITMAP_COL_OFFSET_0);
    hero->pos = PosMove(hero->pos, dir);
    printf("HERO MOVED TO x=%d, y=%d\n", hero->pos.x, hero->pos.y);
    return 1;
}


int HeroGoalReached(hHero hero) {
    assert(hero);
    return (MapGetTile(hero->map, hero->pos) == TILE_TYPE_GOAL);
}

int HeroHoleReached(hHero hero) {
    assert(hero);
    return (MapGetTile(hero->map, hero->pos) == TILE_TYPE_HOLE);
}

int HeroGoToStart(hHero hero) {
    assert(hero);
    hero->sprite = hero->sprites[HERO_BITMAP_ROW_OFFSET_FRONT][HERO_BITMAP_COL_OFFSET_0];
    _HeroSetPosition(hero, MapGetStartPosition(hero->map));
    return 1;
}



// TODO rename
tTileType HeroGetCurrentTile(hHero hero) {
    assert(hero);
    return MapGetTile(hero->map, hero->pos);
}





tTileType HeroLook(hHero hero, tDirection dir) {
    assert(hero);
    tPos lookPos = hero->pos;
    switch (dir) 
    {
    case DIRECTION_L : { 
        lookPos.x -= 1;
        return MapGetTile(hero->map, lookPos);
    }
    case DIRECTION_D : {
        lookPos.y += 1;
        return MapGetTile(hero->map, lookPos);
    }
    case DIRECTION_R : {
        lookPos.x += 1;
        return MapGetTile(hero->map, lookPos);
    }
    case DIRECTION_U : {
        lookPos.y -= 1;
        return MapGetTile(hero->map, lookPos);
    }
    default:
        return TILE_TYPE_NO;
    }
}




void HeroDestroy(hHero hero) {
    if (hero) {

        for (int i = 0; i < HERO_BITMAP_ROW_OFFSET_LENGTH; ++i) {
            for (int j = 0; j < HERO_BITMAP_COL_OFFSET_LENGTH; ++j) {
                sfSprite_destroy(hero->sprites[i][j]);
            }
        }
        // NOTE: do not destroy hero->sprite here! (it is already destroyed since it is an alias)

        free(hero);
        hero = NULL;
    }
}


