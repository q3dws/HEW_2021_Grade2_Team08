#pragma once
#include "Actor.h"

//TIMEUP�Ȃǂ̕\�����s���N���X
//�쐬�ҁ@�N������
// �쐬���@2021/1/18
//

class Fight_Effects :
    public Actor
{
private:

public:
    Fight_Effects(Game* game, int inittime);
    ~Fight_Effects();
    void UpdateActor(float delttime)override;
    void Fight_Effects_texchange(int texnum);
    void SetTime(float deltatime);
};

