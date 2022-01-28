#pragma once
#include "State.h"
#include "Actor.h"
//#include "BGSpriteComponent.h"
#include "main.h"

class tutorialScene : public State<class Game>
{
public:
    tutorialScene(Game* game);
    ~tutorialScene() override;
    void Initialize(Game* game) override;
    void HandleInput(Game* game) override;
    void Update(Game* game) override;
    //void Draw(Game* game) override;

private:
    bool fadecheck_;
    class Actor* temp;
    
    class SpriteComponent* asc;

    int modecursor = 0;
    Vec2 texsize_;
    Vec2 texpos;
    float texbar;
    bool checkspece = false;
    float startalfa_;
    int BGM_ = 0;
    int SE_ = 0;
};
