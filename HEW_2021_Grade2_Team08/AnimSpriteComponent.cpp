#include "AnimSpriteComponent.h"

AnimSpriteComponent::AnimSpriteComponent(Actor* owner, int draw_order)
    :SpriteComponent(owner, draw_order)
    ,divide_(0)
    ,current_frame_(0)
{
}

void AnimSpriteComponent::Update(float delta_time)
{
    SpriteComponent::Update(delta_time);
    
    if (divide_ > 0)
    {
        current_frame_ += animation_fps_ * delta_time;
        while (current_frame_ >= divide_)
            current_frame_ -= divide_;

        float tempdiv = 1.f / divide_;
        SetUV(Vec2(0.f + (tempdiv * static_cast<int>(current_frame_)), 0.f), Vec2(tempdiv, 1.f));
    }
    
}

void AnimSpriteComponent::SetAnimTextures(const int tex_num, const Vec2& tex_size, const int divide, float anim_fps)
{
    current_frame_ = 0;
    animation_fps_ = anim_fps;
    divide_ = divide;
    SetTexture(tex_num, tex_size, Vec2(0, 0), Vec2(0, 0));
}
