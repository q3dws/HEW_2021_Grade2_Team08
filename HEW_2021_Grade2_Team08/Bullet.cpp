#include "Bullet.h"
#include "SpriteComponent.h"
#include "Window.h"
#include "Player.h"
#include "IceWall.h"
#include "Armor.h"
#include "Golem.h"
#include "Enemy.h"
#include "EArmor.h"
#include "EGolem.h"
#include "EIceWall.h"

Bullet::Bullet(Game* game, int tex, bool Is_player, Vec2 pos)
    :Actor(game)
    , Is_player_(Is_player)
    , snow_vel_(10)
    , snow_pos_(pos)
    , snow_size_(Vec2(30, 30))
    , k_damagetime_(2)
    , motioncount_(0)
    , bullet_state_(static_cast<int>(bullet_Motion::IDLE))
    , k_bullet_tex_{
        LoadTexture(L"Data/Image/snowball.png")
        ,LoadTexture(L"Data/Image/Eff_Iceball_Sheet.png")
        
}
{
    /*auto sc = new SpriteComponent(this, 100);
    sc->SetTexture(tex, snow_size_, Vec2(0, 0), Vec2(1, 1));*/
    bullet_asc_ = new AnimSpriteComponent(this, 100);
    bullet_asc_->SetAnimTextures(k_bullet_tex_[static_cast<int>(bullet_Motion::IDLE)], snow_size_, static_cast<int>(bullet_frame_num::IDLE), 5.f);

    SetPosition(snow_pos_);

    SetCollision(Rect(snow_pos_, snow_size_));
}

Bullet::~Bullet()
{
    
 }

void Bullet::UpdateActor(float deltatime)
{
    Actor::UpdateActor(deltatime);

    Bullet::Bullet_ColligionCheck(deltatime);

    if (bullet_state_ == static_cast<int>(bullet_Motion::LEAVE))
    {
        motioncount_ += 5 * deltatime;
        if (motioncount_ >= static_cast<int>(bullet_frame_num::LEAVE))
        {
            SetState(Dead);
        }
    }
    
}

