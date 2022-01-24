#pragma once
#include "Skill.h"
#include "Game.h"
#include "Texture.h"
#include <vector>
#include "Stage.h"
#include "AnimSpriteComponent.h"
#include "SpriteComponent.h"

class IceWall :
    public Skill
{
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

    const int k_wall_SE_[3];
    
    enum class wall_SE_num :int
    {
        ADVENT,     //�o��
        LEAVE,      //�ޏ�
        HIT,     //��e��
    };

public:
    IceWall(Game* game, Vec2 playerpos, int layer, bool Is_player);
    ~IceWall();
    void UpdateActor(float deltatime) override;
    void IceWall_texchange(int texnum);
    bool Get_Isplayer();
    void Set_IceWallHit(int power);
};

