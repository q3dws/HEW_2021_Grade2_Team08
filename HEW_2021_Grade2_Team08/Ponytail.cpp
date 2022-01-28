#include "Ponytail.h"
#include "EArmor.h"
#include "sound.h"
#define TESTPT
#define UNIQUE_COST 2


Ponytail::Ponytail(Game* game, Stage* stage):
    Enemy       (game, stage),
    sound      (LoadSound(L"Data/SE/Player/player_skill.wav"))
{
    textures_[ 0] = LoadTexture(L"Data/Image/enemy/chara_B_taiki_Sheet.png"      );//IDLE          ,
    textures_[ 1] = LoadTexture(L"Data/Image/enemy/chara_B_attack_Sheet.png"     );//ATTACK        ,
    textures_[ 2] = LoadTexture(L"Data/Image/enemy/charaB_move_front.png"        );//MOVE_FRONT    ,
    textures_[ 3] = LoadTexture(L"Data/Image/enemy/charaB_move_back.png"         );//MOVE_BACK     ,
    textures_[ 4] = LoadTexture(L"Data/Image/enemy/chara_B_taiki_Sheet.png"      );//MOVE_UPANDDOWN,
    textures_[ 5] = LoadTexture(L"Data/Image/enemy/charaB_snow_in-Sheet.png"     );//COLLECT_IN    ,
    textures_[ 6] = LoadTexture(L"Data/Image/enemy/charaB_snow_loop-Sheet.png"   );//COLLECT_LOOP  ,
    textures_[ 7] = LoadTexture(L"Data/Image/enemy/charaB_snow_out-Sheet.png"    );//COLLECT_OUT   ,
    textures_[ 8] = LoadTexture(L"Data/Image/enemy/charaB_damage.png"            );//HIT           ,
    textures_[ 9] = LoadTexture(L"Data/Image/enemy/chara_B_skill_Sheet.png"      );//USE_SKILL     ,// スキル使用
    textures_[10] = -1                                                            ;//USE_SKILL_IN  ,// ロボ専用
    textures_[11] = -1                                                            ;//USE_SKILL_LOOP,// ロボ専用
    textures_[12] = -1                                                            ;//USE_SKILL_OUT  // ロボ専用


    current_animation_->SetAnimTextures
    (
        textures_[EC(ANIMATION_INDEX::IDLE)],
        texsize_, 
        EC(ANIMATION_FRAME::IDLE),
        5.f
    );
}

void Ponytail::UpdateActor(float deltatime)
{
    UpdateLayer();
    UpdatePositionInfo();
    UpdateDirection();
    UpdateNextAction();

    if (current_frame_ >= UPDATE_FRAME_)
    {
        ChangeState();
        current_frame_ = 0;
    }
    else
    {
        ++current_frame_;
    }

    auto s = GetState();
    switch (s) {
    case Moving:
        Move();
        break;
    case Attacking:
        Attack();
        break;
    case Gathering_In:
    case Gathering_Loop:
    case Gathering_Out:
        Gather();
        break;
    case Unique_s:
        Unique();
        break;
    case Golem_s:
        Golem();
        break;
    case IceWall_s:
        Wall();
        break;
    case BigBullet_s:
        BigSnow();
        break;
    case Idle:
        ;
    default:
        ;
    }
}

void Ponytail::ChangeState()
{

    if (in_action_ == false)
    {
        //if (position_info_.is_behind_wall_)                                     //盾の後ろかどうか
        //{
        //    if (Probability(50))
        //    {
        //        SetState(Moving);
        //    }
        //    else if (Probability(33))
        //    {
        //        
        //    }
        //}
        //else
        //{
        //    if (position_info_.same_row && position_info_.h_distance == 1)      //同じ列で距離が１攻撃チャンス
        //    {
        //        ;
        //    }
        //    else if (position_info_.same_row && position_info_.h_distance < 3)       //同じ列で距離が２以下
        //    {
        //
        //    }
        //    else if(position_info_.h_distance < 3)                              //距離が２以下
        //    {
        //
        //    }
        //    else if (position_info_.same_row && position_info_.h_distance == 3)  //同じ列で距離が４以上 安全/ゾー/ン
        //    {
        //        
        //    }
        //
        //}

#ifdef TESTPT
        if (Probability(prob_info_.move_))
        {
            SetState(Moving);
            SetDestination();
            in_action_ = true;
        }
        else if (Probability(prob_info_.gather_))
        {
            SetState(Gathering_In);
            in_action_ = true;
        }
        else if (Probability(prob_info_.attack_))
        {
            SetState(Attacking);
            in_action_ = true;
        }
        else if (Probability(prob_info_.icewall_))
        {
            SetState(IceWall_s);
            in_action_ = true;
        }
        else if (Probability(prob_info_.golem_))
        {
            SetState(Golem_s);
            in_action_ = true;
        }
        else if (Probability(prob_info_.bigbullet_))
        {
            SetState(BigBullet_s);
            in_action_ = true;
        }
        else if (Probability(15))
        {
            SetState(Unique_s);
            in_action_ = true;
        }
#else
        if (Probability(50.0))
        {
            SetState(Moving);
            SetDestination();
            in_action_ = true;
        }
        else if (Probability(30.0))
        {
            SetState(Gathering);
            in_action_ = true;
        }
        else if (Probability(20.0))
        {
            SetState(Attacking);
            in_action_ = true;
        }
#endif
    }
}

