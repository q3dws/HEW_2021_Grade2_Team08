#include "EIceWall.h"
#include "Texture.h"
#include "AnimSpriteComponent.h"
EIceWall::EIceWall(Game* game, Vec2 playerpos, int layer, int posidx) : Skill(game)
, k_wall_pos_(Vec2(55, 30))
, wall_size_(Vec2(-180, -180))
, k_wall_layer_(layer + 1)
, k_wall_cost_(2)
, k_Is_player_(false)
, k_wall_hitsize_(Vec2(90, 90))
, wall_hp_(5)
{
    SetPosIndex(posidx);
    k_wall_tex_[0] = LoadTexture(L"Data/Image/skill/icewall_in_Right.png");
    k_wall_tex_[1] = LoadTexture(L"Data/Image/skill/icewall1_Right.png");
    k_wall_tex_[2] = LoadTexture(L"Data/Image/skill/icewall_out_Right.png");
    k_wall_tex_[3] = LoadTexture(L"Data/Image/skill/icewall_hit_Right.png");

    SetPosition(Vec2(playerpos.x_ - k_wall_pos_.x_ - 5, playerpos.y_ + k_wall_pos_.y_));
    SetCollision(Rect(Vec2(playerpos.x_ - k_wall_pos_.x_ - 5, playerpos.y_ + k_wall_pos_.y_), k_wall_hitsize_));
    this->wall_asc_ = new AnimSpriteComponent(this, k_wall_layer_);
    EIceWall::IceWall_texchange(static_cast<int>(wall_Motion::ADVENT));

    hitcount_ = 0;
}

EIceWall::~EIceWall()
{
    GetGame()->RemoveEIceWall(this);
}

void EIceWall::UpdateActor(float deltatime)
{
    Actor::UpdateActor(deltatime);

    switch (wall_state_)
    {
    case static_cast<int>(wall_Motion::ADVENT):
        //ìoèÍíÜ
        motioncount_ += 5 * deltatime;
        if (motioncount_ >= static_cast<int>(wall_frame_num::ADVENT))
        {
            IceWall_texchange(static_cast<int>(wall_Motion::IDLE));
            motioncount_ = 0;
        }
        break;
    case static_cast<int>(wall_Motion::IDLE):
        //í èÌíÜ
        motioncount_ += 5 * deltatime;
        if (motioncount_ >= 85 || wall_hp_ <= 0)
        {
            IceWall_texchange(static_cast<int>(wall_Motion::LEAVE));
            motioncount_ = 0;
        }

        break;
    case static_cast<int>(wall_Motion::LEAVE):
        //ëﬁèÍíÜ
        SetCollision(Rect(Vec2(0, 0), Vec2(0, 0)));
        motioncount_ += 5 * deltatime;
        if (motioncount_ >= static_cast<int>(wall_frame_num::LEAVE))
        {
            SetState(Dead);
        }
        break;
    case static_cast<int>(wall_Motion::HIT):
        //ëﬁèÍíÜ
        hitcount_ += 5 * deltatime;
        if (hitcount_ >= static_cast<int>(wall_frame_num::HIT))
        {
            IceWall_texchange(static_cast<int>(wall_Motion::IDLE));
        }
        if (wall_hp_ <= 0)
        {
            IceWall_texchange(static_cast<int>(wall_Motion::LEAVE));
            motioncount_ = 0;
        }
        break;
    default:
        break;
    }

}

void EIceWall::IceWall_texchange(int texnum)
{
    wall_state_ = texnum;

    this->RemoveComponent(wall_asc_);
    this->GetGame()->RemoveSprite(wall_asc_);
    wall_asc_ = new AnimSpriteComponent(this, k_wall_layer_);

    if (texnum == static_cast<int>(wall_Motion::ADVENT))
    {
        wall_asc_->SetAnimTextures(k_wall_tex_[texnum], wall_size_, static_cast<int>(wall_frame_num::ADVENT), 5.f);
    }

    if (texnum == static_cast<int>(wall_Motion::IDLE))
    {
        wall_asc_->SetAnimTextures(k_wall_tex_[texnum], wall_size_, static_cast<int>(wall_frame_num::IDLE), 5.f);
        //idle_timeto_ = static_cast<int>(charaA_frame_num::ATTACK); //àÍíËéûä‘å„Ç…ë“ã@èÛë‘Ç…
    }

    if (texnum == static_cast<int>(wall_Motion::LEAVE))
    {

        wall_asc_->SetAnimTextures(k_wall_tex_[texnum], wall_size_, static_cast<int>(wall_frame_num::LEAVE), 5.f);
    }

    if (texnum == static_cast<int>(wall_Motion::HIT))
    {

        wall_asc_->SetAnimTextures(k_wall_tex_[texnum], wall_size_, static_cast<int>(wall_frame_num::HIT), 5.f);
    }
}


bool EIceWall::Get_Isplayer()
{
    return k_Is_player_;
}

//ïXÇÃï«Ç…ÉqÉbÉgÇµÇΩÇ∆Ç´Ç…åƒÇ‘ä÷êî
void EIceWall::Set_IceWallHit(int power)
{
    if (wall_state_ == static_cast<int>(wall_Motion::IDLE) || wall_state_ == static_cast<int>(wall_Motion::HIT))
    {
        hitcount_ = 0;
        wall_hp_ -= power;
        IceWall_texchange(static_cast<int>(wall_Motion::HIT));
    }
}