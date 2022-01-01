#include "DEBUG_Comand.h"

DEBUG_Comand::DEBUG_Comand(Game* game, bool Is_Player) : Actor(game)
,k_Is_player_(Is_Player)
{
	countDEBUG_ = 0;
}

void DEBUG_Comand::UpdateActor(float deltatime)
{
	Actor::UpdateActor(deltatime);

	if (GetKeyboardTrigger(DIK_UP) && k_Is_player_ && countDEBUG_ < 2)
		countDEBUG_++;

	if (GetKeyboardTrigger(DIK_DOWN) && k_Is_player_ && 2 <= countDEBUG_ &&countDEBUG_ < 4)
		countDEBUG_++;

	if (GetKeyboardTrigger(DIK_LEFT) && k_Is_player_ && (countDEBUG_ == 4 || countDEBUG_ == 6))
		countDEBUG_++;

	if (GetKeyboardTrigger(DIK_RIGHT) && k_Is_player_ && (countDEBUG_ == 5 || countDEBUG_ == 7))
		countDEBUG_++;

	if (GetKeyboardTrigger(DIK_A) && k_Is_player_ && countDEBUG_ == 8)
		countDEBUG_ = 11;

	if (GetKeyboardTrigger(DIK_B) && k_Is_player_ && countDEBUG_ == 8)
		countDEBUG_++;

	if (GetKeyboardTrigger(DIK_A) && k_Is_player_ && countDEBUG_ == 9)
		countDEBUG_++;
}

bool DEBUG_Comand::CheckDEBUGmode()
{
	if (countDEBUG_ == 10)
	{
		countDEBUG_++;
		return true;
	}
	return false;
}
