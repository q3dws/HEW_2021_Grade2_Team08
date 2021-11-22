#pragma once
#ifndef GAMESCENE_H
#define GAMESCENE_H
#include "State.h"
#include "Actor.h"
#include "BGSpriteComponent.h"
#include "main.h"
#include "Snow.h"
#include "Stage.h"

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
    class AnimationTestObj* obj;
    class Stage* stg;

};
#endif // !GAMESCENE_H