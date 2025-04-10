//
// Created by Adams Humbert on 4/1/2025.
//

#ifndef GAME_H
#define GAME_H

#include <cstdint>


enum EnemyDirection{ Right, Left};

typedef struct GameState
{

    uint16_t score = 0;
    EnemyDirection enemy_direction{Right};

} GameState;







#endif //GAME_H
