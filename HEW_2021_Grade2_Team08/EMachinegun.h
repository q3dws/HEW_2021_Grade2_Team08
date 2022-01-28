#pragma once
#ifndef EMACHINGUN_H
#define EMACHINEGUN_H
#include "Skill.h"
class EMachinegun :
    public Skill
{
public:
    EMachinegun(Game* game, Vec2 pos, int bullettex, int bulletnum);
    ~EMachinegun() {}
    void UpdateActor(float delta_time) override;
    bool Is_MGEnd();
private:
    const bool  k_Is_player_;
    Vec2        machinegun_pos_;       //’e‚ªo‚éˆÊ’u
    const int   k_bullettex_;                     //’e‚ÌƒeƒNƒXƒ`ƒƒ
    const int   k_bulletnum_;                 //’e‚Ì”
    const float k_machinegun_ver_;        //’e‚Ìo‚éŠÔŠu
    const float k_machinegun_power_;    //’e‚Ìo‚é—Ê‚Ì”{—¦
    const int   k_machingun_Lowestline_;  //‹Ê‚ª‘‚¦‚éÅ’á’l
    float       machinegun_counttime_;          //’e‚Ìo‚éŠÔ‚ğ”‚¦‚é
    float       machinegun_countbullet_;        //o‚µ‚½’e‚ğ”‚¦‚é
    bool        mg_out_;
    const int sounds_[3];
};
#endif // !EMACHINGUN_H