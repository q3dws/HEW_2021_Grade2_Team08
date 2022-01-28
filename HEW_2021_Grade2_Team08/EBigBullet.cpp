#include "EBigBullet.h"
#include "Game.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include "Window.h"
#include "Texture.h"
#include "Golem.h"
#include "Armor.h"
#include "IceWall.h"
#include "Math.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "sound.h"
#include "Enemy.h"
#include "EArmor.h"
#include "EIceWall.h"
#include "EGolem.h"

EBigBullet::EBigBullet(Game* game, Vec2 pos, int layer):
    Skill(game)                                                      ,
    k_bigsnow_vel_(10)                                               ,
    k_bigsnow_tex_(LoadTexture(L"Data/Image/skill/snowball_big.png")),
    k_bigsnow_Grow(Vec2(40, 40))                                     ,
    k_bigsnow_Growrot_(180)                                          ,
    k_Is_player_(false)                                              ,
    k_bigsnow_layer_(layer + 1)                                      ,
    bigsnow_pos_(pos)                                                ,
    sounds_{
        LoadSound(L"Data/SE/Skill/bigsnow_init.wav"),
        LoadSound(L"Data/SE/Skill/bigsnow_hit.wav")
    }
{
    bigsnow_size_ = Vec2(20, 20);

    bigsnow_asc_ = new SpriteComponent(this, k_bigsnow_layer_);
    bigsnow_asc_->SetTexture(k_bigsnow_tex_, bigsnow_size_, Vec2(0, 0), Vec2(1, 1));

    SetPosition(bigsnow_pos_);

    SetCollision(Rect(bigsnow_pos_, bigsnow_size_));
    bigsnow_rot_ = 0;
    bigsnow_power_ = 1;
    bigsnow_distance_count_ = 0;

    PlaySound(sounds_[0], 0);
}

EBigBullet::~EBigBullet()
{
    int test = 0;
}

void EBigBullet::UpdateActor(float delta_time)
{
    Actor::UpdateActor(delta_time);
    EBigBullet::BigBullet_move(delta_time);

    //移動距離に応じて威力アップ
    bigsnow_distance_count_ += k_bigsnow_Growrot_ * delta_time;
    if (bigsnow_distance_count_ >= 100)
    {
        bigsnow_power_++;
        bigsnow_distance_count_ = 0;
    }


    if (GetPosition().x_ > WINDOW_WIDTH + bigsnow_size_.x_)
        SetState(Dead);

    if (GetPosition().x_ < 0 - bigsnow_size_.x_)
        SetState(Dead);

    //氷の壁との当たり判定
    if (GetGame()->GetIceWallSize() != 0)
    {
        for (int i = 0; i < GetGame()->GetIceWallSize(); i++)
        {
            if (CollisionRC_NoInd(GetGame()->GetIceWall(i), this) && this->GetState() == 0)
            {
                if (GetGame()->GetIceWall(i)->Get_Isplayer() != k_Is_player_)
                {
                    //位置の関係で1ダメージ足りなくなるので増やしています
                    if (bigsnow_power_ >= 2)
                        GetGame()->GetIceWall(i)->Set_IceWallHit(bigsnow_power_ + 1);
                    else
                        GetGame()->GetIceWall(i)->Set_IceWallHit(bigsnow_power_ + 1);

                    SetState(Dead);
                }
            }
        }
    }
    for (int i = 0; i < GetGame()->GetEIceWalls().size(); ++i)
    {
        if (GetGame()->GetEIceWalls().at(i))
        {
            if (GetGame()->GetEIceWalls().at(i)->Get_Isplayer() != k_Is_player_)
            {
                if (CollisionRC_NoInd(GetGame()->GetEIceWalls().at(i), this) && this->GetState() == 0)
                {
                    GetGame()->GetEIceWalls().at(i)->Set_IceWallHit(bigsnow_power_ + 1);
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
                if (GetGame()->GetArmor(i)->Get_Isplayer() != k_Is_player_)
                {
                    GetGame()->GetArmor(i)->Set_Armorhit(bigsnow_power_);
                    SetState(Dead);
                }
            }
        }
    }
    for (int i = 0; i < GetGame()->GetEArmor().size(); ++i)
    {
        if (GetGame()->GetEArmor().at(i))
        {
            if (GetGame()->GetEArmor().at(i)->Get_Isplayer() != k_Is_player_)
            {
                if (CollisionRC_NoInd(GetGame()->GetEArmor().at(i), this) && this->GetState() == 0)
                {
                    GetGame()->GetEArmor().at(i)->Set_Armorhit(bigsnow_power_);
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
                if (GetGame()->GetGolem(i)->Get_Isplayer() != k_Is_player_)
                {
                    GetGame()->GetGolem(i)->Set_Golemhit(bigsnow_power_);
                    SetState(Dead);
                }
            }
        }
    }
    for (int i = 0; i < GetGame()->GetEGolems().size(); ++i)
    {
        if (GetGame()->GetEGolems().at(i))
        {
            if (GetGame()->GetEGolems().at(i)->Get_Isplayer() != k_Is_player_)
            {
                if (CollisionRC_NoInd(GetGame()->GetEGolems().at(i), this) && this->GetState() == 0)
                {
                    GetGame()->GetEGolems().at(i)->Set_Golemhit(bigsnow_power_);
                    SetState(Dead);
                }
            }
        }
    }


    if (k_Is_player_)//プレイヤー側の弾
    {
        //敵にヒットしたときの処理
        if(GetGame()->GetPlayer2p())
        if (CollisionRC_NoInd(GetGame()->GetPlayer2p(), this) && this->GetState() == 0)
        {
            GetGame()->GetPlayer2p()->Player_SetHit(bigsnow_power_ * 2);

            GetGame()->GetScoreManager()->AddScore(bigsnow_power_);

            SetState(Dead);
        }
        if (GetGame()->GetEnemy())
        {
            if (CollisionRC_NoInd(GetGame()->GetEnemy(), this) && this->GetState() == 0)
            {
                GetGame()->GetScoreManager()->AddScore(bigsnow_power_);

                SetState(Dead);
            }
        }
    }
    else
    {
        //プレイヤー1にヒットしたときの処理
        if (CollisionRC_NoInd(GetGame()->GetPlayer(), this) && this->GetState() == 0)
        {
            GetGame()->GetPlayer()->Player_SetHit(bigsnow_power_ * 2);

            GetGame()->GetScoreManager()->EnemyAddScore(bigsnow_power_);

            SetState(Dead);
        }
    }
}

void EBigBullet::BigBullet_move(float delta_time)
{
    bigsnow_size_ += k_bigsnow_Grow * delta_time;

    bigsnow_asc_->SetSize(bigsnow_size_);

    if (k_Is_player_)
    {
        SetPosition(Vec2(GetPosition().x_ + k_bigsnow_vel_, GetPosition().y_));
        bigsnow_rot_ += k_bigsnow_Growrot_ * delta_time;

        //当たり判定移動
        MoveCollison(Vec2(k_bigsnow_vel_, 0));
    }
    else
    {
        SetPosition(Vec2(GetPosition().x_ - k_bigsnow_vel_, GetPosition().y_));
        bigsnow_rot_ -= k_bigsnow_Growrot_ * delta_time;

        //当たり判定移動
        MoveCollison(Vec2(-k_bigsnow_vel_, 0));
    }
    bigsnow_asc_->SetRot(bigsnow_rot_ * M_PI / 180);


}
