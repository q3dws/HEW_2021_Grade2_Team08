#pragma once
#ifndef SCORE_H_
#define SCORE_H_

#include "Actor.h"
#include "Game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCORE_MAX			(99)		// �X�R�A�̍ő�l
#define SCORE_DIGIT			(2)			// ����


class Score : public Actor 
{
public:
	Score(class Game* game);
	void UpdateActor(float deltatime) override;
	void AddScore(int add);
private:
	
};
class Score2 : public Actor
{
public:
	Score2(class Game* game);
};

#endif // SCORE_H_
