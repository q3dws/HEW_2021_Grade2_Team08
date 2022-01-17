#pragma once
#include "Skill.h"
#include "Actor.h"
#include "Game.h"
#include "Texture.h"
#include <vector>
#include "Stage.h"
#include "AnimSpriteComponent.h"
#include "SpriteComponent.h"

class Golem :
    public Skill
{
private:
    class AnimSpriteComponent* golem_asc_;
    int     golem_state_;            //�S�[�����̏��
    float     attackcount_;                //�S�[�����̍U������܂ł̎��Ԃ𐔂���    
    float     motioncount_;             //�S�[�����̓o��/�ޏ�A�j���̏I��鎞�Ԃ𐔂���
    int     deathcount;            //�������ʂ̐��𐔂���

    int golem_tex_[3];                       //�S�[�����̃e�N�X�`��
    const Vec2 k_golem_pos_;                         //�S�[�����̈ʒu
    Vec2 k_golem_size_;                      //�S�[�����̑傫��
    const int k_golem_layer;                    //�S�[�����̕`��̗D��x
    const int k_bullettex_;                         //�e�̃e�N�X�`��
    const bool  k_Is_player_;                   //�v���C���[�����ǂ����̕ϐ�
    std::vector<class Bullet*> bullets_; //�e�̃I�u�W�F�N�g����铮�I�z��
    int golem_hp_;                          //�S�[�����̑ϋv�l

    enum class golem_frame_num : int
    {
        ADVENT = 17,
        ATTACK = 14,
        LEAVE = 8,
    };

    enum class golem_Motion :int
    {
        ADVENT,     //�o��
        ATTACK,     //�U����
        LEAVE,      //�ޏ�
    };


public:
    Golem(Game* game, Vec2(pos), int bullettex, int layer, bool Is_player_);
    ~Golem();
    void UpdateActor(float deltatime) override;
    void Golem_snow_throw(float deltatime);
    void Golem_death_check(float deltatime);
    void Golem_texchange(int texnum) ;
    void Set_Golemhit(int power);
    bool Get_Isplayer();
};

