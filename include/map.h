#ifndef MAP_H__
#define MAP_H__

#include <SFML/Graphics.h>

#include "framework.h"
#include "point.h"
#include "env.h"


/* Zise of the sqare bitmap size */
#define MAP_TILE_SIZE 32


/*
+======================================================================+
|                            Tile Type                                 |
+======================================================================+
*/


typedef enum tagTileType {
    TILE_TYPE_NO     = 0,
    TILE_TYPE_START  = 'S',
    TILE_TYPE_GOAL   = 'G',
    TILE_TYPE_FROZEN = 'F',
    TILE_TYPE_HOLE   = 'H',
} tTileType;


/*
    Get a info stinrg about tile type
*/
const char* TileType2Str(tTileType tile);


/*
    Check if a hero can step on a tile of type `tile`
*/
int TileTypeIsSteppable(tTileType tile);





/*
+======================================================================+
|                            MAP Interface                             |
+======================================================================+
*/



/* Map handle */
typedef struct tagMap *hMap;


/*
    Create map from a string
*/
hMap MapCreate(char* mapstr, uint8_t size);


/*
    Draw a map on the window
    Params:
        - `map`: map handle
        - `renderWindow`: CSFML Render Window handle (pointer)
*/
void MapDraw(hMap map, sfRenderWindow* renderWindow);


/*
    Get type of a tile at position `pos`
*/
tTileType MapGetTile(hMap map, tPos pos);


/*
    Get the player's start position
*/
tPos MapGetStartPosition(hMap map);


/*
    Get the goal position
*/
tPos MapGetGoalPosition(hMap map);


/*
    Free map resources
*/
void MapDestroy(hMap map);



#endif // !MAP_H__
