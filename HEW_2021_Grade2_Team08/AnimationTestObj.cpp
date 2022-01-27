#include "AnimationTestObj.h"
#include "AnimSpriteComponent.h"
#include "input.h"
#include "TestBullet.h"
#include "Texture.h"
AnimationTestObj::AnimationTestObj(Game* game)
    :Actor(game)
{
    testtex = LoadTexture(L"Data/Image/TestTile.png");
    auto asc = new AnimSpriteComponent(this, 100);
    asc->SetAnimTextures(game->GetTexture(L"Data/Image/running.png"), Vec2(70, 160), 10, 5);
}

void AnimationTestObj::UpdateActor(float deltatime)
{
    Actor::UpdateActor(deltatime);
    if (GetKeyboardRelease(DIK_RETURN))
    {
        auto bullet = new TestBullet(GetGame(), testtex);
        bullet->SetPosition(GetPosition());
    }
    
	if (GetKeyboardRelease(DIK_W))
	{
		SetPosition(Vec2(GetPosition().x_, GetPosition().y_ - 120));
	}
	if (GetKeyboardRelease(DIK_S))
	{
		SetPosition(Vec2(GetPosition().x_, GetPosition().y_ + 120));
	}
	if (GetKeyboardRelease(DIK_A))
	{
		SetPosition(Vec2(GetPosition().x_ - 120, GetPosition().y_));
	}
	if (GetKeyboardRelease(DIK_D))
	{
		SetPosition(Vec2(GetPosition().x_ + 120, GetPosition().y_));
	}
}