void Ponytail::ChangeTexture(int tex)
{
    switch (tex)
    {
    case EC(ANIMATION_INDEX::IDLE           ):
    {
        current_animation_->SetAnimTextures
        (
            textures_.at(tex),
            texsize_,
            EC(ANIMATION_FRAME::IDLE),
            5.f
        );
        break;
    }
    case EC(ANIMATION_INDEX::ATTACK         ):
    {
        current_animation_->SetAnimTextures
        (
            textures_.at(tex),
            texsize_,
            EC(ANIMATION_FRAME::ATTACK),
            5.f
        );
        break;
    }
    case EC(ANIMATION_INDEX::MOVE_FRONT     ):
    {
        current_animation_->SetAnimTextures
        (
            textures_.at(tex),
            texsize_,
            EC(ANIMATION_FRAME::MOVE_FRONT),
            5.f
        );
        break;
    }
    case EC(ANIMATION_INDEX::MOVE_BACK      ):
    {
        current_animation_->SetAnimTextures
        (
            textures_.at(tex),
            texsize_,
            EC(ANIMATION_FRAME::MOVE_BACK),
            5.f
        );
        break;
    }
    case EC(ANIMATION_INDEX::MOVE_UPANDDOWN ):
    {
        current_animation_->SetAnimTextures
        (
            textures_.at(tex),
            texsize_,
            EC(ANIMATION_FRAME::MOVE_UPANDDOWN),
            5.f
        );
        break;
    }
    case EC(ANIMATION_INDEX::COLLECT_IN     ):
    {
        current_animation_->SetAnimTextures
        (
            textures_.at(tex),
            texsize_,
            EC(ANIMATION_FRAME::COLLECT_IN),
            5.f
        );
        break;
    }
    case EC(ANIMATION_INDEX::COLLECT_LOOP   ):
    {
        current_animation_->SetAnimTextures
        (
            textures_.at(tex),
            texsize_,
            EC(ANIMATION_FRAME::COLLECT_LOOP),
            5.f
        );
        break;
    }
    case EC(ANIMATION_INDEX::COLLECT_OUT    ):
    {
        current_animation_->SetAnimTextures
        (
            textures_.at(tex),
            texsize_,
            EC(ANIMATION_FRAME::COLLECT_OUT),
            5.f
        );
        break;
    }
    case EC(ANIMATION_INDEX::HIT            ):
    {
        current_animation_->SetAnimTextures
        (
            textures_.at(tex),
            texsize_,
            EC(ANIMATION_FRAME::HIT),
            5.f
        );
        break;
    }
    case EC(ANIMATION_INDEX::USE_SKILL      ):
    {
        current_animation_->SetAnimTextures
        (
            textures_.at(tex),
            texsize_,
            EC(ANIMATION_FRAME::USE_SKILL),
            5.f
        );
        break;
    }
    case EC(ANIMATION_INDEX::USE_SKILL_IN   ):
        break;
    case EC(ANIMATION_INDEX::USE_SKILL_LOOP ):
        break;
    case EC(ANIMATION_INDEX::USE_SKILL_OUT  ):
        break;
    }
}

void Ponytail::Unique()
{
    if (in_animation_)
    {
        if (current_animation_->IsAnimEnd() && GetState() == Unique_s)
        {
            in_action_ = false;
            in_animation_ = false;
            SetState(Idle);
            ChangeTexture(EC(ANIMATION_INDEX::IDLE));
        }
    }
    else
    {
        if (snow_num_ >= EC(Costs::ARMOR))
        {
            if (GetGame()->AddEArmor(new EArmor(GetGame(), GetPosition(), this, GetCollision().size_)))
            {
                PlaySound(sound, 0);
                snow_num_ -= EC(Costs::ARMOR);
                ChangeTexture(EC(ANIMATION_INDEX::USE_SKILL));
                in_animation_ = true;
            }
            else
            {
                in_action_ = false;
                SetState(Idle);
            }
        }
        else
        {
            in_action_ = false;
            SetState(Idle);
        }
    }
}