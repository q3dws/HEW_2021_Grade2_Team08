#pragma once
#include "Skill.h"
#include "Actor.h"
#include "Game.h"
#include "Texture.h"
#include <vector>
#include "Stage.h"
#include "AnimSpriteComponent.h"
#include "SpriteComponent.h"

//スキル大玉のクラス
//作成者　君島朝日
// 作成日　2021/12/12
//

class BigBullet :
    public Skill
{
public:
    BigBullet(class Game* game);
    ~BigBullet();
    void UpdateActor(float delta_time) override;
private:
    class SpriteComponent* bigsnow_asc_;
    const int k_bigsnow_tex_;                       //大玉のテクスチャ
    const float k_bigsnow_vel_;                     //大玉の速さ
    const Vec2 k_bigsnow_Grow;                 //大玉の大きくなる速度
    Vec2 bigsnow_size_; //大玉の大きさ

};

