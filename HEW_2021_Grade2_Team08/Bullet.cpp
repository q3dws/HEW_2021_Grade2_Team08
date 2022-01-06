#include "Bullet.h"
#include "SpriteComponent.h"
#include "Window.h"
#include "Player.h"
#include "IceWall.h"

Bullet::Bullet(Game* game, int tex, bool Is_player, Vec2 pos)
    :Actor(game)
    , Is_player_(Is_player)
    , snow_vel_(10)
    , snow_pos_(pos)
{
    auto sc = new SpriteComponent(this, 100);
    sc->SetTexture(tex, Vec2(30, 30), Vec2(0, 0), Vec2(1, 1));

    SetPosition(snow_pos_);

    SetCollision(Rect(snow_pos_, Vec2(30, 30)));
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
        MoveCollison(Vec2(snow_vel_, 0));

        if (CollisionRC_NoInd(GetGame()->GetPlayer2p(), this))
        {
            GetGame()->GetPlayer2p()->Player_SetHit();
            SetState(Dead);
        }
           
    }
    else
    {
        SetPosition(Vec2(GetPosition().x_ - snow_vel_, GetPosition().y_));
        MoveCollison(Vec2(-snow_vel_, 0));

        if (CollisionRC_NoInd(GetGame()->GetPlayer(), this))
        {
            GetGame()->GetPlayer()->Player_SetHit();
            SetState(Dead);
        }
    }

    if (GetGame()->GetIceWallSize() != 0)
    {
        for (int i = 0; i < GetGame()->GetIceWallSize(); i++)
        {
            if (CollisionRC_NoInd(GetGame()->GetIceWall(i), this) && this->GetState() == 0)
            {
                if (GetGame()->GetIceWall(i)->Get_Isplayer() != Is_player_)
                {
                    GetGame()->GetIceWall(i)->Set_IceWallHit();
                    SetState(Dead);
                }         
            }     
        }
    }

   if (GetPosition().x_ > WINDOW_WIDTH)
        SetState(Dead);

   if (GetPosition().x_ < 0)
       SetState(Dead);
}