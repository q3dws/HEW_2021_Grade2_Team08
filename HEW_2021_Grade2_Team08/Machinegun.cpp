#include "Machinegun.h"

Machinegun::Machinegun(Game* game, bool Is_player, Vec2 pos, int bullettex, int bulletnum, int bulletdelay) : Skill(game)
,k_bulletnum_(bulletnum)
,k_Is_player_(Is_player)
,machinegun_pos_(pos)
,k_bullettex_(bullettex)
, k_bulletdelay_(bulletdelay)
,k_machinegun_ver_(0.9)
, k_machinegun_power_(1.0)
, k_machingun_Lowestline_(4)
{
	if (k_Is_player_)
	{
		machinegun_pos_ = (Vec2(pos.x_ + 70, pos.y_ + 40));
	}
	else
	{
		machinegun_pos_ = (Vec2(pos.x_ - 70, pos.y_ + 40));
	}

	machinegun_counttime_ = 0;
	machinegun_countbullet_ = 0;

	delaycheck_ = false;
}

void Machinegun::UpdateActor(float delta_time)
{
	Actor::UpdateActor(delta_time);

	//’e‚Ìo‚é‚Ü‚Å‚ÌŠÔ‘Ò‚Â
	machinegun_counttime_ += 5 * delta_time;

	if (machinegun_counttime_ >= k_bulletdelay_)
	{
		delaycheck_ = true;
	}

	//’e‚ğ“™ŠÔŠu‚Å”­Ë‚·‚é
	if (machinegun_counttime_ >= k_machinegun_ver_ && delaycheck_)
	{
		auto a = new Bullet(GetGame(),k_bullettex_,k_Is_player_, machinegun_pos_);
		
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

//ƒ}ƒVƒ“ƒKƒ“Œ‚‚ÂŠÔ‚ğ‹‚ß‚éŠÖ”
float Machinegun::GetMachinegunTime(float delta_time)
{
	return k_bulletnum_ * k_machinegun_power_ * (k_machinegun_ver_ + 0.1);
}
