#pragma once
#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H
#include "Component.h"
#include <vector>
#include "Game.h"
class SpriteComponent:public Component
{
public:
    SpriteComponent(class Actor* owner, int draw_order);
    ~SpriteComponent();

    virtual void Draw();
    virtual void SetTexture(const int tex_num, const Vec2& texture_size, const Vec2& uv, const Vec2& uv_wh);
    void SetSize(const Vec2& texture_size) { texture_size_ = texture_size; }
    void SetUV(const Vec2& uv, const Vec2& uv_wh) { uv_ = uv; uv_wh_ = uv_wh; }

    void SetRot(const float rot) { rot_ = rot; }
    void SetAlfa(const float alfa) { alfa_ = alfa; }
    int GetDrawOrder() const { return draw_order_; }
    float GetAlfa() const { return alfa_; };
private:
    int texture_number_;
    Vec2 top_left_     = Vec2();
    Vec2 texture_size_ = Vec2();
    Vec2 uv_           = Vec2();
    Vec2 uv_wh_        = Vec2();
    int draw_order_;

    float current_frame_;
    float animation_fps_;

    float rot_;
    float alfa_;
};
#endif // !SPRITECOMPONENT_H