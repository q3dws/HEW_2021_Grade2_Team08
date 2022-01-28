#pragma once
#ifndef SCOOPLADY_H
#define SCOOPLADY_H
#include "Enemy.h"
class ScoopLady :
    public Enemy
{
public:
    ScoopLady(class Game* game, class Stage* stage);
    void UpdateActor  (float deltatime) final;
    void ChangeState  (               ) final;
    void ChangeTexture(int tex        ) final;
    void Unique       (               ) final;
public:
        enum class ANIMATION_FRAME {
        IDLE           =  8,
        ATTACK         =  8,
        MOVE_FRONT     =  1,
        MOVE_BACK      =  1,
        MOVE_UPANDDOWN =  8,
        COLLECT_IN     =  5,
        COLLECT_LOOP   =  3,
        COLLECT_OUT    =  5,
        USE_SKILL      = 13,
        HIT            =  1,
    };
private:
    const int sound;
};
#endif // !SCOOPLADY_H