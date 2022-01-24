#pragma once
#ifndef GAMESCENE_H
#define GAMESCENE_H
#include "State.h"
#include "Actor.h"
#include "BGSpriteComponent.h"
#include "main.h"
#include "Charaselect.h"

#define STAGE_HEIGHT 320
#define STAGESCREEN_X 622
#define STAGESCREEN_Y 262

class StartScene : public State<class Game>
{
public:
    StartScene(Game* game);
    ~StartScene() override;
    void Initialize(Game* game) override;
    void HandleInput(Game* game) override;
    void Update(Game* game) override;
    //void Draw(Game* game) override;

private:
    bool fadecheck_;
    Actor* temp;
    Actor* temp1;
    Actor* temp2;
    SpriteComponent* asc;

    Actor* arcade;
    SpriteComponent* arcadetex;
    Actor* vs;
    SpriteComponent* vstex;
    Actor* exit;
    SpriteComponent* exittex;
    Actor* tutorial;
    SpriteComponent* tutorialtex;

    Actor* cursor;
    SpriteComponent* cursortex;

    int modecursor = 0;
    Vec2 texsize_;
    Vec2 texpos;
    float texbar;
    bool checkspece = false;
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
    class AnimationTestObj* obj;
    class Player* player;
    class Stage* stg;
    class PlayerScore* p_playerscore;
    class PlayerScore2* p_playerscore2;
    class EnemyScore* p_enemyscore;
    int testtex;

    bool fadecheck_;
    Actor* temp;
    Actor* temp1;
    Actor* temp2;
    SpriteComponent* asc;

    Actor* arcade;
    SpriteComponent* arcadetex;
    Actor* vs;
    SpriteComponent* vstex;
    Actor* exit;
    SpriteComponent* exittex;
    Actor* tutorial;
    SpriteComponent* tutorialtex;
};


#endif // !GAMESCENE_H
