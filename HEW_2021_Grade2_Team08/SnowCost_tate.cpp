#include "SnowCost_tate.h"

SnowCost_tate::SnowCost_tate(Game* game, bool Is_player) : Actor(game)
, k_snowframe_tex_(LoadTexture(L"Data/Image/UI/yukicost/yukicost_tate/snowcostwaku_tate.png"))
, k_frame_size_(Vec2(400, 400))
, k_frame_pos_(Vec2(60, 250))
, k_point_pos_(Vec2(k_frame_pos_.x_ - 16, k_frame_pos_.y_ + 98))
, k_point_size_(Vec2(k_frame_size_.x_ / 7, k_frame_size_.y_ / 7))
, k_point_var_(Vec2(30 , 34.5))
, k_point_num_(18)
, k_Is_player_(Is_player)
{
    frame_asc_ = new SpriteComponent(this, 150);
    frame_asc_->SetTexture(k_snowframe_tex_, k_frame_size_, Vec2(0, 0), Vec2(1, 1));

    if (k_Is_player_ == false)
    {
        k_frame_pos_ = (Vec2(WINDOW_WIDTH - k_frame_pos_.x_, k_frame_pos_.y_));
        k_point_pos_ = (Vec2(k_frame_pos_.x_ - 16, k_frame_pos_.y_ + 98));
    }

    SetPosition(k_frame_pos_);
    //k_point_num_�̕������������X�v���C�g�𐶐�����
   
    for (int j = 0; j < 2; j++)
    for (int i = 0; i < k_point_num_  / 2; i++)
    {
        if(j == 0)
        snowpoints_.emplace_back(new SnowPoint_tate(GetGame()
            , Vec2(k_point_pos_.x_ + k_point_var_.x_ * j, k_point_pos_.y_ - k_point_var_.y_ * i), k_point_size_, 150 - 1));
        else
            snowpoints_.emplace_back(new SnowPoint_tate(GetGame()
                , Vec2(k_point_pos_.x_ + k_point_var_.x_ * j,
                    k_point_pos_.y_ - k_point_var_.y_ * (k_point_num_ / 2 - 1) + k_point_var_.y_ * i)
                , k_point_size_, 150 - 1));
    
    }

}

SnowCost_tate::~SnowCost_tate()
{
}

void SnowCost_tate::UpdateActor(float deltatime)
{
    Actor::UpdateActor(deltatime);
}

//�v���C���[�̎����Ă����̐���n���Ƃ��̕�����������������֐�
void SnowCost_tate::SetSnownum(int num)
{
    if (snowpoints_.empty() == false)
    {
        if (k_Is_player_)
            for (int i = 1; i <= k_point_num_; i++)
            {
                if (i <= num)
                {
                    snowpoints_[i - 1]->point_inset();
                }
                else
                {
                    snowpoints_[i - 1]->point_outset();
                }
            }
        else //�G�p
            for (int i = 1; i <= k_point_num_; i++)
            {
                if (i <= num)
                {
                    snowpoints_[k_point_num_ - i]->point_inset();
                }
                else
                {
                    snowpoints_[k_point_num_ - i]->point_outset();
                }

            }
    }
}

//-------------------------------------------------------
//��������
//-------------------------------------------------------
SnowPoint_tate::SnowPoint_tate(Game* game, Vec2 pos, Vec2 size, int layer)
    :Actor(game)
    , k_point_size_(size)
    , k_point_pos_(pos)
    , k_point_layer_(layer)
    , point_tex_{
     LoadTexture(L"Data/Image/UI/yukicost/yukicost_tate/yukimemori_in.png")
    ,LoadTexture(L"Data/Image/UI/yukicost/yukicost_tate/yukimemori_tte.png")
    ,LoadTexture(L"Data/Image/UI/yukicost/yukicost_tate/yukimemori_out.png")
}
{
    motioncount_ = 0;
    point_asc_ = new AnimSpriteComponent(this, k_point_layer_);

    UVWH = Vec2(0, 0);
    point_asc_->SetAnimTextures(point_tex_[static_cast<int>(point_Motion::IDLE)], k_point_size_, static_cast<int>(point_frame_num::IDLE), 5.f);
    point_texchange(static_cast<int>(point_Motion::IDLE));

    SetPosition(k_point_pos_);
}

