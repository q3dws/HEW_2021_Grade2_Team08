#include "Scoop.h"
#define _USE_MATH_DEFINES
#include <math.h>

Scoop::Scoop(Game* game, int layer, Vec2 pos, bool Is_player) : Skill(game)
, k_scoop_tex_(LoadTexture(L"Data/Image/skill/snowball_big.png"))
, k_scoop_size_(Vec2(30, 30))
,k_scoop_layer_(layer)
, k_scoop_g_(9.8)
,k_scoop_pos_init_(Vec2(pos.x_, pos.y_ + 50))
, k_scoop_deg_(60)
, k_scoop_distination_(Vec2(312 + (k_scoop_size_.x_ / 2), pos.y_))
,k_Is_player_(Is_player)
{
	scoop_pos_ = pos;
	scoop_asc_ = new SpriteComponent(this, 250);
	scoop_asc_->SetTexture(k_scoop_tex_, k_scoop_size_, Vec2(0, 0), Vec2(1, 1));
	
	if (k_Is_player_ == false)
	{
		k_scoop_distination_ = (Vec2(312 , pos.y_));
	}

	SetPosition(k_scoop_pos_init_);
	
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
	//Žg‚¢•û@Šp“x‚Æd—Í‰Á‘¬“x‚Æ’…’e“_‚ðÝ’è‚·‚é‚ÆŽ©“®‚Å•ú•¨ü‰^“®‚ª¶¬‚³‚ê‚Ü‚·

	float rad = k_scoop_deg_ * M_PI / 180;
	float g = k_scoop_g_ / delta_time;

	float v = sqrt(g * k_scoop_distination_.x_ / (2 * sinf(rad) * cosf(rad)));
	float t = k_scoop_distination_.x_ / (v * cosf(rad));

	scoop_pos_.x_ += (k_scoop_distination_.x_ / t) * delta_time;

	float x = scoop_pos_.x_ - k_scoop_pos_init_.x_;

	float y = scoop_pos_.y_ + 50 + -1 *
		(x * tan(rad) - (g / ((2 * v * v) * cos(rad) * cos(rad)) * x * x));

	if (k_Is_player_ )
	{		
		SetPosition(Vec2(scoop_pos_.x_, y));
	}
	else
	{
		SetPosition(Vec2(k_scoop_pos_init_.x_ - x, y));
	}
}

//’…’eŽŸ‘æ”š—ô‚·‚éˆ—
void Scoop::Scoop_exprosion()
{
	if (k_Is_player_)
	{
		if (GetPosition().x_ > k_scoop_pos_init_.x_ + k_scoop_distination_.x_)
		{
			auto a = new MiniBullet(GetGame(), k_scoop_tex_, GetPosition(), true);
			auto b = new MiniBullet(GetGame(), k_scoop_tex_, GetPosition(), false);

			SetState(Dead);
		}
	}
	else
	{
		if (GetPosition().x_ < k_scoop_pos_init_.x_ - k_scoop_distination_.x_)
		{
			auto a = new MiniBullet(GetGame(), k_scoop_tex_, GetPosition(), true);
			auto b = new MiniBullet(GetGame(), k_scoop_tex_, GetPosition(), false);

			SetState(Dead);
		}
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