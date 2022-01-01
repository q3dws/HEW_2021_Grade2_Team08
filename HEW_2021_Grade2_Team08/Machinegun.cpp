#include "Machinegun.h"

Machinegun::Machinegun(Game* game, bool Is_player, Vec2 pos, int bullettex, int bulletnum, int bulletdelay) : Skill(game)
,k_bulletnum_(bulletnum)
,k_Is_player_(Is_player)
,k_machinegun_pos_(Vec2(pos.x_ + 70, pos.y_ + 40))
,k_bullettex_(bullettex)
, k_bulletdelay_(bulletdelay)
,k_machinegun_ver_(0.9)
, k_machinegun_power_(1.5)
, k_machingun_Lowestline_(4)
{
	machinegun_counttime_ = 0;
	machinegun_countbullet_ = 0;

	delaycheck_ = false;
}

void Machinegun::UpdateActor(float delta_time)
{
	Actor::UpdateActor(delta_time);

	machinegun_counttime_ += 5 * delta_time;

	if (machinegun_counttime_ >= k_bulletdelay_)
	{
		delaycheck_ = true;
	}

	if (machinegun_counttime_ >= k_machinegun_ver_ && delaycheck_)
	{
		auto a = new Bullet(GetGame(),k_bullettex_,k_Is_player_);
		a->SetPosition(k_machinegun_pos_);
		machinegun_counttime_ = 0;
		machinegun_countbullet_++;
	}

	if (k_bulletnum_ > k_machingun_Lowestline_)
	{
		if (machinegun_countbullet_ >= k_bulletnum_ * k_machinegun_power_)
		{
			SetState(Dead);
		}
	}
	else
	{
		if (machinegun_countbullet_ >= k_bulletnum_ )
		{
			SetState(Dead);
		}
	}
}

float Machinegun::GetMachinegunTime(float delta_time)
{
	return k_bulletnum_ * k_machinegun_power_ * (k_machinegun_ver_ + 0.1);
}
