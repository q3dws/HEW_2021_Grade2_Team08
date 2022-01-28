#pragma once
#include "Actor.h"

#define BLACKHOLE_SIZE  200
#define BASEUSETIME		20
#define BH_POS_X		480
#define BH_POS_Y		120

class THEBH :
    public Actor
{
private:
    class AnimSpriteComponent* BH_asc_;
    int BH_state_;
    float motioncount_;
    float hitcount_;

    int k_BH_tex_[4];                       //�ǂ̃e�N�X�`��
    const Vec2 k_BH_pos_;                         //���ׂ̈ʒu
    Vec2 BH_size_;                      //�ǂ̑傫��
    const Vec2 k_BH_hitsize_;
    const int k_BH_layer_;                    //�ǂ̕`��D��x
    const int k_BH_cost_;                 //�ǂ̃R�X�g
    
    int BH_hp_;               //�ǂ̑ϋv��

    enum class BH_frame_num : int
    {
        ADVENT = 5,
        IDLE = 8,
        LEAVE = 5,
        HIT = 4
    };

    enum class BH_Motion :int
    {
        ADVENT,     //�o��
        IDLE,     //�ʏ�
        LEAVE,      //�ޏ�
        HIT,        //�q�b�g��
    };

    const int k_BH_SE_[3];

    enum class BH_SE_num :int
    {
        ADVENT,     //�o��
        LEAVE,      //�ޏ�
        HIT,     //��e��
    };

public:
    THEBH(Game* game, int layer);
    ~THEBH();
    void UpdateActor(float deltatime) override;
    void THEBH_texchange(int texnum);
  
    void Set_THEBHHit(int power);
};

