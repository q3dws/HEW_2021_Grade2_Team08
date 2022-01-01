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

    int k_wall_tex_[3];                       //�ǂ̃e�N�X�`��
    const Vec2 k_wall_pos_;                         //���ׂ̈ʒu
    Vec2 wall_size_;                      //�ǂ̑傫��
    const int k_wall_layer_;                    //�ǂ̕`��D��x
    const int k_wall_cost_;                 //�ǂ̃R�X�g

    enum class wall_frame_num : int
    {
        ADVENT = 5,
        IDLE = 1,
        LEAVE = 8,
    };

    enum class wall_Motion :int
    {
        ADVENT,     //�o��
        IDLE,     //�ʏ�
        LEAVE,      //�ޏ�
    };

public:
    IceWall(Game* game, Vec2 playerpos, int layer, bool Is_player);
    void UpdateActor(float deltatime) override;
    void IceWall_texchange(int texnum);
};

