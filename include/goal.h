#ifndef GOAL_H__
#define GOAL_H__

#include <SFML/Graphics.h>

#include "framework.h"
#include "point.h"
#include "map.h"


/*
    Goal handle
*/
typedef struct tagGoal tGoal, *hGoal;


/*
    Goal creation function
    Params:
        - `map`: handle to a map instance

    Returns:
        a handle to a created goal instance
*/
hGoal GoalCreate(hMap map);


/*
    Draw the goal bitmap on the window
    Params:
        - `goal`: handle to a goal instance
        - `renderWindow`: pointer to a SFML render window
*/
int GoalDraw(hGoal goal, sfRenderWindow* renderWindow);


/*
    Free allocated resources
*/
void GoalDestroy(hGoal goal);


#endif // !GOAL_H__
