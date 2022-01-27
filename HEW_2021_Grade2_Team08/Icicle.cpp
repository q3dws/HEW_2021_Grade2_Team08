#include "Icicle.h"
#include "Texture.h"
#include "SpriteComponent.h"


Icicle::Icicle(Game* game, const Vec2& destination, int index_x, int index_y, int icicle_index)
	:Actor(game)
	,fp_(new FallPoint(GetGame(), destination, icicle_index))
	,destination_(destination)
	,texno_(icicle_index)
{
	texno_ = LoadTexture(L"Data/Image/turara.png");

	SetPosition(Vec2(SNOW_POS_X + index_x * 113, 200 - SNOW_POS_Y + index_y * 75));

	Icicle_Sprite_ = new SpriteComponent(this, 120);
	Icicle_Sprite_->SetTexture(texno_, Vec2(ICICLE_SIZE, ICICLE_SIZE), Vec2(0, 0), Vec2(1, 1));

}

Icicle::~Icicle()
{
	fp_->SetState(Dead);
}

void Icicle::UpdateActor(float deltatime)
{	
	SetPosition(Vec2(GetPosition().x_, GetPosition().y_ + move_));
	if (GetPosition().y_ > destination_.y_)
	{
		ico_ = new IcicleOut(GetGame(), destination_);
		SetState(Dead);
	}
}


