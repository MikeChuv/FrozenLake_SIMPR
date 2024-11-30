
#include "env.h"

#include "goal.h"

#define GOAL_TILE_FILE  "./resources/goal.png"

#define GOAL_TILE_SIZE 32


struct tagGoal {
    sfTexture* texture;
    sfSprite* sprite;
    hMap map;
    tPos pos;
};


static inline sfVector2f _GoalGetSpritePosition(tPos pos) {
    return (sfVector2f) {
        ENV_SCREEN_SCALE * GOAL_TILE_SIZE * pos.x,
        ENV_SCREEN_SCALE * GOAL_TILE_SIZE * pos.y
    };
}


hGoal GoalCreate(hMap map) {
    hGoal goal = (hGoal)malloc(sizeof(tGoal));
    if (!goal) {
        return NULL;
    }
    memset(goal, 0, sizeof(tGoal));

    goal->map = map;
    goal->pos = MapGetGoalPosition(goal->map);

    goal->texture = sfTexture_createFromFile(GOAL_TILE_FILE, NULL);
    if (!goal->texture) {
        free(goal);
        return NULL;
    }

    goal->sprite = sfSprite_create();
    if (!goal->sprite) {
        sfTexture_destroy(goal->texture);
        free(goal);
        return NULL;
    }

    sfSprite_setTexture( goal->sprite, goal->texture, sfTrue);
    //sfSprite_setTextureRect(*sprite, HERO_TEXTURE_RECT(i, j));
    sfSprite_setScale(   goal->sprite, ENV_SPRITE_SCALE);
    sfSprite_setPosition(goal->sprite, _GoalGetSpritePosition(goal->pos));

    return goal;
}

int GoalDraw(hGoal goal, sfRenderWindow* renderWindow) {
    assert(goal != NULL);
    sfRenderWindow_drawSprite(renderWindow, goal->sprite, NULL);
    return 1;
}



void GoalDestroy(hGoal goal) {
    assert(goal != NULL);
    sfSprite_destroy(goal->sprite);
    sfTexture_destroy(goal->texture);
    free(goal);
    goal = NULL;
}
