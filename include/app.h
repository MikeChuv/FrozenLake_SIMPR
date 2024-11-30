#ifndef APP_H__
#define APP_H__


#include "env.h"
#include "interpreter.h"
#include "console.h"
#include "map.h"
#include "hero.h"
#include "goal.h"


#define FROZEN_LAKE_SCREEN_SIZE  ENV_MAP_SIZE * MAP_TILE_SIZE * ENV_SCREEN_SCALE



/*
    App instance structure
*/
typedef struct tagApp {
    tInterpreter    interpreter;      /* interpreter instance           */
    hConsole        console;          /* handle to a console            */
    HWND            winapiMainWindow; /* handle to a winsows app window */
    sfRenderWindow* sfMainWindow;     /* handle to a SFML window        */
    hMap            map;              /* map handle  */
    hHero           hero;             /* hero handle */
    hGoal           goal;             /* goal handle */
} tApp, *pApp;


/*
    Initialize app and its components
*/
int AppInit(pApp app);


/*
    Process a received Windows message
*/
int AppProcessWinMessage(pApp app, const MSG* msg);


/*
    Redraw the app's SFML window
*/
void AppRedraw(pApp app);



int AppDestroy(pApp app);




#endif // !APP_H__