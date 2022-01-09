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
    Machinegun(Game* game, bool Is_player,Vec2 pos, int bullettex, int bulletnum, int bulletdelay);
    ~Machinegun() {}
    void UpdateActor(float delta_time) override;
    float GetMachinegunTime(float delta_time);
private:
    const bool k_Is_player_;
    Vec2 machinegun_pos_;       //�e���o��ʒu
    const int k_bullettex_;                     //�e�̃e�N�X�`��
    const int k_bulletnum_;                 //�e�̐�
    const float k_machinegun_ver_;        //�e�̏o��Ԋu
    const float k_machinegun_power_;    //�e�̏o��ʂ̔{��
    const float k_bulletdelay_;                 //�e���o��O�ɑ҂A�j������
    const int k_machingun_Lowestline_;  //�ʂ�������Œ�l
    bool    delaycheck_;
    float   machinegun_counttime_;          //�e�̏o�鎞�Ԃ𐔂���
    float   machinegun_countbullet_;        //�o�����e�𐔂���
};

