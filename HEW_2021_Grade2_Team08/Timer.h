#pragma once
#include "Actor.h"
#include "Score.h"
class Timer :
    public Actor
{
public:
    Timer(Game* game,int inittime);
    ~Timer();
    void UpdateActor(float delttime)override;
    void SetTime(float deltatime);
    float GetTime();
private:
    class PlayerScore* second_;         //秒
    class PlayerScore* second_ten_;     //2桁目の秒
    class PlayerScore* minute_;         //分

    const float time_MAX_;
    const float time_vel_;      //時間の流れる速さ
    float remaining_time_;         //内部の時間
    float count_time_;          //時間を数える

};

