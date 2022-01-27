#pragma once
#include "State.h"
#include "Actor.h"
//#include "BGSpriteComponent.h"
#include "main.h"

#define STAGE_HEIGHT 300
#define STAGESCREEN_X 622
#define STAGESCREEN_Y 262

class ModeselectScene :
    public State<class Game>
{
public:
    ModeselectScene(Game* game);
    ~ModeselectScene() override;
    void Initialize(Game* game) override;
    void HandleInput(Game* game) override;
    void Update(Game* game) override;
    //void Draw(Game* game) override;


    enum class celectMODE :int
    {
        ARCADE,
        VERSUS,
        TUTORIAL,
        EXIT,

        STAGE1,
        STAGE2,
        STAGE3,
    };
private:
    class Actor* temp;
    class Actor* arcade_;
    class Actor* versus_;
    class Actor* tutrial_;
    class Actor* exit_;
    class Actor* tempUI1;
    
    class SpriteComponent* arcade_asc_;
    class SpriteComponent* versus_asc_;
    class  SpriteComponent* tutrial_asc_;
    class SpriteComponent* exit_asc_;
    class SpriteComponent* charaUI1;
   
    class Actor* logo;
    class SpriteComponent* logotex;
    int cursor = 0;
    int cursorbuffer_ = 0;
    Vec2 iconsize_;
    Vec2 charapos;
    float bar;
    Vec2 charaUIsize;
    Vec2 charaUIpos;

    Vec2 exitsize_;
   
    int BGM_ = 0;

    int SE_[3];
    enum class SE :int
    {
        PUSH,
        CURSORMOVE,
        EXIT,
    };
};


