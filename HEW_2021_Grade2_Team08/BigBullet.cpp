#include "BigBullet.h"

BigBullet::BigBullet(Game* game, bool Is_player, int layer) : Skill(game)
, k_bigsnow_vel_(10)
, k_bigsnow_tex_(LoadTexture(L"Data/Image/skill/snowball_big.png"))
, k_bigsnow_Grow(Vec2(40,40))
,k_bigsnow_Growrot_(180)
,k_Is_player_(Is_player)
,k_bigsnow_layer_(layer + 1)
{
	bigsnow_size_ = Vec2(20, 20);

	bigsnow_asc_ = new SpriteComponent(this, k_bigsnow_layer_);
	bigsnow_asc_->SetTexture(k_bigsnow_tex_, bigsnow_size_, Vec2(0, 0), Vec2(1, 1));

	bigsnow_rot_ = 0;
}

BigBullet::~BigBullet()
{
}

void BigBullet::UpdateActor(float delta_time)
{
	Actor::UpdateActor(delta_time);

	bigsnow_size_ += k_bigsnow_Grow * delta_time;

	
	bigsnow_asc_->SetSize(bigsnow_size_);

	if (k_Is_player_)
	{
		SetPosition(Vec2(GetPosition().x_ + k_bigsnow_vel_, GetPosition().y_));
		bigsnow_rot_ += k_bigsnow_Growrot_ * delta_time;
		bigsnow_asc_->SetRot(bigsnow_rot_ * 3.14 / 180);
	}
	else
	{
		SetPosition(Vec2(GetPosition().x_ - k_bigsnow_vel_, GetPosition().y_));
		bigsnow_rot_ -= k_bigsnow_Growrot_ * delta_time;
		bigsnow_asc_->SetRot(bigsnow_rot_ * 3.14 / 180);
	}
	
	if (GetPosition().x_ > WINDOW_WIDTH + bigsnow_size_.x_)
		SetState(Dead);

	if (GetPosition().x_ < 0 - bigsnow_size_.x_)
		SetState(Dead);

	

}
