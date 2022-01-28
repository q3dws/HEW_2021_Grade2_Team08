#pragma once
#ifndef ROBOT_H_
#define ROBOT_H_
#include "Enemy.h"
class Robot :
    public Enemy
{
public:
    Robot(class Game* game, class Stage* stage);
    void UpdateActor(float deltatime) final;
    void ChangeState() final;
    void ChangeTexture(int tex) final;
    void Unique() final;
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
        USE_SKILL_IN   =  6,
        USE_SKILL_LOOP =  2,
        USE_SKILL_OUT  =  6
    };
private:
    int bulletnum_                 ;
    class EMachinegun* emachinegun_;
    const int sound;
};
#endif // !ROBOT_H_