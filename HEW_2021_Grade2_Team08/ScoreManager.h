#pragma once
#include "Actor.h"
#include "Score.h"
#include "Fight_Effects.h"

//�C���@�N������ 1/8 score�N���X�Ƃ��ǂ����s�̑f�ނɍ��킹�Ď蒼��

class ScoreManager :
    public Actor
{
public:
    ScoreManager(Game* game);
    ~ScoreManager();
    void UpdateActor(float delttime)override;
    void AddScore(int add);
    void EnemyAddScore(int add);
    bool GetTimeUP();
    int GetPlayerScore();
    int GetEnemyScore();
private:
    class PlayerScore* score1;
    class PlayerScore* score2;
    class PlayerScore* enemyscore1;
    class PlayerScore* enemyscore2;

    class Actor* temp1;
    class Actor* temp2;
    class Actor* temp3;
    class Timer* timer;

    //class Fight_Effects* effect1;

    bool timeupcheck;
    bool gameendflag;

    float timespare_;

    int  number;
    int  enemynumber;
    const int SCORE_MAX;
    const int k_fight_time_;    //��������

};
