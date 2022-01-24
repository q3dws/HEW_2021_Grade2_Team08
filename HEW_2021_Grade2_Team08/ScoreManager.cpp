#include "ScoreManager.h"
#include "Game.h"
#include "Texture.h"
#include "SpriteComponent.h"
#include "BGSpriteComponent.h"
#include "Timer.h"

ScoreManager::ScoreManager(Game* game)
	:Actor(game)
	,SCORE_MAX(99)
	, k_fight_time_(90)
{
	GetGame()->SetScoreManager(this);

	score1 = new PlayerScore(game, Vec2(WINDOW_WIDTH/2 - 60, 50));
	score2 = new PlayerScore(game, Vec2(WINDOW_WIDTH / 2 - 80, 50));
	enemyscore1 = new PlayerScore(game, Vec2(WINDOW_WIDTH / 2 + 80, 50));
	enemyscore2 = new PlayerScore(game, Vec2(WINDOW_WIDTH / 2 + 60, 50));
	number = 0;
	enemynumber = 0;

	//スコアボード表示
	auto temp1 = new Actor(game);
	temp1->SetPosition(Vec2(WINDOW_WIDTH / 2 - 70 - 44, 50));
	BGSpriteComponent* scorebg1 = new BGSpriteComponent(temp1, 45);
	scorebg1->SetScreenSize(Vec2(140, 140));
	std::vector<int > bgtexs1 = {
		game->GetTexture(L"Data/Image/UI/scorbord/scorbord_bule1.png")
	};
	scorebg1->SetBGTextures(bgtexs1);

	//スコアボード表示
	auto temp2 = new Actor(game);
	temp2->SetPosition(Vec2(WINDOW_WIDTH / 2 + 70 + 42, 50));
	BGSpriteComponent* scorebg2 = new BGSpriteComponent(temp2, 45);
	scorebg2->SetScreenSize(Vec2(140, 140));
	std::vector<int > bgtexs2 = {
		game->GetTexture(L"Data/Image/UI/scorbord/scorbord_red1.png")
	};
	scorebg2->SetBGTextures(bgtexs2);
	
	//タイマーが入る所表示
	auto temp3 = new Actor(game);
	temp3->SetPosition(Vec2(WINDOW_WIDTH / 2, 50));
	auto temp3_asc = new SpriteComponent(temp3, 49);
	temp3_asc->SetTexture(LoadTexture(L"Data/Image/UI/scorbord/time.png")
		, Vec2(64 * 2, 64 * 2), Vec2(0, 0), Vec2(1, 1));

	
	//タイマー表示
	auto timer = new Timer(game, k_fight_time_);

	auto efect = new Fight_Effects(GetGame(), Vec2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2)
		, Vec2(700, 700), 10
		, static_cast<int>(Fight_Effects::fight_effects_Motion::READY_IN));
}

void ScoreManager::UpdateActor(float delttime)
{

}

void ScoreManager::AddScore(int add)
{
	number += add;

	if (number > SCORE_MAX)
	{
		number = SCORE_MAX;
	}

	score1->AddScore(number);

	int addnumber2;

	addnumber2 = number / 10;
	score2->AddScore(addnumber2);

	//auto b = new Fight_Effects(GetGame(), Vec2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), Vec2(700, 700), 30, static_cast<int>(fight_effects_Motion::WAKU_IN));
	//auto a = new Fight_Effects(GetGame(),Vec2(WINDOW_WIDTH /2 , WINDOW_HEIGHT / 2), Vec2(700,700), 20, static_cast<int>(fight_effects_Motion::TIMEUP_IN));
}

void ScoreManager::EnemyAddScore(int add)
{
	enemynumber += add;

	if (enemynumber > SCORE_MAX)
	{
		enemynumber = SCORE_MAX;
	}

	enemyscore1->AddScore(enemynumber);

	int a;

	a = enemynumber / 10;
	enemyscore2->AddScore(a);
}
