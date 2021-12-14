#include "Scoop.h"
#define _USE_MATH_DEFINES
#include <math.h>

Scoop::Scoop(Game* game, int layer, Vec2 pos) : Skill(game)
, k_scoop_vel_(Vec2(200,196))
, k_scoop_tex_(LoadTexture(L"Data/Image/skill/snowball_big.png"))
, k_scoop_size_(Vec2(30, 30))
,k_scoop_layer_(layer)
, k_scoop_g_(196)
,k_scoop_pos_init_(pos)
{
	scoop_pos_ = pos;
	scoop_distination_ = Vec2(pos.x_ + 312 + (k_scoop_size_.x_ / 2), pos.y_);
	scoop_asc_ = new SpriteComponent(this, 250);
	scoop_asc_->SetTexture(k_scoop_tex_, k_scoop_size_, Vec2(0, 0), Vec2(1, 1));

	//SetPosition(scoop_pos_);
}

Scoop::~Scoop()
{
}

void Scoop::UpdateActor(float delta_time)
{
	Actor::UpdateActor(delta_time);
	Scoop::Scoop_parabola(delta_time);
	Scoop::Scoop_exprosion();
}

//•ú•¨ü‰^“®‚ðì‚éŠÖ”
void Scoop::Scoop_parabola(float delta_time)
{
	float v0 = sqrtf(k_scoop_vel_.x_ * k_scoop_vel_.x_ + k_scoop_vel_.y_ * k_scoop_vel_.y_);

	float rad = asin(((scoop_distination_.x_ - scoop_pos_.x_) * k_scoop_g_ / (v0 * v0) ) ) /2;

	scoop_pos_.x_ += k_scoop_vel_.x_ * delta_time;

	float x = scoop_pos_.x_ - k_scoop_pos_init_.x_;
	float y =scoop_pos_.y_ +  -1 * 
		(x * tan(rad) - k_scoop_g_ * x * x / ((2 * v0 * 2* v0) * cos(rad) * cos(rad)));

	SetPosition(Vec2(scoop_pos_.x_, y));
}

//’…’eŽŸ‘æ”š—ô‚·‚éˆ—
void Scoop::Scoop_exprosion()
{
	if (GetPosition().x_ > scoop_distination_.x_ )
	{
		auto a = new MiniBullet(GetGame(), k_scoop_tex_, GetPosition(),true);
		auto b = new MiniBullet(GetGame(), k_scoop_tex_, GetPosition(), false);

		SetState(Dead);
	}
		
}


MiniBullet::MiniBullet(Game* game, int tex, Vec2 pos,bool up)
	:Actor(game)
	, snow_vel_(10)
{
	auto sc = new SpriteComponent(this, 150);
	sc->SetTexture(tex, Vec2(30, 30), Vec2(0, 0), Vec2(1, 1));
	up_ = up;

	SetPosition(pos);
}

MiniBullet::~MiniBullet()
{

}

void MiniBullet::UpdateActor(float deltatime)
{
	Actor::UpdateActor(deltatime);

	if (up_)
	{
		SetPosition(Vec2(GetPosition().x_, GetPosition().y_ + snow_vel_));
	}
	else
	{
		SetPosition(Vec2(GetPosition().x_, GetPosition().y_ - snow_vel_));
	}

	if (GetPosition().y_ > WINDOW_HEIGHT || GetPosition().y_ < 0)
		SetState(Dead);
}