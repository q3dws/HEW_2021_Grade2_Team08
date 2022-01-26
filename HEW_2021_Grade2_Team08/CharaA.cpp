#include "CharaA.h"
#include "Scoop.h"

//プレイヤーのテクスチャを変える処理
void CharaA::Player_texchange(int texnum) 
{
	player_mode_ = texnum;

	this->RemoveComponent(asc_);
	this->GetGame()->RemoveSprite(asc_);
	asc_ = new AnimSpriteComponent(this, player_layer_);

	switch (texnum)
	{
	case static_cast<int>(PlayerMotion::IDLE):
		asc_->SetAnimTextures(k_charaA_[texnum], k_player_size_, static_cast<int>(charaA_frame_num::IDLE), 5.f);
		break;

	case static_cast<int>(PlayerMotion::ATTACK):
		asc_->SetAnimTextures(k_charaA_[texnum], k_player_size_, static_cast<int>(charaA_frame_num::ATTACK), 5.f);
		idle_timeto_ = static_cast<int>(charaA_frame_num::ATTACK); //一定時間後に待機状態に
		break;

	case static_cast<int>(PlayerMotion::MOVE_FRONT):
		asc_->SetAnimTextures(k_charaA_[texnum], k_player_size_, static_cast<int>(charaA_frame_num::MOVE_FRONT), 5.f);

		break;

	case static_cast<int>(PlayerMotion::MOVE_BACK):
		asc_->SetAnimTextures(k_charaA_[texnum], k_player_size_, static_cast<int>(charaA_frame_num::MOVE_BACK), 5.f);

		break;

	case static_cast<int>(PlayerMotion::COLLECT_IN):
		asc_->SetAnimTextures(k_charaA_[texnum], k_player_size_, static_cast<int>(charaA_frame_num::COLLECT_IN), 5.f);
		idle_timeto_ = static_cast<int>(charaA_frame_num::COLLECT_IN); //一定時間後に待機状態に
		break;

	case static_cast<int>(PlayerMotion::COLLECT_LOOP):
		asc_->SetAnimTextures(k_charaA_[texnum], k_player_size_, static_cast<int>(charaA_frame_num::COLLECT_LOOP), 5.f);
		idle_timeto_ = static_cast<int>(charaA_frame_num::COLLECT_LOOP); //一定時間後に待機状態に
		break;

	case static_cast<int>(PlayerMotion::COLLECT_OUT):
		asc_->SetAnimTextures(k_charaA_[texnum], k_player_size_, static_cast<int>(charaA_frame_num::COLLECT_OUT), 5.f);
		idle_timeto_ = static_cast<int>(charaA_frame_num::COLLECT_OUT); //一定時間後に待機状態に
		break;

	case static_cast<int>(PlayerMotion::USE_SKILL):
		asc_->SetAnimTextures(k_charaA_[texnum], k_player_size_, static_cast<int>(charaA_frame_num::USE_SKILL), 5.f);
		idle_timeto_ = static_cast<int>(charaA_frame_num::USE_SKILL); //一定時間後に待機状態に
		break;

	case static_cast<int>(PlayerMotion::MOVE_UPANDDOWN):
		//上下移動はIDLEの画像を使います
		asc_->SetAnimTextures(k_charaA_[static_cast<int>(PlayerMotion::MOVE_UPANDDOWN)], k_player_size_, static_cast<int>(charaA_frame_num::MOVE_UPANDDOWN), 5.f);
		break;

	case static_cast<int>(PlayerMotion::HIT):
		asc_->SetAnimTextures(k_charaA_[texnum], k_player_size_, static_cast<int>(charaA_frame_num::HIT), 5.f);
		idle_timeto_ = damagetime_; //一定時間後に待機状態に
		break;

	default:
		break;
	}
	
}

//固有スキルの関数
void CharaA::Player_UniqueSkill(void)
{

	Player_texchange(static_cast<int>(PlayerMotion::USE_SKILL));
	//弾を生成
	auto a = (new Scoop(GetGame(), player_layer_, player_pos_, k_Is_player_, stg_,this));
	//scoops_.back()->SetPosition(this->GetPosition());

	//scoops;
	player_snow_ -= k_player_skillcost_[3];
}
