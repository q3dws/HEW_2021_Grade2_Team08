#pragma once
#include "State.h"
#include "Actor.h"
//#include "BGSpriteComponent.h"
#include "main.h"

#define STAGE_HEIGHT 300
#define STAGESCREEN_X 622
#define STAGESCREEN_Y 262

class VSResultScene :
    public State<class Game>
{
public:
    VSResultScene(Game* game, int p1score, int p2score);
    ~VSResultScene() override;
    void Initialize(Game* game) override;
    void HandleInput(Game* game) override;
    void Update(Game* game) override;
    //void Draw(Game* game) override;



private:
    class Actor* temp;

    class Fight_Effects* youwinlogo_;
    class Fight_Effects* scorelogo_;

    class PlayerScore* digit_;         //‚Ð‚Æ‚¯‚½‚ß
    class PlayerScore* second_digit_;     //‚Ó‚½‚¯‚½‚ß
    class PlayerScore* third_digit_;         //san‚¯‚½‚ß

    class Fight_Effects* p2youwinlogo_;
    class Fight_Effects* p2scorelogo_;

    class Fight_Effects* waku1_;
    class Fight_Effects* waku2_;

    class PlayerScore* p2digit_;         //‚Ð‚Æ‚¯‚½‚ß
    class PlayerScore* p2second_digit_;     //‚Ó‚½‚¯‚½‚ß
    class PlayerScore* p2third_digit_;         //san‚¯‚½‚ß

    int cursor = 0;
    int cursorbuffer_ = 0;
    Vec2 iconsize_;
    Vec2 charapos;
    float bar;
    Vec2 charaUIsize;
    Vec2 charaUIpos;

    Vec2 exitsize_;
    int p1score_ = 0;
    int p2score_ = 0;
    int p1_ = 0;
    int p2_ = 0;

    int SE_[3];
    enum class SE :int
    {
        WIN,
        CLEAR,
        LOSE,
    };
};



