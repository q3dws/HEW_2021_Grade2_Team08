#pragma once
#include "State.h"
#include "Actor.h"
//#include "BGSpriteComponent.h"
#include "main.h"

#define STAGE_HEIGHT 300
#define STAGESCREEN_X 622
#define STAGESCREEN_Y 262

class ResultScene :
    public State<class Game>
{
public:
    ResultScene(Game* game, int score,int enemyscore, int mode, int player1, int player2);
    ~ResultScene() override;
    void Initialize(Game* game) override;
    void HandleInput(Game* game) override;
    void Update(Game* game) override;
    //void Draw(Game* game) override;


    
private:
    class Actor* temp;
   
    class Fight_Effects* waku_;
    class Fight_Effects* youwinlogo_;
    class Fight_Effects* scorelogo_;

    class PlayerScore* digit_;         //‚Ð‚Æ‚¯‚½‚ß
    class PlayerScore* second_digit_;     //‚Ó‚½‚¯‚½‚ß
    class PlayerScore* third_digit_;         //san‚¯‚½‚ß

    int cursor = 0;
    int cursorbuffer_ = 0;
    Vec2 iconsize_;
    Vec2 charapos;
    float bar;
    Vec2 charaUIsize;
    Vec2 charaUIpos;

    Vec2 exitsize_;
    int mode_ = 0;
    int p1_ = 0;
    int p2_ = 0;
    bool win_;

    int score_;

    int SE_[3];
    enum class SE :int
    {
        WIN,
        CLEAR,
        LOSE,
    };
};


