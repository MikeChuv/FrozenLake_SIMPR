#ifndef GOAL_H__
#define GOAL_H__

#include <SFML/Graphics.h>

#include "framework.h"
#include "point.h"
#include "map.h"



typedef struct tagGoal tGoal, *hGoal;



hGoal GoalCreate(hMap map);



int GoalDraw(hGoal goal, sfRenderWindow* renderWindow);



void GoalDestroy(hGoal goal);



#endif // !GOAL_H__
