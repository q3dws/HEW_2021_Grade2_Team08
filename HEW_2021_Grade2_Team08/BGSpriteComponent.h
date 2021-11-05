#pragma once
#ifndef BGSPRITECOMPONENT_H
#define BGSPRITECOMPONENT_H
#include "SpriteComponent.h"
#include "sprite.h"

class BGSpriteComponent : public SpriteComponent
{
public:
    BGSpriteComponent(class Actor* owner, int drawOrder);

    void Update(float delta_time) override;
    void Draw() override;

    void SetBGTextures(const std::vector<int>& textures);
    void SetScreenSize(const Vec2& size) { screen_size_ = size; }
    void SetScrollSpeed(float speed) { scroll_speed_ = speed; }

    float GetScrollSpeed() const { return scroll_speed_; }
private:
    struct BGTexture
    {
        int tex_no_;
        Vec2 offset_;
    };
    std::vector<BGTexture> bg_textures_;
    Vec2 screen_size_ = Vec2();
    float scroll_speed_;
};
#endif // !BSSPRITECOMPONENT_H