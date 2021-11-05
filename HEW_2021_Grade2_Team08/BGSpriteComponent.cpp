#include "BGSpriteComponent.h"
#include "Actor.h"
BGSpriteComponent::BGSpriteComponent(Actor* owner, int drawOrder)
    :SpriteComponent(owner, drawOrder)
    ,scroll_speed_(0)
{
}

void BGSpriteComponent::Update(float delta_time)
{
    SpriteComponent::Update(delta_time);
    for (auto& bg : bg_textures_)
    {
        bg.offset_.x_ += scroll_speed_ * delta_time;
        if (bg.offset_.x_ <= -screen_size_.x_)
            bg.offset_.x_ = (bg_textures_.size() - 1) * screen_size_.x_ - 1;
    }
}

void BGSpriteComponent::Draw()
{
    for (auto& bg : bg_textures_)
    {
        auto size = Vec2(screen_size_.x_, screen_size_.y_);
        auto pos = Vec2(
            owner_->GetPosition().x_ - size.x_ / 2 + bg.offset_.x_,
            owner_->GetPosition().y_ - size.y_ / 2 + bg.offset_.y_);
        DrawLeftTop(
            bg.tex_no_,
            pos,
            size,
            Vec2(0, 0),
            Vec2(1, 1));
    }
}

void BGSpriteComponent::SetBGTextures(const std::vector<int>& textures)
{
    auto count = 0;
    for (auto tex : textures)
    {
        BGTexture temp;
        temp.tex_no_ = tex;
        temp.offset_.x_ = count * screen_size_.x_;
        temp.offset_.y_ = 0;
        bg_textures_.emplace_back(temp);
        count++;
    }
}
