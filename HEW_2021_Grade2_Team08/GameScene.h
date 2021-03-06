#pragma once
#ifndef GAMESCENE_H
#define GAMESCENE_H
#include "State.h"
#include "Actor.h"
//#include "BGSpriteComponent.h"
#include "main.h"

#define STAGE_HEIGHT 300
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

    int modecursor = 0;
    Vec2 texsize_;
    Vec2 texpos;
    float texbar;
    bool checkspece = false;
    float startalfa_;
    int BGM_ = 0;
    int SE_ = 0;
};

class BattleScene : public State<class Game>
{
public:
    BattleScene(Game* game,int mode, int player1, int player2, int score);
    ~BattleScene() override;
    void Initialize(Game* game) override;
    void HandleInput(Game* game) override;
    void Update(Game* game) override;
    //void Draw(Game* game) override;

    void Setplayer(Game* game, int playernum, bool isplayer);
    class Enemy* RetEnemy();
    enum ECHARACTERNUMBER {
        SCOOPLADY,
        ROBOT,
        PONYTAIL,
        WITCH
    };
private:
    class AnimationTestObj* obj;
    class Player* player;
    class Player* player2;
    class Enemy* enemy_;
    
    
    class Stage* stg;
    class Game* game_;
    class ScoreManager* p_ScoreManager;
    int testtex;
    int mode_ = 0;
    int player1_num_;
    int BGM_ = 0;
    int inhertscore_ = 0;
};
#endif // !GAMESCENE_H