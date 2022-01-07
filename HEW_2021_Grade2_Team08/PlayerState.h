#pragma once
#ifndef PLAYERSTATE_H
#include "State.h"
#include "Player.h"

//�v���C���[�ҋ@���
class PlayerIdle :
    public State<class Player>
{
public:
    PlayerIdle(Player* player);
    ~PlayerIdle() override;
    void Initialize(Player* player) override;
    void HandleInput(Player* player) override;
    void Update(Player* player) override;
    //void Draw(Game* game) override;

    //Actor* temp;
};

#endif // !PLAYERSTATE_H


