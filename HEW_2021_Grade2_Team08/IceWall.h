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
   
    const int k_wall_tex_;                       //�ǂ̃e�N�X�`��
    const Vec2 k_wall_pos_;                         //���ׂ̈ʒu
    const Vec2 k_wall_size_;                      //�ǂ̑傫��
    const int k_wall_layer_;                    //�ǂ̕`��D��x

public:
    IceWall(Game* game, Vec2 playerpos, int layer);
    void UpdateActor(float deltatime) override;
   
};

