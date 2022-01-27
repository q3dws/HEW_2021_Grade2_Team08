#pragma once
#ifndef GAMESCENE_H
#define GAMESCENE_H
#include "State.h"
#include "Actor.h"
#include "BGSpriteComponent.h"
#include "main.h"

class StartScene : public State<class Game>
{
public:
    StartScene(Game* game);
    ~StartScene() override;
    void Initialize(Game* game) override;
    void HandleInput(Game* game) override;
    void Update(Game* game) override;
    //void Draw(Game* game) override;

    Actor* temp;
};

class BattleScene : public State<class Game>
{
public:
    BattleScene(Game* game);
    ~BattleScene() override;
    void Initialize(Game* game) override;
    void HandleInput(Game* game) override;
    void Update(Game* game) override;
    //void Draw(Game* game) override;
private:
    class Player* player;
    class FirstStage* stg;
    class Score* p_score;
    class Score2* p_score2;
    int testtex;
};

class SecondBattleScene : public State<class Game>
{
public:
    SecondBattleScene(Game* game);
    ~SecondBattleScene() override;
    void Initialize(Game* game) override;
    void HandleInput(Game* game) override;
    void Update(Game* game) override;
    //void Draw(Game* game) override;

private:
    class Player* player;
    class SecondStage* stg2;
    class Score* p_score;
    class Score2* p_score2;
    int testtex;

};

class ThirdBattleScene : public State<class Game>
{
public:
    ThirdBattleScene(Game* game);
    ~ThirdBattleScene() override;
    void Initialize(Game* game) override;
    void HandleInput(Game* game) override;
    void Update(Game* game) override;
    //void Draw(Game* game) override;

private:
    class Player* player;
    class ThirdStage* stg3;
    class Score* p_score;
    class Score2* p_score2;
    int testtex;

};
#endif // !GAMESCENE_H