#include "enemytestB.h"

//プレイヤーのテクスチャを変える処理
void EnemytestB::Player_texchange(int texnum)
{
	player_mode_ = texnum;

	this->RemoveComponent(asc_);
	this->GetGame()->RemoveSprite(asc_);
	asc_ = new AnimSpriteComponent(this, 100);

	if (texnum == static_cast<int>(PlayerMotion::IDLE))
	{
		asc_->SetAnimTextures(k_enemyB_[texnum], k_player_size_, static_cast<int>(enemyB_frame_num::IDLE), 5.f);
	}

	if (texnum == static_cast<int>(PlayerMotion::ATTACK))
	{
		asc_->SetAnimTextures(k_enemyB_[texnum], k_player_size_, static_cast<int>(enemyB_frame_num::ATTACK), 5.f);
		idle_timeto_ = static_cast<int>(enemyB_frame_num::ATTACK); //一定時間後に待機状態に
	}

	if (texnum == static_cast<int>(PlayerMotion::MOVE_FRONT))
	{
		asc_->SetAnimTextures(k_enemyB_[texnum], k_player_size_, static_cast<int>(enemyB_frame_num::MOVE_FRONT), 5.f);
	}

	if (texnum == static_cast<int>(PlayerMotion::MOVE_BACK))
	{
		asc_->SetAnimTextures(k_enemyB_[texnum], k_player_size_, static_cast<int>(enemyB_frame_num::MOVE_BACK), 5.f);

	}

	if (texnum == static_cast<int>(PlayerMotion::COLLECT_IN))
	{
		asc_->SetAnimTextures(k_enemyB_[texnum], k_player_size_, static_cast<int>(enemyB_frame_num::COLLECT_IN), 5.f);
		idle_timeto_ = static_cast<int>(enemyB_frame_num::COLLECT_IN); //一定時間後に待機状態に
	}

	if (texnum == static_cast<int>(PlayerMotion::COLLECT_LOOP))
	{

		asc_->SetAnimTextures(k_enemyB_[texnum], k_player_size_, static_cast<int>(enemyB_frame_num::COLLECT_LOOP), 5.f);
		idle_timeto_ = static_cast<int>(enemyB_frame_num::COLLECT_LOOP); //一定時間後に待機状態に

	}
	if (texnum == static_cast<int>(PlayerMotion::COLLECT_OUT))
	{
		asc_->SetAnimTextures(k_enemyB_[texnum], k_player_size_, static_cast<int>(enemyB_frame_num::COLLECT_OUT), 5.f);
		idle_timeto_ = static_cast<int>(enemyB_frame_num::COLLECT_OUT); //一定時間後に待機状態に

	}

}