#pragma once
#include "Actor.h"
#include "Score.h"

//�C���@�N������ 1/8 score�N���X�Ƃ��ǂ����s�̑f�ނɍ��킹�Ď蒼��

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
