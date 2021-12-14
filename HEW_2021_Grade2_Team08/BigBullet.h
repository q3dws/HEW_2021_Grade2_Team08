#pragma once
#include "Skill.h"
#include "Actor.h"
#include "Game.h"
#include "Texture.h"
#include <vector>
#include "Stage.h"
#include "AnimSpriteComponent.h"
#include "SpriteComponent.h"

//�X�L����ʂ̃N���X
//�쐬�ҁ@�N������
// �쐬���@2021/12/12
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
    const int k_bigsnow_tex_;                       //��ʂ̃e�N�X�`��
    const float k_bigsnow_vel_;                     //��ʂ̑���
    const Vec2 k_bigsnow_Grow;                 //��ʂ̑傫���Ȃ鑬�x
    Vec2 bigsnow_size_; //��ʂ̑傫��

};

