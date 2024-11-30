
#include "app.h"



int AppInit(pApp app) {

    if (ENV_USE_CONSOLE) {
        app->console = ConsoleCreate(1);
        if (!app->console) {
            return FALSE;
        }
    }

    sfVideoMode mode = { FROZEN_LAKE_SCREEN_SIZE, FROZEN_LAKE_SCREEN_SIZE, 32 };
    app->sfMainWindow = sfRenderWindow_create(mode, ENV_WINDOW_TITLE, sfDefaultStyle, NULL);
    sfRenderWindow_setFramerateLimit(app->sfMainWindow, ENV_FRAMERATE);
    sfRenderWindow_setVerticalSyncEnabled(app->sfMainWindow, sfTrue);

    app->map = MapCreate(ENV_MAP_STR, ENV_MAP_SIZE);
    if (!app->map) {
        sfRenderWindow_destroy(app->sfMainWindow);
        ConsoleDestroy(app->console);
        return FALSE;
    }

    app->hero = HeroCreate(app->map);
    if (!app->hero) {
        MapDestroy(app->map);
        sfRenderWindow_destroy(app->sfMainWindow);
        ConsoleDestroy(app->console);
        return FALSE;
    }

    app->goal = GoalCreate(app->map);
    if (!app->goal) {
        HeroDestroy(app->hero);
        MapDestroy(app->map);
        sfRenderWindow_destroy(app->sfMainWindow);
        ConsoleDestroy(app->console);
        return FALSE;
    }

	InterpreterInit(&app->interpreter, app->hero);

    return TRUE;

}


void AppRedraw(pApp app) {
    printf("APP REDRAW\n");

    // Clear the screen
    sfRenderWindow_clear(app->sfMainWindow, sfBlack);

    MapDraw(app->map, app->sfMainWindow);
    GoalDraw(app->goal, app->sfMainWindow);
    HeroDraw(app->hero, app->sfMainWindow);

    // Update the window
    sfRenderWindow_display(app->sfMainWindow);
}


int AppProcessWinMessage(pApp app, const MSG* msg) {

    switch (msg->message)
    {
    case WM_KEYDOWN:
        {
        switch (msg->wParam)
        {
        case VK_UP: {
            printf("UP\n");
            HeroMove(app->hero, DIRECTION_U);
            break; 
        }
        case VK_DOWN:  {
            printf("DOWN\n");
            HeroMove(app->hero, DIRECTION_D);
            break;
        }
        case VK_LEFT:  {
            printf("LEFT\n");
            HeroMove(app->hero, DIRECTION_L);
            break;
        }
        case VK_RIGHT: {
            printf("RIGHT\n");
            HeroMove(app->hero, DIRECTION_R);
            break;
        }
        default:
            break;
        }
        }
    case WM_KEYUP: { }
    default:
        break;
    }

    return 1;
}



int AppDestroy(pApp app) {

    GoalDestroy(app->goal);
    HeroDestroy(app->hero);
    MapDestroy(app->map);

    sfRenderWindow_destroy(app->sfMainWindow);

    ConsoleDestroy(app->console);

    return 1;
}
