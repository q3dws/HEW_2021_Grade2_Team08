#include "WarningPoint.h"
#include "Texture.h"
#include "AnimSpriteComponent.h"

WarningPoint::WarningPoint(Game* game, Vec2 pos)
	:Actor(game),pos_(pos)
{
	texno_ = LoadTexture(L"Data/Image/stage_keikoku.png");

	WP_Sprite = new AnimSpriteComponent(this, 120);
	WP_Sprite->SetAnimTextures(texno_, Vec2(FALLPOINT_SIZE, FALLPOINT_SIZE), 4, 5);
	SetPosition(pos);

}

void WarningPoint::UpdateActor(float deltatime)
{
	
}
