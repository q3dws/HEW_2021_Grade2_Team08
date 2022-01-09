#include "ScoreManager.h"
#include "Game.h"
#include "Texture.h"
#include "SpriteComponent.h"
#include "BGSpriteComponent.h"

ScoreManager::ScoreManager(Game* game)
	:Actor(game)
	,SCORE_MAX(99)
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
	auto temp3_asc = new SpriteComponent(temp3, 150);
	temp3_asc->SetTexture(LoadTexture(L"Data/Image/UI/scorbord/time.png")
		, Vec2(64 * 2, 64 * 2), Vec2(0, 0), Vec2(1, 1));

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

	int a;

	a = number / 10;
	score2->AddScore(a);

	
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
