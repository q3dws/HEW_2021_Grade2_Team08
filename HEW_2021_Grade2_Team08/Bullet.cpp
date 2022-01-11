#include "Bullet.h"
#include "SpriteComponent.h"
#include "Window.h"
#include "Player.h"
#include "IceWall.h"
#include "Armor.h"
#include "Golem.h"

Bullet::Bullet(Game* game, int tex, bool Is_player, Vec2 pos)
    :Actor(game)
    , Is_player_(Is_player)
    , snow_vel_(10)
    , snow_pos_(pos)
    , k_damagetime_(2)
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

    Bullet::Bullet_ColligionCheck(deltatime);

}

//当たり判定を見て死ぬ関数
void Bullet::Bullet_ColligionCheck(float delta_taime)
{
    //氷の壁との当たり判定
    if (GetGame()->GetIceWallSize() != 0)
    {
        for (int i = 0; i < GetGame()->GetIceWallSize(); i++)
        {
            if (CollisionRC_NoInd(GetGame()->GetIceWall(i), this) && this->GetState() == 0)
            {
                if (GetGame()->GetIceWall(i)->Get_Isplayer() != Is_player_)
                {
                    GetGame()->GetIceWall(i)->Set_IceWallHit(1);
                    SetState(Dead);
                }
            }
        }
    }

    //アーマーとの当たり判定
    if (GetGame()->GetArmorSize() != 0)
    {
        for (int i = 0; i < GetGame()->GetArmorSize(); i++)
        {
            if (CollisionRC_NoInd(GetGame()->GetArmor(i), this) && this->GetState() == 0)
            {
                if (GetGame()->GetArmor(i)->Get_Isplayer() != Is_player_)
                {
                    GetGame()->GetArmor(i)->Set_Armorhit(1);
                    SetState(Dead);
                }
            }
        }
    }


    //ゴーレムとの当たり判定
    if (GetGame()->GetGolemSize() != 0)
    {
        for (int i = 0; i < GetGame()->GetGolemSize(); i++)
        {
            if (CollisionRC_NoInd(GetGame()->GetGolem(i), this) && this->GetState() == 0)
            {
                if (GetGame()->GetGolem(i)->Get_Isplayer() != Is_player_)
                {
                    GetGame()->GetGolem(i)->Set_Golemhit(1);
                    SetState(Dead);
                }
            }
        }
    }

    if (Is_player_)//プレイヤー側の弾
    {
        SetPosition(Vec2(GetPosition().x_ + snow_vel_, GetPosition().y_));
        MoveCollison(Vec2(snow_vel_, 0));

        //敵にヒットしたときの処理
        if (CollisionRC_NoInd(GetGame()->GetPlayer2p(), this) && this->GetState() == 0)
        {
            GetGame()->GetPlayer2p()->Player_SetHit(k_damagetime_);

            GetGame()->GetScoreManager()->AddScore(1);

            SetState(Dead);
        }

    }
    else
    {
        SetPosition(Vec2(GetPosition().x_ - snow_vel_, GetPosition().y_));
        MoveCollison(Vec2(-snow_vel_, 0));

        //プレイヤー1にヒットしたときの処理
        if (CollisionRC_NoInd(GetGame()->GetPlayer(), this) && this->GetState() == 0)
        {
            GetGame()->GetPlayer()->Player_SetHit(k_damagetime_);

            GetGame()->GetScoreManager()->EnemyAddScore(1);

            SetState(Dead);
          
        }
    }


    if (GetPosition().x_ > WINDOW_WIDTH)
        SetState(Dead);

    if (GetPosition().x_ < 0)
        SetState(Dead);
}
