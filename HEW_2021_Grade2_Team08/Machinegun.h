#pragma once
#include "Skill.h"
#include "Bullet.h"

//スキルマシンガンのクラス
//作成者　君島朝日
// 作成日　2021/12/19
//

class Machinegun :
    public Skill
{
public:
    Machinegun(Game* game, bool Is_player,Vec2 pos, int bullettex, int bulletnum, int bulletdelay);
    ~Machinegun() {}
    void UpdateActor(float delta_time) override;
    float GetMachinegunTime(float delta_time);
private:
    const bool k_Is_player_;
    Vec2 machinegun_pos_;       //弾が出る位置
    const int k_bullettex_;                     //弾のテクスチャ
    const int k_bulletnum_;                 //弾の数
    const float k_machinegun_ver_;        //弾の出る間隔
    const float k_machinegun_power_;    //弾の出る量の倍率
    const float k_bulletdelay_;                 //弾が出る前に待つアニメ枚数
    const int k_machingun_Lowestline_;  //玉が増える最低値
    bool    delaycheck_;
    float   machinegun_counttime_;          //弾の出る時間を数える
    float   machinegun_countbullet_;        //出した弾を数える
};

