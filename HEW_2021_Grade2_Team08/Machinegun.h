#pragma once
#include "Skill.h"
#include "Bullet.h"

//�X�L���}�V���K���̃N���X
//�쐬�ҁ@�N������
// �쐬���@2021/12/19
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
    const Vec2 k_machinegun_pos_;       //�e���o��ʒu
    const int k_bullettex_;                     //�e�̃e�N�X�`��
    const int k_bulletnum_;                 //�e�̐�
    const float k_machinegun_ver_;        //�e�̏o��Ԋu

    float   machinegun_counttime_;          //�e�̏o�鎞�Ԃ𐔂���
    float   machinegun_countbullet_;        //�o�����e�𐔂���
};

