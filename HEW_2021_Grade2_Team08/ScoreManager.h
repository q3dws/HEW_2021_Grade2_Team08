#pragma once
#include "Actor.h"
#include "Score.h"

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

    int  number;
    int  enemynumber;
    const int SCORE_MAX;
};