//当たり判定を見て死ぬ関数
void Bullet::Bullet_ColligionCheck(float delta_taime)
{
    //氷の壁との当たり判定
    if (GetGame()->GetIceWallSize() != 0)
    {
        for (int i = 0; i < GetGame()->GetIceWallSize(); i++)
        {
            if (CollisionRC_NoInd(GetGame()->GetIceWall(i), this) && bullet_state_ == static_cast<int>(bullet_Motion::IDLE))
            {
                if (GetGame()->GetIceWall(i)->Get_Isplayer() != Is_player_)
                {
                    Bullet_texchange(static_cast<int>(bullet_Motion::LEAVE));
                    GetGame()->GetIceWall(i)->Set_IceWallHit(1);
                    //SetState(Dead);
                }
            }
        }
    }
    for (int i = 0; i < GetGame()->GetEIceWalls().size(); ++i)
    {
        if (GetGame()->GetEIceWalls().at(i))
        {
            if (GetGame()->GetEIceWalls().at(i)->Get_Isplayer() != Is_player_)
            {
                if (CollisionRC_NoInd(GetGame()->GetEIceWalls().at(i), this) && bullet_state_ == static_cast<int>(bullet_Motion::IDLE))
                {
                    Bullet_texchange(static_cast<int>(bullet_Motion::LEAVE));
                    GetGame()->GetEIceWalls().at(i)->Set_IceWallHit(1);
                }
            }
        }
    }

    //アーマーとの当たり判定
    if (GetGame()->GetArmorSize() != 0)
    {
        for (int i = 0; i < GetGame()->GetArmorSize(); i++)
        {
            if (CollisionRC_NoInd(GetGame()->GetArmor(i), this) && bullet_state_ == static_cast<int>(bullet_Motion::IDLE))
            {
                if (GetGame()->GetArmor(i)->Get_Isplayer() != Is_player_)
                {
                    Bullet_texchange(static_cast<int>(bullet_Motion::LEAVE));
                    GetGame()->GetArmor(i)->Set_Armorhit(1);
                    //SetState(Dead);
                }
            }
        }
    }
    for (int i = 0; i < GetGame()->GetEArmor().size(); ++i)
    {
        if (GetGame()->GetEArmor().at(i))
        {
            if (GetGame()->GetEArmor().at(i)->Get_Isplayer() != Is_player_)
            {
                if (CollisionRC_NoInd(GetGame()->GetEArmor().at(i), this) && bullet_state_ == static_cast<int>(bullet_Motion::IDLE))
                {
                    Bullet_texchange(static_cast<int>(bullet_Motion::LEAVE));
                    GetGame()->GetEArmor().at(i)->Set_Armorhit(1);
                }
            }
        }
    }


    //ゴーレムとの当たり判定
    if (GetGame()->GetGolemSize() != 0)
    {
        for (int i = 0; i < GetGame()->GetGolemSize(); i++)
        {
            if (CollisionRC_NoInd(GetGame()->GetGolem(i), this) && bullet_state_ == static_cast<int>(bullet_Motion::IDLE))
            {
                if (GetGame()->GetGolem(i)->Get_Isplayer() != Is_player_)
                {
                    Bullet_texchange(static_cast<int>(bullet_Motion::LEAVE));
                    GetGame()->GetGolem(i)->Set_Golemhit(1);
                    //SetState(Dead);
                }
            }
        }
    }
    for (int i = 0; i < GetGame()->GetEGolems().size(); ++i)
    {
        if (GetGame()->GetEGolems().at(i))
        {
            if (GetGame()->GetEGolems().at(i)->Get_Isplayer() != Is_player_)
            {
                if (CollisionRC_NoInd(GetGame()->GetEGolems().at(i), this) && bullet_state_ == static_cast<int>(bullet_Motion::IDLE))
                {
                    GetGame()->GetEGolems().at(i)->Set_Golemhit(1);
                    Bullet_texchange(static_cast<int>(bullet_Motion::LEAVE));
                }
            }
        }
    }

    if (Is_player_)//プレイヤー側の弾
    {
        
        if (bullet_state_ == static_cast<int>(bullet_Motion::IDLE))
        {
            SetPosition(Vec2(GetPosition().x_ + snow_vel_, GetPosition().y_));
            MoveCollison(Vec2(snow_vel_, 0));

        }

        //敵にヒットしたときの処理
        if(GetGame()->GetPlayer2p())
        if (CollisionRC_NoInd(GetGame()->GetPlayer2p(), this) && bullet_state_ == static_cast<int>(bullet_Motion::IDLE))
        {
            Bullet_texchange(static_cast<int>(bullet_Motion::LEAVE));
            GetGame()->GetPlayer2p()->Player_SetHit(k_damagetime_);

            GetGame()->GetScoreManager()->AddScore(1);

            //SetState(Dead);
        }
        if (GetGame()->GetEnemy())
        {
            if (CollisionRC_NoInd(GetGame()->GetEnemy(), this) && bullet_state_ == static_cast<int>(bullet_Motion::IDLE))
            {
                Bullet_texchange(static_cast<int>(bullet_Motion::LEAVE));
                //GetGame()->GetEnemy()->Player_SetHit(k_damagetime_);

                GetGame()->GetScoreManager()->AddScore(1);
            }
        }

    }
    else
    {
        
        if (bullet_state_ == static_cast<int>(bullet_Motion::IDLE))
        {
            SetPosition(Vec2(GetPosition().x_ - snow_vel_, GetPosition().y_));
            MoveCollison(Vec2(-snow_vel_, 0));

        }

        //プレイヤー1にヒットしたときの処理
        if (CollisionRC_NoInd(GetGame()->GetPlayer(), this) && bullet_state_ == static_cast<int>(bullet_Motion::IDLE))
        {
            Bullet_texchange(static_cast<int>(bullet_Motion::LEAVE));
            GetGame()->GetPlayer()->Player_SetHit(k_damagetime_);

            GetGame()->GetScoreManager()->EnemyAddScore(1);

            //SetState(Dead);
          
        }
    }


    if (GetPosition().x_ > WINDOW_WIDTH)
        SetState(Dead);

    if (GetPosition().x_ < 0)
        SetState(Dead);
}

void Bullet::Bullet_texchange(int texnum)
{
    bullet_state_ = texnum;

    this->RemoveComponent(bullet_asc_);
    this->GetGame()->RemoveSprite(bullet_asc_);
    bullet_asc_ = new AnimSpriteComponent(this, 100);

    if (texnum == static_cast<int>(bullet_Motion::LEAVE))
    {
        bullet_asc_->SetAnimTextures(k_bullet_tex_[texnum], snow_size_, static_cast<int>(bullet_frame_num::LEAVE), 5.f);
    }

}
