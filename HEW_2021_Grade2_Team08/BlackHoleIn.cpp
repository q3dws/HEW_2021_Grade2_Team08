#include "BlackHoleIn.h"
#include "Texture.h"

BlackHoleIn::BlackHoleIn(Game* game)
	:Actor(game)
{
	texno_ = LoadTexture(L"Data/Image/black hole_in.png");

	BHIn_Sprite_ = new AnimSpriteComponent(this, 120);
	BHIn_Sprite_->SetAnimTextures(texno_, Vec2(BLACKHOLE_SIZE, BLACKHOLE_SIZE), 5, 1.2f);
	SetPosition(Vec2(BH_POS_X, BH_POS_Y));
}

void BlackHoleIn::UpdateActor(float deltatime)
{
}
