#include "Bullet.h"
#include "SpriteComponent.h"
#include "Window.h"
Bullet::Bullet(Game* game, int tex)
    :Actor(game)
    , death_timer(0.2f)
    , snow_vel_(10)
{
    auto sc = new SpriteComponent(this, 150);
    sc->SetTexture(tex, Vec2(30, 30), Vec2(0, 0), Vec2(1, 1));

}

Bullet::~Bullet()
{
    
 }

void Bullet::UpdateActor(float deltatime)
{
    Actor::UpdateActor(deltatime);

    SetPosition(Vec2(GetPosition().x_ + snow_vel_, GetPosition().y_));
   if (GetPosition().x_ > WINDOW_WIDTH)
        SetState(Dead);
}