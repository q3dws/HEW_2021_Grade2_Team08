#include "EMachinegun.h"
#include "Bullet.h"
#include "sound.h"

EMachinegun::EMachinegun(Game* game, Vec2 pos, int bullettex, int bulletnum):
    Skill                   (game       ),
    k_Is_player_            (false      ),
    machinegun_pos_         (pos        ),
    k_bullettex_            (bullettex  ),
    k_bulletnum_            (bulletnum  ),
    k_machinegun_ver_       (0.9        ),
    k_machinegun_power_     (1.5        ),
    k_machingun_Lowestline_ (4          ),
    machinegun_counttime_   (           ),
	machinegun_countbullet_ (           ),
    mg_out_                 (           ),
    sounds_{
        LoadSound(L"Data/SE/Skill/machingun_init.wav"),
        LoadSound(L"Data/SE/Skill/machingun_bullet.wav"),
        LoadSound(L"Data/SE/Skill/machingun_end.wav")
    }
{
    PlaySound(sounds_[0], 0);
}

void EMachinegun::UpdateActor(float delta_time)
{
    machinegun_counttime_ += 5 * delta_time;
    //’e‚ð“™ŠÔŠu‚Å”­ŽË‚·‚é
    if (machinegun_counttime_ >= k_machinegun_ver_)
    {
        PlaySound(sounds_[1], 0);
        auto a = new Bullet(GetGame(), k_bullettex_, k_Is_player_, machinegun_pos_);

        machinegun_counttime_ = 0;
        machinegun_countbullet_++;
    }

    if (k_bulletnum_ > k_machingun_Lowestline_)
    {
        if (machinegun_countbullet_ >= k_bulletnum_ * k_machinegun_power_)
        {
            SetState(Dead);
            mg_out_ = true;
        }
    }
    else
    {
        if (machinegun_countbullet_ >= k_bulletnum_)
        {
            SetState(Dead);
            mg_out_ = true;
        }
    }
}

bool EMachinegun::Is_MGEnd()
{
    return mg_out_;
}
