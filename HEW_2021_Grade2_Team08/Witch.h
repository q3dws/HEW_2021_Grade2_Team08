#pragma once
#ifndef WITCH_H
#define WITCH_H
#include "Enemy.h"
class Witch :
    public Enemy
{
public:
    Witch(class Game* game, class Stage* stage);
    void UpdateActor  (float deltatime) final;
    void ChangeState  (               ) final;
    void ChangeTexture(int tex        ) final;
    void Unique       (               ) final;
public:
    enum class ANIMATION_FRAME {
        IDLE           = 16,
        ATTACK         =  8,
        MOVE_FRONT     =  1,
        MOVE_BACK      =  1,
        MOVE_UPANDDOWN = 16,
        COLLECT_IN     =  5,
        COLLECT_LOOP   =  3,
        COLLECT_OUT    =  5,
        USE_SKILL      = 13,
        HIT            =  1,
    };
private:
    const int sound;
};
#endif // !WITCH_H