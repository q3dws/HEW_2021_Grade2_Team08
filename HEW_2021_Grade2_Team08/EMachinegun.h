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
    Vec2        machinegun_pos_;       //弾が出る位置
    const int   k_bullettex_;                     //弾のテクスチャ
    const int   k_bulletnum_;                 //弾の数
    const float k_machinegun_ver_;        //弾の出る間隔
    const float k_machinegun_power_;    //弾の出る量の倍率
    const int   k_machingun_Lowestline_;  //玉が増える最低値
    float       machinegun_counttime_;          //弾の出る時間を数える
    float       machinegun_countbullet_;        //出した弾を数える
    bool        mg_out_;
    const int sounds_[3];
};
#endif // !EMACHINGUN_H