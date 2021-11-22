#include "AnimationTestObj.h"
#include "AnimSpriteComponent.h"
#include "input.h"
#include "TestBullet.h"

AnimationTestObj::AnimationTestObj(Game* game)
    :Actor(game)
{
    auto asc = new AnimSpriteComponent(this, 100);
    asc->SetAnimTextures(game->GetTexture(L"Data/Image/running.png"), Vec2(70, 160), 10, 5.f);
}

void AnimationTestObj::UpdateActor(float deltatime)
{
    Actor::UpdateActor(deltatime);
    
}
