#ifndef POINT_H__
#define POINT_H__

#include "framework.h"


typedef struct tagPos{
    uint8_t x;
    uint8_t y;
} tPos;


typedef enum tagDirection{
	DIRECTION_UNKNOWN = -1,
    DIRECTION_L = 1,
    DIRECTION_D,
    DIRECTION_R,
    DIRECTION_U,
} tDirection;




static inline int PosGetLinear(tPos pos, uint8_t ysize) {
    return pos.y * ysize + pos.x;
}

static inline tPos PosGetFromLinear(int linpos, uint8_t xsize) {
    return (tPos){linpos % xsize, linpos / xsize};
}

static inline tPos PosMove(tPos pos, tDirection dir) {
    switch (dir) 
    {
    case DIRECTION_L : { pos.x -= 1; break; }
    case DIRECTION_D : { pos.y += 1; break; }
    case DIRECTION_R : { pos.x += 1; break; }
    case DIRECTION_U : { pos.y -= 1; break; }
    default:
        break;
    }
    return pos;
}

#endif // !POINT_H__



