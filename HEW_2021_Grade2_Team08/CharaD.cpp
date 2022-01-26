#include "CharaD.h"

//プレイヤーのテクスチャを変える処理
void CharaD::Player_texchange(int texnum)
{
	player_mode_ = texnum;

	this->RemoveComponent(asc_);
	this->GetGame()->RemoveSprite(asc_);
	asc_ = new AnimSpriteComponent(this, player_layer_);

	if (texnum == static_cast<int>(PlayerMotion::IDLE))
	{
		asc_->SetAnimTextures(k_charaD_[texnum], k_player_size_, static_cast<int>(charaD_frame_num::IDLE), 5.f);
	}

	if (texnum == static_cast<int>(PlayerMotion::ATTACK))
	{
		asc_->SetAnimTextures(k_charaD_[texnum], k_player_size_, static_cast<int>(charaD_frame_num::ATTACK), 5.f);
		idle_timeto_ = static_cast<int>(charaD_frame_num::ATTACK); //一定時間後に待機状態に
	}

	if (texnum == static_cast<int>(PlayerMotion::MOVE_FRONT))
	{
		asc_->SetAnimTextures(k_charaD_[texnum], k_player_size_, static_cast<int>(charaD_frame_num::MOVE_FRONT), 5.f);
	}

	if (texnum == static_cast<int>(PlayerMotion::MOVE_BACK))
	{
		asc_->SetAnimTextures(k_charaD_[texnum], k_player_size_, static_cast<int>(charaD_frame_num::MOVE_BACK), 5.f);

	}

	if (texnum == static_cast<int>(PlayerMotion::COLLECT_IN))
	{
		asc_->SetAnimTextures(k_charaD_[texnum], k_player_size_, static_cast<int>(charaD_frame_num::COLLECT_IN), 5.f);
		idle_timeto_ = static_cast<int>(charaD_frame_num::COLLECT_IN); //一定時間後に待機状態に
	}

	if (texnum == static_cast<int>(PlayerMotion::COLLECT_LOOP))
	{

		asc_->SetAnimTextures(k_charaD_[texnum], k_player_size_, static_cast<int>(charaD_frame_num::COLLECT_LOOP), 5.f);
		idle_timeto_ = static_cast<int>(charaD_frame_num::COLLECT_LOOP); //一定時間後に待機状態に

	}
	if (texnum == static_cast<int>(PlayerMotion::COLLECT_OUT))
	{
		asc_->SetAnimTextures(k_charaD_[texnum], k_player_size_, static_cast<int>(charaD_frame_num::COLLECT_OUT), 5.f);
		idle_timeto_ = static_cast<int>(charaD_frame_num::COLLECT_OUT); //一定時間後に待機状態に

	}
	if (texnum == static_cast<int>(PlayerMotion::USE_SKILL))
	{
		asc_->SetAnimTextures(k_charaD_[texnum], k_player_size_, static_cast<int>(charaD_frame_num::USE_SKILL), 5.f);
		idle_timeto_ = static_cast<int>(charaD_frame_num::USE_SKILL); //一定時間後に待機状態に

	}

	if (texnum == static_cast<int>(PlayerMotion::MOVE_UPANDDOWN))
	{
		asc_->SetAnimTextures(k_charaD_[static_cast<int>(PlayerMotion::MOVE_UPANDDOWN)], k_player_size_, static_cast<int>(charaD_frame_num::MOVE_UPANDDOWN), 5.f);
	}

	if (texnum == static_cast<int>(PlayerMotion::USE_SKILL_IN))
	{
		asc_->SetAnimTextures(k_charaD_[static_cast<int>(PlayerMotion::USE_SKILL_IN)], k_player_size_, static_cast<int>(charaD_frame_num::USE_SKILL_IN), 5.f);	
		idle_timeto_ = static_cast<int>(charaD_frame_num::USE_SKILL_IN); //一定時間後に待機状態に

	}

	if (texnum == static_cast<int>(PlayerMotion::USE_SKILL_LOOP))
	{
		asc_->SetAnimTextures(k_charaD_[static_cast<int>(PlayerMotion::USE_SKILL_LOOP)], k_player_size_, static_cast<int>(charaD_frame_num::USE_SKILL_LOOP), 5.f);
	
		idle_timeto_ = machineguns_.back()->GetMachinegunTime(0.05f); //一定時間後に待機状態に
	}

	if (texnum == static_cast<int>(PlayerMotion::USE_SKILL_OUT))
	{
		asc_->SetAnimTextures(k_charaD_[static_cast<int>(PlayerMotion::USE_SKILL_OUT)], k_player_size_, static_cast<int>(charaD_frame_num::USE_SKILL_OUT), 5.f);
	
		idle_timeto_ = static_cast<int>(charaD_frame_num::USE_SKILL_OUT); //一定時間後に待機状態に
	}
	if (texnum == static_cast<int>(PlayerMotion::HIT))
	{
		asc_->SetAnimTextures(k_charaD_[texnum], k_player_size_, static_cast<int>(charaD_frame_num::HIT), 5.f);
		idle_timeto_ = damagetime_; //一定時間後に待機状態に

	}
}

//固有スキルの関数
void CharaD::Player_UniqueSkill(void)
{

	Player_texchange(static_cast<int>(PlayerMotion::USE_SKILL_IN));

	//auto a = new Machinegun(GetGame(), k_Is_player_, player_pos_, bullettex_, player_snow_);

	//弾を生成
	machineguns_.emplace_back(new Machinegun(GetGame(), k_Is_player_, player_pos_, bullettex_, player_snow_
		, static_cast<int>(charaD_frame_num::USE_SKILL_IN))
		);

	player_snow_ = 0;
}
