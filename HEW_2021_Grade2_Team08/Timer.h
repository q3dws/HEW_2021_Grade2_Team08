#pragma once
#include "Actor.h"
#include "Score.h"
class Timer :
    public Actor
{
public:
    Timer(Game* game,int inittime);
    void UpdateActor(float delttime)override;
    void SetTime(float deltatime);
private:
    class PlayerScore* second_;
    class PlayerScore* second_ten_;
    class PlayerScore* minute_;

    const float time_MAX_;
    const float time_vel_;      //ŽžŠÔ‚Ì—¬‚ê‚é‘¬‚³
    float remaining_time_;
    float count_time_;
};

