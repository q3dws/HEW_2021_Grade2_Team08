#pragma once
#ifndef EICEWALL_H
#define EICEWALL_H


#include "Skill.h"
class EIceWall :
    public Skill
{
public:
    EIceWall(Game* game, Vec2 playerpos, int layer, int posidx);
    ~EIceWall();
    void UpdateActor(float deltatime) override;
    void IceWall_texchange(int texnum);
    bool Get_Isplayer();
    void Set_IceWallHit(int power);
private:
    class AnimSpriteComponent* wall_asc_;
    int wall_state_;
    float motioncount_;
    float hitcount_;

    int k_wall_tex_[4];                       //�ǂ̃e�N�X�`��
    const Vec2 k_wall_pos_;                         //���ׂ̈ʒu
    Vec2 wall_size_;                      //�ǂ̑傫��
    const Vec2 k_wall_hitsize_;
    const int k_wall_layer_;                    //�ǂ̕`��D��x
    const int k_wall_cost_;                 //�ǂ̃R�X�g
    const bool k_Is_player_;
    int wall_hp_;               //�ǂ̑ϋv��

    enum class wall_frame_num : int
    {
        ADVENT = 5,
        IDLE = 1,
        LEAVE = 8,
        HIT = 4
    };

    enum class wall_Motion :int
    {
        ADVENT,     //�o��
        IDLE,     //�ʏ�
        LEAVE,      //�ޏ�
        HIT,        //�q�b�g��
    };
};
#endif // !EICEWALL_H