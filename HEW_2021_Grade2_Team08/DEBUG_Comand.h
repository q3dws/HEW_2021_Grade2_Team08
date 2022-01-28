#pragma once
#include "Actor.h"
#include "Game.h"
#include "input.h"


//デバッグ用のコマンドを実装するクラス
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

