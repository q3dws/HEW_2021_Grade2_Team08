#pragma once
#ifndef PLAYER_H
#define PLAYER_H
/*
    �쐬�ҁ@�N������
    �쐬�� 2021/11/07
*/


#include "Actor.h"
#include "Game.h"
#include "Texture.h"
#include <vector>
#include "Stage.h"
#include "AnimSpriteComponent.h"
#include "SpriteComponent.h"

#include "Skillicon.h"
#include "SnowCost.h"
#include "SnowCost_tate.h"
#include "DEBUG_Comand.h"

//#define  ECSC static_cast<int> //enum class static cast�̗�

class Bullet;
class Golem;

class Player : public Actor
{
protected: 
    Vec2 player_pos_;          //�v���C���[�̉�ʏ�̍��W
    int player_snow_;                     //�v���C���[�̌��ݎ����Ă����
    int     player_pos_num_;                    //�v���C���[�̂���}�X�̔ԍ�
    /*
    012
    345 ���ꂼ��̐������}�X�̔ԍ��ɑΉ�
    678
    */
    //class Stage* pstage;
  
    int bullettex_;                              //�e�̃e�N�X�`��
    std::vector<class Bullet*> bullets_; //�e�̃I�u�W�F�N�g����铮�I�z��
    
    std::vector<class Golem*> golems_; //�S�[�����̃I�u�W�F�N�g����铮�I�z��
    class SnowCost* snowcost_;                        //�����Ă����̐���\������I�u�W�F�N�g�����
    class SnowCost_tate* snowcost_tate_;
    class Skillicon* skillicon_;                        //�X�L����UI��\������I�u�W�F�N�g�����
    class DEBUG_Comand* debugcomand_;

    class AnimSpriteComponent* asc_;    
    int     player_mode_;                          //�v���C���[�̃X�e�[�g(Player�����Ŋ��������)
    float idlecount_;                                //�ҋ@��Ԃɓ���܂ł̃^�C�}�[
    float     idle_timeto_;                           //timeto�܂Ő�����Ƒҋ@��ԂɂȂ�

    int     player_layer_;                           //�v���C���[�̕`��̗D��x
    const int k_player_layer_var;           //�v���C���[�̕`��̗D��x�̕ω���

    const int k_player_snow_max_;     //�v���C���[�̎��Ă��̏��
    const int k_player_snow_min_ ;     //�v���C���[�̎��Ă��̉���

    Vec2 k_player_pos_center_;      //9�}�X�̐^�񒆂̍��W
    const Vec2 k_player_pos_var_;          //�{�^�����������Ƃ��̃v���C���[�̈ړ��ʁ@
    const Vec2 k_player_vel_;          //�v���C���[�̈ړ����x
    Vec2 k_player_size_;                      //�v���C���[�L�����̑傫��

    const int k_player_skillcost_[4];   //���ʃX�L���̃R�X�g
    const int k_who_player_;            //�v���C���[�̎�ނ�����
    const bool k_Is_player_;                //true�Ȃ�v���C���[�� false �Ȃ�G��

    enum class WHO_Player : int
    {
        CHARAA,
        CHARAB,
        CHARAC,
        CHARAD,
    };
    //�L�����̉摜�̔ԍ����X�e�[�g�𓯎��ɕ\���񋓌^
    enum class PlayerMotion :int
    {
        IDLE,                   //�ҋ@
        ATTACK,             //�U��
        MOVE_FRONT,     //�O�ړ�
        MOVE_BACK,      //���ړ�
        MOVE_UPANDDOWN,     //�㉺�ړ� 

        COLLECT_IN,     //��W�ߊJ�n
        COLLECT_LOOP,   //��W�ߒ�
        COLLECT_OUT,       //��W�ߏI��
        USE_SKILL,          //�X�L���g�p��

        USE_SKILL_IN,       //�X�L���J�n
        USE_SKILL_LOOP, //�X�L����
        USE_SKILL_OUT,  //�X�L���I��
    };

    StateContext<Player>* pplayer_state_context_;
    Stage* stg_;

    
public:

    Player(class Game* game, Stage* stg ,Vec2 size, Vec2 center,int uniquecost, bool Is_player, int who);
    virtual ~Player();
    void UpdateActor(float deltatime) override;

    void Player_move(float deltatime);
    void Player_snow_collect();
    void Player_snow_throw(float deltatime);
    void Player_idlecheck(float deltatime);
    void Player_useskill(void);
    int Player_getstagenum(void);
    int Player_getsnow(void);
    virtual void Player_UniqueSkill(void) = 0;
    virtual void Player_texchange(int texnum) = 0;
    //void Player_Draw(int mode);
};
#endif // PLAYER_H

