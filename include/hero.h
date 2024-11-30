#ifndef HERO_H__
#define HERO_H__


#include <SFML/Graphics.h>

#include "framework.h"
#include "map.h"
#include "point.h"



typedef enum tagHeroAction {
	HERO_ACTION_L = 1,
	HERO_ACTION_D,
	HERO_ACTION_R,
	HERO_ACTION_U,
} tHeroAction;



typedef struct tagHero tHero, * hHero;




hHero HeroCreate(hMap map);

int HeroDraw(hHero hero, sfRenderWindow* renderWindow);

int HeroMove(hHero hero, tDirection dir);

int HeroGoalReached(hHero hero);

int HeroHoleReached(hHero hero);

int HeroGoToStart(hHero hero);

tTileType HeroGetCurrentTile(hHero hero);

tTileType HeroLook(hHero hero, tDirection dir);

void HeroDestroy(hHero hero);





#endif // !HERO_H__
