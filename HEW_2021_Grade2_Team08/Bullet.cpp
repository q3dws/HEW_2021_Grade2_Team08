#include "Bullet.h"
#include "SpriteComponent.h"
#include "Window.h"
Bullet::Bullet(Game* game, int tex, bool Is_player)
    :Actor(game)
    , Is_player_(Is_player)
    , snow_vel_(10)
{
    auto sc = new SpriteComponent(this, 100);
    sc->SetTexture(tex, Vec2(30, 30), Vec2(0, 0), Vec2(1, 1));

}

Bullet::~Bullet()
{
    
 }

void Bullet::UpdateActor(float deltatime)
{
    Actor::UpdateActor(deltatime);

    if (Is_player_)
    {
        SetPosition(Vec2(GetPosition().x_ + snow_vel_, GetPosition().y_));
    }
    else
    {
        SetPosition(Vec2(GetPosition().x_ - snow_vel_, GetPosition().y_));
    }

   if (GetPosition().x_ > WINDOW_WIDTH)
        SetState(Dead);

   if (GetPosition().x_ < 0)
       SetState(Dead);
}