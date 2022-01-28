#pragma once
#ifndef ANIMSPRITECOMPONENT_H
#define ANIMSPRITECOMPONENT_H
#include "SpriteComponent.h"
#include <vector>
class AnimSpriteComponent : public SpriteComponent
{
public:
    AnimSpriteComponent(class Actor* owner, int draw_order);
    void Update(float delta_time) override;
    void SetAnimTextures(const int tex_num, const Vec2& tex_size, const int divide, float anim_fps = 1);
    float GetAnimFPS() const { return animation_fps_; }
    void SetAnimFPS(float fps) { animation_fps_ = fps; }
    bool IsAnimEnd() const { return is_end_; }

private:
    int divide_;
    float current_frame_;
    float animation_fps_;
    bool is_end_;
};
#endif // !ANIMSPRITECOMPONENT_


