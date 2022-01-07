#pragma once
#ifndef g_EnemySTATE_H
#include "State.h"
#include "Enemy.h"

//プレイヤー待機状態
class EnemyIdle :
    public State<class Enemy>
{
public:
    EnemyIdle(Enemy* enemy);
    ~EnemyIdle() override;
    void Initialize(Enemy* enemy) override;
    void HandleInput(Enemy* enemy) override;
    void Update(Enemy* enemy) override;
    //void Draw(Game* game) override;

    //Actor* temp;
};

#endif // !g_EnemySTATE_H

