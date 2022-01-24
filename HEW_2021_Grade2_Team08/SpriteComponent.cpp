#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"
#include "Texture.h"
#include "sprite.h"
SpriteComponent::SpriteComponent(Actor* owner, int draw_order)
    :Component(owner, draw_order)
    , draw_order_(draw_order)
    , texture_size_(Vec2())
    , current_frame_(0.f)
    , animation_fps_(60.f)
    , rot_(0)
    , alfa_(1.0f)
{
    owner_->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
    owner_->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Draw()
{

    /*DrawCenter(
        texture_number_,
        owner_->GetPosition(),
        texture_size_ * owner_->GetScale(),
        uv_,
        uv_wh_);*/

    DrawSpriteRotCntr(
        texture_number_,
        owner_->GetPosition(),
        texture_size_ * owner_->GetScale(),
        uv_,
        uv_wh_,
        rot_,
        alfa_
    );

}

void SpriteComponent::SetTexture(const int tex_num, const Vec2& texture_size, const Vec2& uv, const Vec2& uv_wh)
{
    texture_number_ = tex_num;
    texture_size_ = texture_size;
    uv_ = uv;
    uv_wh_ = uv_wh;

}

float SpriteComponent::GetAlfa()
{
    return alfa_;
}
