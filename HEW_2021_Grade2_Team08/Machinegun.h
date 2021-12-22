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
    Machinegun(Game* game, bool Is_player,Vec2 pos, int bullettex, int bulletnum);
    ~Machinegun() {}
    void UpdateActor(float delta_time) override;

private:
    const bool k_Is_player_;
    const Vec2 k_machinegun_pos_;       //弾が出る位置
    const int k_bullettex_;                     //弾のテクスチャ
    const int k_bulletnum_;                 //弾の数
    const float k_machinegun_ver_;        //弾の出る間隔

    float   machinegun_counttime_;          //弾の出る時間を数える
    float   machinegun_countbullet_;        //出した弾を数える
};

