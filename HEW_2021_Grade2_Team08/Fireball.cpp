#include "Fireball.h"

#define _USE_MATH_DEFINES
#include <math.h>

Fireball::Fireball(Game* game, int layer, Vec2 pos, Player* player, Stage* stg, bool Is_player) : Skill(game)
, k_fireball_tex_(LoadTexture(L"Data/Image/skill/IceWall.png"))
, k_fireball_size_(Vec2(80, 80))
, k_fireball_layer_(layer)
, k_fireball_g_(9.8)
, k_fireball_pos_init_(Vec2(pos.x_, pos.y_ + 50))
, k_fireball_deg_(60)
, k_fireball_distination_(Vec2(312 + (k_fireball_size_.x_ / 2), pos.y_))
, k_Is_player_(Is_player)

{
	fireball_pos_ = pos;
	fireball_asc_ = new SpriteComponent(this, 250);
	fireball_asc_->SetTexture(k_fireball_tex_, k_fireball_size_, Vec2(0, 0), Vec2(1, 1));

	SetPosition(k_fireball_pos_init_);

	fireball_stage_num_ = player->Player_getstagenum() + 3;

	if (k_Is_player_ == false)
	{
		k_fireball_distination_ = (Vec2(312, pos.y_));
		fireball_stage_num_ = player->Player_getstagenum() - 3;
	}

	stg_ = stg;
}

Fireball::~Fireball()
{
}

void Fireball::UpdateActor(float delta_time)
{
	Actor::UpdateActor(delta_time);
	Fireball::Fireball_parabola(delta_time);
	Fireball::Fireball_exprosion();
}

//•ú•¨ü‰^“®‚ðì‚éŠÖ”
//Žg‚¢•û@Šp“x‚Æd—Í‰Á‘¬“x‚Æ’…’e“_‚ðÝ’è‚·‚é‚ÆŽ©“®‚Å•ú•¨ü‰^“®‚ª¶¬‚³‚ê‚Ü‚·
void Fireball::Fireball_parabola(float delta_time)
{
	float rad = k_fireball_deg_ * M_PI / 180;
	float g = k_fireball_g_ / delta_time;

	float v = sqrt(g * k_fireball_distination_.x_ / (2 * sinf(rad) * cosf(rad)));
	float t = k_fireball_distination_.x_ / (v * cosf(rad));

	fireball_pos_.x_ += (k_fireball_distination_.x_ / t) * delta_time;

	float x = fireball_pos_.x_ - k_fireball_pos_init_.x_;

	float y = fireball_pos_.y_ + 50 + -1 *
		(x * tan(rad) - (g / ((2 * v * v) * cos(rad) * cos(rad)) * x * x));

	float rot = 0;
	if (k_Is_player_)
	{
		SetPosition(Vec2(fireball_pos_.x_, y));
		//ƒXƒvƒ‰ƒCƒg‚ð•ú•¨ü‚É‡‚í‚¹‚Ä‰ñ“]‚³‚¹‚é
		rot = ((double)(90 - (double)k_fireball_deg_) + (((double)k_fireball_deg_ * 2) * (x / k_fireball_distination_.x_))) * M_PI / 180;
	}
	else
	{
		SetPosition(Vec2(k_fireball_pos_init_.x_ - x, y));
		//ƒXƒvƒ‰ƒCƒg‚ð•ú•¨ü‚É‡‚í‚¹‚Ä‰ñ“]‚³‚¹‚é
		rot =-1 * ((double)(90 - (double)k_fireball_deg_) + (((double)k_fireball_deg_ * 2) * (x / k_fireball_distination_.x_))) * M_PI / 180;
	}
	fireball_asc_->SetRot(rot);
}

//’…’eŽŸ‘æ”š—ô‚·‚éˆ—
void Fireball::Fireball_exprosion()
{
	
	if (k_Is_player_)
	{
		if (GetPosition().x_ > k_fireball_pos_init_.x_ + k_fireball_distination_.x_)
		{
			stg_->SetSnow(fireball_stage_num_);
			SetState(Dead);
		}
	}
	else
	{
		if (GetPosition().x_ < k_fireball_pos_init_.x_ - k_fireball_distination_.x_)
		{
			stg_->SetSnow(fireball_stage_num_);
			SetState(Dead);
		}
	}
}

