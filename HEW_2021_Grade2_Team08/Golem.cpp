#include "Golem.h"
#include "Bullet.h"

Golem::Golem(Game* game, Vec2 pos,  int bullettex, int layer, bool Is_player_) : Skill(game)
,k_golem_pos_(Vec2(pos))
,k_golem_size_(Vec2(-64 * 2, -64 * 2))
,k_bullettex_(bullettex)
,k_golem_layer(layer - 1)
, k_Is_player_(Is_player_)
{
	golem_tex_[0] = LoadTexture(L"Data/Image/skill/golem_up_Sheet_Right.png");
	golem_tex_[1] = LoadTexture(L"Data/Image/skill/golem_throw_Sheet_Right.png");
	golem_tex_[2] = LoadTexture(L"Data/Image/skill/golem_down_Sheet_Right.png");
	
	if (k_Is_player_ == false)
	{
		golem_tex_[0] = LoadTexture(L"Data/Image/skill/golem_up_Sheet.png");
		golem_tex_[1] = LoadTexture(L"Data/Image/skill/golem_throw_Sheet.png");
		golem_tex_[2] = LoadTexture(L"Data/Image/skill/golem_down_Sheet.png");

		k_golem_size_ = (Vec2(64 * 2, 64 * 2));
	}

	this->attackcount_ = static_cast<int>(golem_frame_num::ATTACK) - 10;	//������R�}�܂ł̒���
	this->motioncount_ = 0;
	this->golem_state_ = static_cast<int>(golem_Motion::ADVENT);
	
	this->SetPosition(k_golem_pos_);
	this->golem_asc_ = new AnimSpriteComponent(this, k_golem_layer);
	Golem::Golem_texchange(static_cast<int>(golem_Motion::ADVENT));

}

void Golem::UpdateActor(float deltatime)
{
	Actor::UpdateActor(deltatime);

	Golem::Golem_snow_throw(deltatime);
	Golem::Golem_death_check(deltatime);

}

//�S�[��������ʂ𓊂��鏈��
void Golem::Golem_snow_throw(float deltatime)
{
	if (golem_state_ == static_cast<int>(golem_Motion::ATTACK))
	{
		attackcount_ += 5 * deltatime;
		//�U������R�}�ɂȂ�����ˌ�����
		if (attackcount_ >= static_cast<int>(golem_frame_num::ATTACK))
		{
			//�e�𐶐�
			bullets_.emplace_back(new Bullet(GetGame(), k_bullettex_,k_Is_player_, k_golem_pos_));
			
			attackcount_ = 0;
			
			//�e���l�񓊂��Ă���Ǝ��S����
			deathcount++;
			if(deathcount > 4)
				Golem_texchange(static_cast<int>(golem_Motion::LEAVE));
		}
	}
	else if(golem_state_ == static_cast<int>(golem_Motion::ADVENT))
	{
		//�o�ꒆ�̏ꍇ�̓A�j�����I���̂�҂��Ă���U����ԂɈڂ鏈��
		motioncount_ += 5 * deltatime;
		if (motioncount_ >= static_cast<int>(golem_frame_num::ADVENT))
		{
			Golem_texchange(static_cast<int>(golem_Motion::ATTACK));
			motioncount_ = 0;
		}
	}

}

//�S�[�����̃e�N�X�`����؂�ւ��鏈��
void Golem::Golem_texchange(int texnum)
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
		golem_asc_->SetAnimTextures(golem_tex_[texnum], k_golem_size_, static_cast<int>(golem_frame_num::ATTACK), 5.f);
		//idle_timeto_ = static_cast<int>(charaA_frame_num::ATTACK); //��莞�Ԍ�ɑҋ@��Ԃ�
	}

	if (texnum == static_cast<int>(golem_Motion::LEAVE))
	{
		golem_asc_->SetAnimTextures(golem_tex_[texnum], k_golem_size_, static_cast<int>(golem_frame_num::LEAVE), 5.f);
	}

}

//�S�[�����̑ޏ�A�j�����I���������������鏈��
void Golem::Golem_death_check(float deltatime)
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