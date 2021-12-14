#include "BigBullet.h"

BigBullet::BigBullet(Game* game) : Skill(game)
, k_bigsnow_vel_(10)
, k_bigsnow_tex_(LoadTexture(L"Data/Image/skill/snowball_big.png"))
, k_bigsnow_Grow(Vec2(40,40))
{
	bigsnow_size_ = Vec2(20, 20);

	bigsnow_asc_ = new SpriteComponent(this, 150);
	bigsnow_asc_->SetTexture(k_bigsnow_tex_, bigsnow_size_, Vec2(0, 0), Vec2(1, 1));
}

BigBullet::~BigBullet()
{
}

void BigBullet::UpdateActor(float delta_time)
{
	Actor::UpdateActor(delta_time);

	SetPosition(Vec2(GetPosition().x_ + k_bigsnow_vel_, GetPosition().y_));
	bigsnow_asc_->SetSize(bigsnow_size_);

	bigsnow_size_ += k_bigsnow_Grow * delta_time;

	if (GetPosition().x_ > WINDOW_WIDTH + bigsnow_size_.x_)
		SetState(Dead);
}
