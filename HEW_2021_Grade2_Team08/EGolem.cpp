#include "EGolem.h"
#include "Bullet.h"
#include "AnimSpriteComponent.h"
#include "Texture.h"
#include "sound.h"
//#include "Player.h"

EGolem::EGolem(Game* game, Vec2 pos, int bullettex, int layer, int posidx) : Skill(game)
, k_golem_pos_(Vec2(pos))
, k_golem_size_(Vec2(-64 * 2, -64 * 2))
, k_bullettex_(bullettex)
, k_golem_layer(layer - 1)
, k_Is_player_(false)
, golem_hp_(2)
, sounds_{
    LoadSound(L"Data/SE/Skill/golem_init.wav"),
    LoadSound(L"Data/SE/Skill/golem_throw.wav"),
    LoadSound(L"Data/SE/Skill/golem_death.wav"),
    LoadSound(L"Data/SE/Skill/golem_hit.wav")
}
{
    SetPosIndex(posidx);
    golem_tex_[0] = LoadTexture(L"Data/Image/skill/golem_up_Sheet.png");
    golem_tex_[1] = LoadTexture(L"Data/Image/skill/golem_throw_Sheet.png");
    golem_tex_[2] = LoadTexture(L"Data/Image/skill/golem_down_Sheet.png");

    this->attackcount_ = static_cast<int>(golem_frame_num::ATTACK) - 10;	//投げるコマまでの調整
    this->motioncount_ = 0;
    this->golem_state_ = static_cast<int>(golem_Motion::ADVENT);

    this->SetPosition(k_golem_pos_);
    this->golem_asc_ = new AnimSpriteComponent(this, k_golem_layer);
    EGolem::Golem_texchange(static_cast<int>(golem_Motion::ADVENT));

    PlaySound(sounds_[0], 0);
    //SetCollision(Rect(k_golem_pos_ - Vec2(0,20), Vec2(64 * 2, 64 * 2) - Vec2(64, 82)));
}

EGolem::~EGolem()
{
    GetGame()->RemoveEGolem(this);
}

void EGolem::UpdateActor(float deltatime)
{
    Actor::UpdateActor(deltatime);

    EGolem::Golem_snow_throw(deltatime);
    EGolem::Golem_death_check(deltatime);

}

//ゴーレムが雪玉を投げる処理
void EGolem::Golem_snow_throw(float deltatime)
{
    if (golem_state_ == static_cast<int>(golem_Motion::ATTACK))
    {
        attackcount_ += 5 * deltatime;
        //攻撃するコマになったら射撃する
        if (attackcount_ >= static_cast<int>(golem_frame_num::ATTACK))
        {
            //弾を生成
            bullets_.emplace_back(new Bullet(GetGame(), k_bullettex_, k_Is_player_, k_golem_pos_));

            attackcount_ = 0;
            PlaySound(sounds_[1], 0);

            //弾を四回投げていると死亡する
            deathcount++;
            if (deathcount > 4)
                Golem_texchange(static_cast<int>(golem_Motion::LEAVE));
        }
    }
    else if (golem_state_ == static_cast<int>(golem_Motion::ADVENT))
    {
        //登場中の場合はアニメが終わるのを待ってから攻撃状態に移る処理
        motioncount_ += 5 * deltatime;
        if (motioncount_ >= static_cast<int>(golem_frame_num::ADVENT))
        {

            Golem_texchange(static_cast<int>(golem_Motion::ATTACK));
            motioncount_ = 0;
        }
    }

}

//ゴーレムのテクスチャを切り替える処理
void EGolem::Golem_texchange(int texnum)
{
    golem_state_ = texnum;

    this->RemoveComponent(golem_asc_);
    this->GetGame()->RemoveSprite(golem_asc_);
    golem_asc_ = new AnimSpriteComponent(this, k_golem_layer);

    if (texnum == static_cast<int>(golem_Motion::ADVENT))
    {
        golem_asc_->SetAnimTextures(golem_tex_[texnum], k_golem_size_, static_cast<int>(golem_frame_num::ADVENT), 5.f);
    }

    if (texnum == static_cast<int>(golem_Motion::ATTACK))
    {
        //当たり判定登場
        SetCollision(Rect(k_golem_pos_ + Vec2(0, 20), Vec2(64 * 2, 64 * 2) - Vec2(64, 82)));

        golem_asc_->SetAnimTextures(golem_tex_[texnum], k_golem_size_, static_cast<int>(golem_frame_num::ATTACK), 5.f);
        //idle_timeto_ = static_cast<int>(charaA_frame_num::ATTACK); //一定時間後に待機状態に
    }

    if (texnum == static_cast<int>(golem_Motion::LEAVE))
    {
        //当たり判定tai場
        SetCollision(Rect(Vec2(0, 0) + Vec2(0, 20), Vec2(64 * 2, 64 * 2) - Vec2(64, 82)));
        PlaySound(sounds_[2], 0);
        golem_asc_->SetAnimTextures(golem_tex_[texnum], k_golem_size_, static_cast<int>(golem_frame_num::LEAVE), 5.f);
    }

}


//ゴーレムの退場アニメが終わったら消え失せる処理
void EGolem::Golem_death_check(float deltatime)
{
    if (golem_state_ == static_cast<int>(golem_Motion::LEAVE))
    {
        motioncount_ += 5 * deltatime;
        if (motioncount_ >= static_cast<int>(golem_frame_num::LEAVE))
        {
            SetState(Dead);
        }
    }
}

//ゴーレムにヒットしたときに出す関数
void EGolem::Set_Golemhit(int power)
{
    golem_hp_ -= power;

    if (golem_hp_ <= 0 && golem_state_ != static_cast<int>(golem_Motion::LEAVE))
    {
        Golem_texchange(static_cast<int>(golem_Motion::LEAVE));
    }
    PlaySound(sounds_[3], 0);
}

bool EGolem::Get_Isplayer()
{
    return k_Is_player_;
}
