#pragma once
#include "Actor.h"
#include "Game.h"
#include "input.h"


//�f�o�b�O�p�̃R�}���h����������N���X
class DEBUG_Comand :
    public Actor
{
private:
    bool k_Is_player_;
    int countDEBUG_;
public:
    DEBUG_Comand(class Game* game, bool Is_Player);
    void UpdateActor(float deltatime) override;

    bool CheckDEBUGmode();
};

