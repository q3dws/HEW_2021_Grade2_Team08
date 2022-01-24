#pragma once

#include "State.h"
#include "Actor.h"
#include "BGSpriteComponent.h"
#include "main.h"

#define STAGE_HEIGHT 320
#define STAGESCREEN_X 622
#define STAGESCREEN_Y 262

class CharaselctScene : public State<class Game>
{
public:
    CharaselctScene(Game* game);
    ~CharaselctScene() override;
    void Initialize(Game* game) override;
    void HandleInput(Game* game) override;
    void Update(Game* game) override;
    //void Draw(Game* game) override;
private:
    Actor* temp;
    Actor* temp1;
    Actor* temp2;
    Actor* temp3;
    Actor* temp4;
    Actor* tempUI1;
    Actor* tempUI2;
    Actor* tempUI3;
    Actor* tempUI4;
    SpriteComponent* chara1;
    SpriteComponent* chara2;
    SpriteComponent* chara3;
    SpriteComponent* chara4;
    SpriteComponent* charaUI1;
    SpriteComponent* charaUI2;
    SpriteComponent* charaUI3;
    SpriteComponent* charaUI4;

    Actor* logo;
    SpriteComponent* logotex;
    int cursor = 0;
    Vec2 iconsize_;
    Vec2 charapos;
    float bar;
    Vec2 charaUIsize;
    Vec2 charaUIpos;

};



