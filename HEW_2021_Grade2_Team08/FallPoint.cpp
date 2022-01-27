#include "FallPoint.h"
#include "Texture.h"
#include "SpriteComponent.h"
#include "AnimSpriteComponent.h"

FallPoint::FallPoint(Game* game, const Vec2& pos, int ptexno)
	:Actor(game),texno_(ptexno)
{
	texno_ = LoadTexture(L"Data/Image/stage_keikoku.png");
	SetPosition(pos);
	FallPoint_Sprite_ = new AnimSpriteComponent(this, 120);
	FallPoint_Sprite_->SetAnimTextures(texno_, Vec2(FALLPOINT_SIZE, FALLPOINT_SIZE), 4, 5);
}

void FallPoint::UpdateActor(float deltatime)
{
}
