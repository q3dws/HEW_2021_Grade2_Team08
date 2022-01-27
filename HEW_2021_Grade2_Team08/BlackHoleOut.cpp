#include "BlackHoleOut.h"
#include "Texture.h"

BlackHoleOut::BlackHoleOut(Game* game)
	:Actor(game),timer_(0)
{
	texno_ = LoadTexture(L"Data/Image/black hole_out.png");

	BHOut_Sprite_ = new AnimSpriteComponent(this, 120);
	BHOut_Sprite_->SetAnimTextures(texno_, Vec2(BLACKHOLE_SIZE, BLACKHOLE_SIZE), 5, 1.2f);
	SetPosition(Vec2(BH_POS_X, BH_POS_Y));
}

void BlackHoleOut::UpdateActor(float deltatime)
{
	timer_++;

	if (timer_ > 60)
		SetState(Dead);
}
