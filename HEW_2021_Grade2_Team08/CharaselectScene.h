#pragma once

#include "State.h"

//#include "BGSpriteComponent.h"
#include "main.h"

#define STAGE_HEIGHT 320
#define STAGESCREEN_X 622
#define STAGESCREEN_Y 262

class CharaselctScene : public State<class Game>
{
public:
    CharaselctScene(Game* game, int mode);
    ~CharaselctScene() override;
    void Initialize(Game* game) override;
    void HandleInput(Game* game) override;
    void Update(Game* game) override;
    //void Draw(Game* game) override;

    enum class celectCHARA :int
    {
        CHARAA,
        CHARAD,
        CHARAB, 
        CHARAC,
        EXIT,
    };
private:
    class Actor* temp;
    class Actor* temp1;
    class Actor* temp2;
    class Actor* temp3;
    class Actor* temp4;
    class Actor* tempUI1;
    class Actor* tempUI2;
    class Actor* tempUI3;
    class Actor* tempUI4;
    class SpriteComponent* chara1;
    class SpriteComponent* chara2;
    class  SpriteComponent* chara3;
    class SpriteComponent* chara4;
    class SpriteComponent* charaUI1;
    class SpriteComponent* charaUI2;
    class SpriteComponent* charaUI3;
    class SpriteComponent* charaUI4;

    class Actor* logo;
    class SpriteComponent* logotex;

    class Actor* exit_;
    class SpriteComponent* exit_asc_;
    Vec2 exitsize_;

    class Actor* p1select;
    class SpriteComponent* p1selecttex;
    class Actor* p2select;
    class SpriteComponent* p2selecttex;

    int cursor = 0;
    int cursorbuffer_ = 0;
    Vec2 iconsize_;
    Vec2 charapos;
    float bar;
    Vec2 charaUIsize;
    Vec2 charaUIpos;
    
    int mode_;
    int selectchara1_num;
    int selectchara2_num;

    int BGM_ = 0;
    int SE_[3];
    enum class SE :int
    {
        PUSH,
        CURSORMOVE,
        EXIT,
    };
};



