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
    class PlayerScore* second_;         //•b
    class PlayerScore* second_ten_;     //2Œ…–Ú‚Ì•b
    class PlayerScore* minute_;         //•ª

    const float time_MAX_;
    const float time_vel_;      //ŠÔ‚Ì—¬‚ê‚é‘¬‚³
    float remaining_time_;         //“à•”‚ÌŠÔ
    float count_time_;          //ŠÔ‚ğ”‚¦‚é
};

