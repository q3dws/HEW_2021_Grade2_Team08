#pragma once
#include "Actor.h"
#include "Score.h"
#include "Fight_Effects.h"

//修正　君島朝日 1/8 scoreクラスともども現行の素材に合わせて手直し

class ScoreManager :
    public Actor
{
public:
    ScoreManager(Game* game);
    void UpdateActor(float delttime)override;
    void AddScore(int add);
    void EnemyAddScore(int add);
private:
    class PlayerScore* score1;
    class PlayerScore* score2;
    class PlayerScore* enemyscore1;
    class PlayerScore* enemyscore2;

    //class Fight_Effects* effect1;

    int  number;
    int  enemynumber;
    const int SCORE_MAX;
    const int k_fight_time_;    //試合時間

};
