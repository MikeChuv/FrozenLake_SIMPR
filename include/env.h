#ifndef ENV_H
#define ENV_H


#include <SFML/Graphics.h>

/*
+======================================================================+
|                 Main FrozenLake environment settings                 |
+======================================================================+
*/



/*
    Map string literal
        - `S` - start
        - `F` - frozen (ice)
        - `H` - hole
        - `G` - goal
*/
#define ENV_MAP_STR \
    "SFFF" \
    "FHFH" \
    "FFFH" \
    "HFFG"

/* Square map size (one side) */
#define ENV_MAP_SIZE     4

/* Screen scale multiplier */
#define ENV_SCREEN_SCALE 4

/* Title of the window */
#define ENV_WINDOW_TITLE "FrozenLake"

/* SFML window settings */
#define ENV_FRAMERATE    60
#define ENV_VSYNC        sfTrue

/* Time spent for each action (to slow down animation) */
#define ENV_ACTION_DELAY 200

/* Console attachment flag */
#define ENV_USE_CONSOLE 0






#define ENV_SPRITE_SCALE       ((sfVector2f){ENV_SCREEN_SCALE, ENV_SCREEN_SCALE})




#endif // !ENV_H


