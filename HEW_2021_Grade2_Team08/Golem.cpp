#include "Golem.h"
#include "Bullet.h"
#include "Player.h"
#include "sound.h"

Golem::Golem(Game* game, Vec2 pos,  int bullettex, int layer, bool Is_player_) : Skill(game)
,k_golem_pos_(Vec2(pos))
,k_golem_size_(Vec2(-64 * 2, -64 * 2))
,k_bullettex_(bullettex)
,k_golem_layer(layer - 1)
, k_Is_player_(Is_player_)
, golem_hp_(2)
, k_golem_SE{
	LoadSound(L"Data/SE/Skill/golem_init.wav"),
	LoadSound(L"Data/SE/Skill/golem_throw.wav"),
	LoadSound(L"Data/SE/Skill/golem_death.wav"),
	LoadSound(L"Data/SE/Skill/golem_hit.wav"),
}
{
	golem_tex_[0] = LoadTexture(L"Data/Image/skill/golem_up_Sheet_Right.png");
	golem_tex_[1] = LoadTexture(L"Data/Image/skill/golem_throw_Sheet_Right.png");
	golem_tex_[2] = LoadTexture(L"Data/Image/skill/golem_down_Sheet_Right.png");
	golem_tex_[3] = LoadTexture(L"Data/Image/skill/golem_damage_A_Right.png");

	if (k_Is_player_ == false)
	{
		golem_tex_[0] = LoadTexture(L"Data/Image/skill/golem_up_Sheet.png");
		golem_tex_[1] = LoadTexture(L"Data/Image/skill/golem_throw_Sheet.png");
		golem_tex_[2] = LoadTexture(L"Data/Image/skill/golem_down_Sheet.png");
		golem_tex_[3] = LoadTexture(L"Data/Image/skill/golem_damage_A.png");

		k_golem_size_ = (Vec2(64 * 2, 64 * 2));
	}

	this->attackcount_ = static_cast<int>(golem_frame_num::ATTACK) - 10;	//������R�}�܂ł̒���
	this->motioncount_ = 0;
	this->golem_state_ = static_cast<int>(golem_Motion::ADVENT);
	
	this->SetPosition(k_golem_pos_);
	this->golem_asc_ = new AnimSpriteComponent(this, k_golem_layer);
	Golem::Golem_texchange(static_cast<int>(golem_Motion::ADVENT));

	GetGame()->SetGolem(this);
	//SetCollision(Rect(k_golem_pos_ - Vec2(0,20), Vec2(64 * 2, 64 * 2) - Vec2(64, 82)));

	PlaySound(k_golem_SE[static_cast<int>(golem_Motion::ADVENT)], 0);
}

Golem::~Golem()
{
	GetGame()->RemoveGolem(this);
}

void Golem::UpdateActor(float deltatime)
{
	Actor::UpdateActor(deltatime);

	Golem::Golem_snow_throw(deltatime);
	

}

//�S�[��������ʂ𓊂��鏈��
void Golem::Golem_snow_throw(float deltatime)
{

	switch (golem_state_)
	{
	case static_cast<int>(golem_Motion::ATTACK):
		attackcount_ += 5 * deltatime;
		//�U������R�}�ɂȂ�����ˌ�����
		if (attackcount_ >= static_cast<int>(golem_frame_num::ATTACK))
		{
			//�e�𐶐�
			bullets_.emplace_back(new Bullet(GetGame(), k_bullettex_, k_Is_player_, k_golem_pos_));

			attackcount_ = 0;

			PlaySound(k_golem_SE[static_cast<int>(golem_Motion::ATTACK)], 0);

			//�e���l�񓊂��Ă���Ǝ��S����
			deathcount++;
			if (deathcount > 4)
				Golem_texchange(static_cast<int>(golem_Motion::LEAVE));
		}
		break;
	case static_cast<int>(golem_Motion::ADVENT):
		//�o�ꒆ�̏ꍇ�̓A�j�����I���̂�҂��Ă���U����ԂɈڂ鏈��
		motioncount_ += 5 * deltatime;
		if (motioncount_ >= static_cast<int>(golem_frame_num::ADVENT))
		{

			Golem_texchange(static_cast<int>(golem_Motion::ATTACK));
			motioncount_ = 0;
		}
		break;
	case static_cast<int>(golem_Motion::LEAVE):
		//�S�[�����̑ޏ�A�j�����I���������������鏈��
		motioncount_ += 5 * deltatime;
		if (motioncount_ >= static_cast<int>(golem_frame_num::LEAVE))
		{
			SetState(Dead);
		}

		break;
	case static_cast<int>(golem_Motion::HIT):
		//�q�b�g�����ꍇ�̓A�j�����I���̂�҂��Ă���U����ԂɈڂ鏈��
		motioncount_ += 5 * deltatime;
		if (motioncount_ >= static_cast<int>(golem_frame_num::HIT))
		{
			if (golem_hp_ <= 0)
			{
				//hp��0�Ȃ玀��
				Golem_texchange(static_cast<int>(golem_Motion::LEAVE));
				motioncount_ = 0;

			}
			else
			{
				Golem_texchange(static_cast<int>(golem_Motion::ATTACK));
				motioncount_ = 0;
				this->attackcount_ = static_cast<int>(golem_frame_num::ATTACK) - 10;	//������R�}�܂ł̒���
			}
			
		}

		
		break;
	default:
		break;
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
		//�����蔻��o��
		SetCollision(Rect(k_golem_pos_ + Vec2(0, 20), Vec2(64 * 2, 64 * 2) - Vec2(64, 82)));

		golem_asc_->SetAnimTextures(golem_tex_[texnum], k_golem_size_, static_cast<int>(golem_frame_num::ATTACK), 5.f);
		//idle_timeto_ = static_cast<int>(charaA_frame_num::ATTACK); //��莞�Ԍ�ɑҋ@��Ԃ�
	}

	if (texnum == static_cast<int>(golem_Motion::LEAVE))
	{
		//�����蔻��tai��
		SetCollision(Rect(Vec2(0,0), Vec2(0, 0)));
		PlaySound(k_golem_SE[static_cast<int>(golem_Motion::LEAVE)], 0);
		golem_asc_->SetAnimTextures(golem_tex_[texnum], k_golem_size_, static_cast<int>(golem_frame_num::LEAVE), 5.f);
	}

	if (texnum == static_cast<int>(golem_Motion::HIT))
	{
		golem_asc_->SetAnimTextures(golem_tex_[texnum], k_golem_size_, static_cast<int>(golem_frame_num::HIT), 5.f);
	}
}


//�S�[�����Ƀq�b�g�����Ƃ��ɏo���֐�
void Golem::Set_Golemhit(int power)
{
	if (golem_state_ == static_cast<int>(golem_Motion::HIT))
	{
		return;
	}

	golem_hp_ -= power;
	Golem_texchange(static_cast<int>(golem_Motion::HIT));
	motioncount_ = 0;

	PlaySound(k_golem_SE[static_cast<int>(golem_Motion::HIT)], 0);
}

bool Golem::Get_Isplayer()
{
	return k_Is_player_;
}
