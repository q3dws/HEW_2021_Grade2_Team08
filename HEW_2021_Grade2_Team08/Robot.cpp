#include "Robot.h"
#include "EMachinegun.h"
#include "sound.h"
#define TESTPT
#define UNIQUE_COST 1


Robot::Robot(Game* game, Stage* stage):
    Enemy     (game, stage),
    bulletnum_(           ),
    sound(LoadSound(L"Data/SE/Player/player_skill.wav"))
{
    textures_[ 0] = LoadTexture(L"Data/Image/enemy/charaD_taiki_Sheet.png"       );//IDLE          ,
    textures_[ 1] = LoadTexture(L"Data/Image/enemy/charaD_attack_Sheet.png"      );//ATTACK        ,
    textures_[ 2] = LoadTexture(L"Data/Image/enemy/charaD_move_front.png"        );//MOVE_FRONT    ,
    textures_[ 3] = LoadTexture(L"Data/Image/enemy/charaD_move_back.png"         );//MOVE_BACK     ,
    textures_[ 4] = LoadTexture(L"Data/Image/enemy/charaD_taiki_Sheet.png"       );//MOVE_UPANDDOWN,
    textures_[ 5] = LoadTexture(L"Data/Image/enemy/charaD_snow_in_Sheet.png"     );//COLLECT_IN    ,
    textures_[ 6] = LoadTexture(L"Data/Image/enemy/charaD_snow_loop_Sheet.png"   );//COLLECT_LOOP  ,
    textures_[ 7] = LoadTexture(L"Data/Image/enemy/charaD_snow_out_Sheet.png"    );//COLLECT_OUT   ,
    textures_[ 8] = LoadTexture(L"Data/Image/enemy/charaD_damage.png"            );//HIT           ,
    textures_[ 9] = LoadTexture(L"Data/Image/enemy/charaD_skill2_Sheet.png"      );//USE_SKILL     ,// スキル使用
    textures_[10] = LoadTexture(L"Data/Image/enemy/charaD_skill_in_Sheet.png"    );//USE_SKILL_IN  ,// ロボ専用
    textures_[11] = LoadTexture(L"Data/Image/enemy/charaD_skill_loop_Sheet.png"  );//USE_SKILL_LOOP,// ロボ専用
    textures_[12] = LoadTexture(L"Data/Image/enemy/charaD_skill_out_Sheet.png"   );//USE_SKILL_OUT  // ロボ専用


    current_animation_->SetAnimTextures
    (
        textures_[EC(ANIMATION_INDEX::IDLE)],
        texsize_, 
        EC(ANIMATION_FRAME::IDLE),
        5.f
    );
}

void Robot::UpdateActor(float deltatime)
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
    case Golem_s:
        Golem();
        break;
    case IceWall_s:
        Wall();
        break;
    case BigBullet_s:
        BigSnow();
        break;
    case UsingSkills_In:
    case UsingSkills_Loop:
    case UsingSkills_Out:
        Unique();
    case Idle:
        ;
    default:
        ;
    }
}

void Robot::ChangeState()
{
    if (in_action_ == false)
    {
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
        else if (Probability(prob_info_.unique_))
        {
            SetState(UsingSkills_In);
            in_action_ = true;
        }
        else if (Probability(prob_info_.golem_))
        {
            SetState(Golem_s);
            in_action_ = true;
        }
        else if (Probability(prob_info_.icewall_))
        {
            SetState(IceWall_s);
            in_action_ = true;
        }
        else if (Probability(prob_info_.bigbullet_))
        {
            SetState(BigBullet_s);
            in_action_ = true;
        }
#else
#endif
    }
}

void Robot::ChangeTexture(int tex)
{
    switch (tex)
    {
    case EC(ANIMATION_INDEX::IDLE):
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
    case EC(ANIMATION_INDEX::ATTACK):
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
    case EC(ANIMATION_INDEX::MOVE_FRONT):
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
    case EC(ANIMATION_INDEX::MOVE_BACK):
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
    case EC(ANIMATION_INDEX::MOVE_UPANDDOWN):
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
    case EC(ANIMATION_INDEX::COLLECT_IN):
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
    case EC(ANIMATION_INDEX::COLLECT_LOOP):
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
    case EC(ANIMATION_INDEX::COLLECT_OUT):
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
    case EC(ANIMATION_INDEX::HIT):
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
    case EC(ANIMATION_INDEX::USE_SKILL):
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
    case EC(ANIMATION_INDEX::USE_SKILL_IN):
        current_animation_->SetAnimTextures
        (
            textures_.at(tex),
            texsize_,
            EC(ANIMATION_FRAME::USE_SKILL_IN),
            5.f
        );
        break;
    case EC(ANIMATION_INDEX::USE_SKILL_LOOP):
        current_animation_->SetAnimTextures
        (
            textures_.at(tex),
            texsize_,
            EC(ANIMATION_FRAME::USE_SKILL_LOOP),
            5.f
        );
        break;
    case EC(ANIMATION_INDEX::USE_SKILL_OUT):
        current_animation_->SetAnimTextures
        (
            textures_.at(tex),
            texsize_,
            EC(ANIMATION_FRAME::USE_SKILL_OUT),
            5.f
        );
        break;
    }
}

void Robot::Unique()
{
    auto gs = GetState();
    if (in_animation_)
    {
        if (current_animation_->IsAnimEnd() && gs == UsingSkills_In)
        {
            SetState(UsingSkills_Loop);
            ChangeTexture(EC(ANIMATION_INDEX::USE_SKILL_LOOP));
            emachinegun_ = new EMachinegun(GetGame(), GetCollision().center_, bullettex_, snow_num_);
            snow_num_ = 0;
        }
        else if (current_animation_->IsAnimEnd() && gs == UsingSkills_Loop)
        {
            if (emachinegun_->Is_MGEnd())
            {
                emachinegun_ = nullptr;
                SetState(UsingSkills_Out);
                ChangeTexture(EC(ANIMATION_INDEX::USE_SKILL_OUT));
            }
        }
        else if (current_animation_->IsAnimEnd() && gs == UsingSkills_Out)
        {
            in_action_ = false;
            in_animation_ = false;
            SetState(Idle);
            ChangeTexture(EC(ANIMATION_INDEX::IDLE));
        }
    }
    else
    {
        if (snow_num_ >= EC(Costs::MACHINEGUN))
        {
            PlaySound(sound, 0);
            ChangeTexture(EC(ANIMATION_INDEX::USE_SKILL_IN));
            in_animation_ = true;
        }
        else
        {
            in_action_ = false;
            SetState(Idle);
        }
    }
}
