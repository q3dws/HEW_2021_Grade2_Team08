#include "FallPoint.h"
#include "Texture.h"
#include "SpriteComponent.h"
#include "AnimSpriteComponent.h"

FallPoint::FallPoint(Game* game, int ptexno)
	:Actor(game),texno_(ptexno)
{
	texno_ = LoadTexture(L"Data/Image/stage_keikoku.png");

	auto afp = new AnimSpriteComponent(this, 120);
	afp->SetAnimTextures(texno_, Vec2(FALLPOINT_SIZE, FALLPOINT_SIZE), 4, 5);
}

void FallPoint::UpdateActor(float deltatime)
{
	SetPosition(Vec2(GetPosition().x_, GetPosition().y_));
}
