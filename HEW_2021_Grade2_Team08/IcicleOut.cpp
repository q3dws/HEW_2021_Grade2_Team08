#include "IcicleOut.h"
#include "Icicle.h"
#include "Texture.h"
IcicleOut::IcicleOut(Game* game, const Vec2& pos)
	:Actor(game)
{
	texno_ = LoadTexture(L"Data/Image/turara_out2.png");
	IcicleOut_Sprite_ = new AnimSpriteComponent(this, 130);
	IcicleOut_Sprite_->SetAnimTextures(texno_, Vec2(ICICLE_SIZE, ICICLE_SIZE), 3, 4.0f);
	SetPosition(pos);
}

void IcicleOut::UpdateActor(float deltatime)
{
	timer_++;
	SetPosition(Vec2(GetPosition().x_, GetPosition().y_));
	if (timer_ > ANIM_FRAME)
	{
		SetState(Dead);
		timer_ = 0;
	}
}
