#include "CharaA.h"


//�v���C���[�̃e�N�X�`����ς��鏈��
void CharaA::Player_texchange(int texnum) 
{
	player_mode_ = texnum;

	this->RemoveComponent(asc_);
	this->GetGame()->RemoveSprite(asc_);
	asc_ = new AnimSpriteComponent(this, player_layer_);

	if (texnum == static_cast<int>(PlayerMotion::IDLE))
	{
		asc_->SetAnimTextures(k_charaA_[texnum], k_player_size_, static_cast<int>(charaA_frame_num::IDLE), 5.f);
	}

	if (texnum == static_cast<int>(PlayerMotion::ATTACK))
	{
		asc_->SetAnimTextures(k_charaA_[texnum], k_player_size_, static_cast<int>(charaA_frame_num::ATTACK), 5.f);
		idle_timeto_ = static_cast<int>(charaA_frame_num::ATTACK); //��莞�Ԍ�ɑҋ@��Ԃ�
	}

	if (texnum == static_cast<int>(PlayerMotion::MOVE_FRONT))
	{
		asc_->SetAnimTextures(k_charaA_[texnum], k_player_size_, static_cast<int>(charaA_frame_num::MOVE_FRONT), 5.f);
	}

	if (texnum == static_cast<int>(PlayerMotion::MOVE_BACK))
	{
		asc_->SetAnimTextures(k_charaA_[texnum], k_player_size_, static_cast<int>(charaA_frame_num::MOVE_BACK), 5.f);

	}

	if (texnum == static_cast<int>(PlayerMotion::COLLECT_IN))
	{
		asc_->SetAnimTextures(k_charaA_[texnum], k_player_size_, static_cast<int>(charaA_frame_num::COLLECT_IN), 5.f);
		idle_timeto_ = static_cast<int>(charaA_frame_num::COLLECT_IN); //��莞�Ԍ�ɑҋ@��Ԃ�
	}

	if (texnum == static_cast<int>(PlayerMotion::COLLECT_LOOP))
	{

		asc_->SetAnimTextures(k_charaA_[texnum], k_player_size_, static_cast<int>(charaA_frame_num::COLLECT_LOOP), 5.f);
		idle_timeto_ = static_cast<int>(charaA_frame_num::COLLECT_LOOP); //��莞�Ԍ�ɑҋ@��Ԃ�

	}
	if (texnum == static_cast<int>(PlayerMotion::COLLECT_OUT))
	{
		asc_->SetAnimTextures(k_charaA_[texnum], k_player_size_, static_cast<int>(charaA_frame_num::COLLECT_OUT), 5.f);
		idle_timeto_ = static_cast<int>(charaA_frame_num::COLLECT_OUT); //��莞�Ԍ�ɑҋ@��Ԃ�

	}
	if (texnum == static_cast<int>(PlayerMotion::USE_SKILL))
	{
		asc_->SetAnimTextures(k_charaA_[texnum], k_player_size_, static_cast<int>(charaA_frame_num::USE_SKILL), 5.f);
		idle_timeto_ = static_cast<int>(charaA_frame_num::USE_SKILL); //��莞�Ԍ�ɑҋ@��Ԃ�

	}

	//�㉺�ړ���IDLE�̉摜���g���܂�
	if (texnum == static_cast<int>(PlayerMotion::MOVE_UPANDDOWN))
	{
		asc_->SetAnimTextures(k_charaA_[static_cast<int>(PlayerMotion::MOVE_UPANDDOWN)], k_player_size_, static_cast<int>(charaA_frame_num::MOVE_UPANDDOWN), 5.f);
	}
}

//�ŗL�X�L���̊֐�
void CharaA::Player_UniqueSkill(void)
{
	Player_texchange(static_cast<int>(PlayerMotion::USE_SKILL));
	//�e�𐶐�
	scoops_.emplace_back(new Scoop(GetGame(),player_layer_,player_pos_));
	scoops_.back()->SetPosition(this->GetPosition());
}