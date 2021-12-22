#include "Machinegun.h"

Machinegun::Machinegun(Game* game, bool Is_player, Vec2 pos, int bullettex, int bulletnum) : Skill(game)
,k_bulletnum_(bulletnum)
,k_Is_player_(Is_player)
,k_machinegun_pos_(pos)
,k_bullettex_(bullettex)
,k_machinegun_ver_(1)
{
	machinegun_counttime_ = 0;
	machinegun_countbullet_ = 0;
}

void Machinegun::UpdateActor(float delta_time)
{
	Actor::UpdateActor(delta_time);

	machinegun_counttime_ += 5 * delta_time;

	if (machinegun_counttime_ >= k_machinegun_ver_)
	{
		auto a = new Bullet(GetGame(),k_bullettex_,k_Is_player_);
		a->SetPosition(k_machinegun_pos_);
		machinegun_counttime_ = 0;
		machinegun_countbullet_++;
	}

	if (machinegun_countbullet_ >= k_bulletnum_)
	{
		SetState(Dead);
	}
}