SnowPoint_tate::~SnowPoint_tate()
{

}

void SnowPoint_tate::UpdateActor(float deltatime)
{
    Actor::UpdateActor(deltatime);

    //point_asc_->SetUV(Vec2(0,0), UVWH);
    if (UVWH.x_ == 1)
        SetPosition(k_point_pos_);

    if (UVWH.x_ == 0)
    {
        SetPosition(Vec2(-50, -50));
        point_texchange(static_cast<int>(point_Motion::IDLE));
    }

    switch (point_state_)
    {
    case static_cast<int>(point_Motion::ADVENT):
        //�o�ꒆ
        motioncount_ += 5 * deltatime;
        if (motioncount_ >= static_cast<int>(point_frame_num::ADVENT))
        {
            point_texchange(static_cast<int>(point_Motion::IDLE));
            motioncount_ = 0;
        }
        break;
    case static_cast<int>(point_Motion::IDLE):
        //�ʏ풆

        break;
    case static_cast<int>(point_Motion::LEAVE):
        //�ޏꒆ
        motioncount_ += 5 * deltatime;
        if (motioncount_ >= static_cast<int>(point_frame_num::LEAVE))
        {
            SetPosition(Vec2(-50, -50));
            motioncount_ = 0; 
            pointUVWHset(Vec2(0, 0));
        }
        
        break;
    default:
        break;
    }
}

//�������̕`��̔�����ς���֐�
void SnowPoint_tate::pointUVWHset(Vec2 uvwh)
{
    UVWH = uvwh;
}

void SnowPoint_tate::point_inset()
{
    if (UVWH.x_ == 0 && point_state_ == static_cast<int>(point_Motion::IDLE))
    {
        motioncount_ = 0;
        pointUVWHset(Vec2(1, 1));
        point_texchange(static_cast<int>(point_Motion::ADVENT));
    }

}

void SnowPoint_tate::point_outset()
{
    if (UVWH.x_ == 1 && point_state_ == static_cast<int>(point_Motion::IDLE))
    {
        motioncount_ = 0;
        //pointUVWHset(Vec2(1, 1));
        point_texchange(static_cast<int>(point_Motion::LEAVE));
    }
}

void SnowPoint_tate::point_texchange(int texnum)
{
    point_state_ = texnum;

    this->RemoveComponent(point_asc_);
    this->GetGame()->RemoveSprite(point_asc_);
    //point_asc_ = new AnimSpriteComponent(this, k_point_layer_);

    if (texnum == static_cast<int>(point_Motion::ADVENT))
    {
        point_asc_ = new AnimSpriteComponent(this, k_point_layer_ + 10);
        point_asc_->SetAnimTextures(point_tex_[texnum], k_point_size_, static_cast<int>(point_frame_num::ADVENT), 5.f);
    }

    if (texnum == static_cast<int>(point_Motion::IDLE))
    {
        point_asc_ = new AnimSpriteComponent(this, k_point_layer_);
        point_asc_->SetAnimTextures(point_tex_[texnum], k_point_size_, static_cast<int>(point_frame_num::IDLE), 5.f);
        //idle_timeto_ = static_cast<int>(charaA_frame_num::ATTACK); //��莞�Ԍ�ɑҋ@��Ԃ�
    }

    if (texnum == static_cast<int>(point_Motion::LEAVE))
    {
        point_asc_ = new AnimSpriteComponent(this, k_point_layer_ + 10);
        point_asc_->SetAnimTextures(point_tex_[texnum], k_point_size_, static_cast<int>(point_frame_num::LEAVE), 5.f);
    }

}


