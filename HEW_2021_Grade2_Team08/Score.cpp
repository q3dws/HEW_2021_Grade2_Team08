#include "score.h"
#include "AnimSpriteComponent.h"
#include "BGSpriteComponent.h"
#include "SpriteComponent.h"
#include "input.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_WIDTH				(50)	// キャラサイズ
#define TEXTURE_HEIGHT				(50)	


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static int						g_score;
static float					g_w, g_h;


Score::Score(Game* game)
	:Actor(game)
{
	g_score = 0;	// スコアの初期化
	g_w = TEXTURE_WIDTH;
	g_h = TEXTURE_HEIGHT;

	int number = g_score;
	for (int i = 0; i < SCORE_DIGIT; i++)
	{
		/*score = new SpriteComponent(this, 50);
		score->SetTexture(game->GetTexture(L"Data/Image/number.png"),Vec2(g_w, g_h),Vec2(0.1f,1.0f),Vec2(0.1f, 1));*/

		
		// 次の桁へ
		number /= 10;
	}

	//スコアボード表示
	auto temp1 = new Actor(game);
	temp1->SetPosition(Vec2(400, 50));
	BGSpriteComponent* scorebg1 = new BGSpriteComponent(temp1, 45);
	scorebg1->SetScreenSize(Vec2(80, 80));
	std::vector<int > bgtexs1 = {
		game->GetTexture(L"Data/Image/TestTile.png")
	};
	scorebg1->SetBGTextures(bgtexs1);
	
	//スコア表示
	SetPosition(Vec2(400, 50));

	
}

void Score::UpdateActor(float deltatime)
{
	Actor::UpdateActor(deltatime);
	
	float a;

	a = g_score * 0.1f;

	delete score;
	this->RemoveComponent(score);
	score = new SpriteComponent(this, 50);
	score->SetTexture(GetGame()->GetTexture(L"Data/Image/number.png"), Vec2(g_w, g_h), Vec2(a, 1.0f), Vec2(0.1f, 1));
}

void Score::AddScore(int add)
{
	g_score += add;

	if (g_score > SCORE_MAX)
	{
		g_score = SCORE_MAX;
	}
}

Score2::Score2(Game* game):Actor(game)
{
	g_w = TEXTURE_WIDTH;
	g_h = TEXTURE_HEIGHT;

	int number = g_score;
	for (int i = 0; i < SCORE_DIGIT; i++)
	{
		auto score = new SpriteComponent(this, 50);
		score->SetTexture(game->GetTexture(L"Data/Image/number.png"), Vec2(g_w + i, g_h), Vec2(0.0f, 1.0f), Vec2(0.1f, 1));


		// 次の桁へ
		number /= 10;
	}

	//スコアボード表示
	auto temp2 = new Actor(game);
	temp2->SetPosition(Vec2(550, 50));
	BGSpriteComponent* scorebg2 = new BGSpriteComponent(temp2, 45);
	scorebg2->SetScreenSize(Vec2(80, 80));
	std::vector<int > bgtexs2 = {
		game->GetTexture(L"Data/Image/TestTile_Blue.png")
	};
	scorebg2->SetBGTextures(bgtexs2);


	//スコア表示
	SetPosition(Vec2(550, 50));

	

}
