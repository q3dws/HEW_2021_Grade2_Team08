#include "GameScene.h"
#include "Math.h"
#include "Actor.h"
#include "BGSpriteComponent.h"
#include "main.h"
#include "Game.h"
#include "Texture.h"
#include "sprite.h"
#include "input.h"
#include "AnimationTestObj.h"
#include "TestBullet.h"
#include "Player.h"
#include "Snow.h"
#include "Stage.h"
#include "Score.h"
#include "ScoreManager.h"
#include "Icicle.h"
#include "CharaA.h"
#include "CharaB.h"
#include "CharaC.h"
#include "CharaD.h"
#include "enemytestB.h"
#include "ModeselectScene.h"
#include "sound.h"

/////////////////////////////////////////////////////////
//  StartScene                                         //
/////////////////////////////////////////////////////////
StartScene::StartScene(Game* game)

{
	Initialize(game);
	temp = new Actor(game);
	temp->SetPosition(Vec2(WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f));
	// Create the "far back" background
	BGSpriteComponent* bg = new BGSpriteComponent(temp, 10);
	bg->SetScreenSize(Vec2(WINDOW_WIDTH, WINDOW_HEIGHT));
	std::vector<int > bgtexs = {
		game->GetTexture(L"Data/Image/titleBG1.png"),
		//game->GetTexture(L"Data/Image/Farback02.png")
	};
	bg->SetBGTextures(bgtexs);
	//bg->SetScrollSpeed(-100.0f);


	temp2 = new Actor(game);
	temp2->SetPosition(Vec2(WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f - 100));
	bg = new BGSpriteComponent(temp2, 20);
	bg->SetScreenSize(Vec2(512 * 2, 128 * 2));
	bgtexs = {
		game->GetTexture(L"Data/Image/titlelogo_2.png")
	};
	bg->SetBGTextures(bgtexs);

	temp1 = new Actor(game);
	temp1->SetPosition(Vec2(WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f + 150));
	asc = new SpriteComponent(temp1, 21);
	asc->SetTexture(game->GetTexture(L"Data/Image/title_start2.png")
		, Vec2(256 * 2, 64 * 2), Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));
	fadecheck_ = true;

	
}
StartScene::~StartScene()
{
	delete temp;
	delete temp1;
	delete temp2;
	
}
void StartScene::Initialize(Game* game)
{
	texsize_ = (Vec2(600, 600));

	texpos = Vec2(100, WINDOW_HEIGHT / 2 + 20);
	texbar = 150;

	startalfa_ = 1.0f;
	StopSoundAll();
	BGM_ = LoadSound(L"Data/BGM/title.wav");
	PlaySound(BGM_, -1);
}

void StartScene::HandleInput(Game* game)
{
	
	if (GetKeyboardRelease(DIK_SPACE))
	{
		game->GetGSM()->ChangeState(new ModeselectScene(game));
		//game->GetGSM()->ChangeState(new BattleScene(game, 0, 0, 1));
	}
	
	
}

void StartScene::Update(Game* game)
{

	if (startalfa_ <= 0.0f)
	{
		fadecheck_ = false;
	}
	if (startalfa_ >= 1.0f)
	{
		fadecheck_ = true;
	}

	if (fadecheck_)
	{
		startalfa_ -= 0.3 * 0.05;
	}
	else
	{
		startalfa_ += 0.3 * 0.05;
	}
	asc->SetAlfa(startalfa_);


}


/////////////////////////////////////////////////////////
//  BattleScene                                        //
/////////////////////////////////////////////////////////
BattleScene::BattleScene(Game* game, int mode, int player1, int player2)
{
	
	Initialize(game);
	/*auto temp = new Actor(game);
	temp->SetPosition(Vec2(WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f));
	BGSpriteComponent* bg = new BGSpriteComponent(temp, 10);
	bg->SetScreenSize(Vec2(WINDOW_WIDTH, WINDOW_HEIGHT));
	std::vector<int > bgtexs = {
		game->GetTexture(L"Data/Image/BattleBG_Test.png")
	};
	bg->SetBGTextures(bgtexs);*/
	/*bg = new BGSpriteComponent(temp, 15);
	bg->SetScreenSize(Vec2(WINDOW_WIDTH, WINDOW_HEIGHT));
	bgtexs = {
		game->GetTexture(L"Data/Image/BattleStage_test.png")
	};
	bg->SetBGTextures(bgtexs);*/

	//obj = new AnimationTestObj(game);
	//obj->SetPosition(Vec2(300, WINDOW_HEIGHT - 240));
	auto temp = new Actor(game);
	temp->SetPosition(Vec2(WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f));
	BGSpriteComponent* bg = new BGSpriteComponent(temp, 10);
	bg->SetScreenSize(Vec2(WINDOW_WIDTH, WINDOW_HEIGHT));
	std::vector<int > bgtexs = {
		game->GetTexture(L"Data/Image/BackGround_2.png")
	};
	bg->SetBGTextures(bgtexs);

	auto bgsta = new Actor(game);
	bgsta->SetPosition(Vec2(WINDOW_WIDTH * 0.5, STAGE_HEIGHT));
	BGSpriteComponent* sbg = new BGSpriteComponent(temp, 11);
	sbg = new BGSpriteComponent(bgsta, 15);
	sbg->SetScreenSize(Vec2(WINDOW_WIDTH, WINDOW_HEIGHT));
	std::vector<int> sbgtexs = {
		game->GetTexture(L"Data/Image/stage1.png")
	};

	sbg->SetBGTextures(sbgtexs);

	
	stg = new Stage(game);
	
	p_ScoreManager = new ScoreManager(game);

	

	switch (player1)
	{
	case static_cast<int>(CharaselctScene::celectCHARA::CHARAA):
		player = new CharaA(game, stg, true);
		break;
	case static_cast<int>(CharaselctScene::celectCHARA::CHARAB):
		player = new CharaB(game, stg, true);
		break;
	case static_cast<int>(CharaselctScene::celectCHARA::CHARAC):
		player = new CharaC(game, stg, true);
		break;
	case static_cast<int>(CharaselctScene::celectCHARA::CHARAD):
		player = new CharaD(game, stg, true);
		break;
	default:
		break;
	}

	switch (player2)
	{
	case static_cast<int>(CharaselctScene::celectCHARA::CHARAA):
		player = new CharaA(game, stg, false);
		break;
	case static_cast<int>(CharaselctScene::celectCHARA::CHARAB):
		player = new CharaB(game, stg, false);
		break;
	case static_cast<int>(CharaselctScene::celectCHARA::CHARAC):
		player = new CharaC(game, stg, false);
		break;
	case static_cast<int>(CharaselctScene::celectCHARA::CHARAD):
		player = new CharaD(game, stg, false);
		break;
	default:
		//player = new CharaA(game, stg, false);
		break;
	}


	mode_ = mode;

	StopSoundAll();
	BGM_ = LoadSound(L"Data/BGM/battle.wav");
	
	PlaySound(BGM_, -1);

	//player = new CharaA(game, stg, true);
	//player = new CharaA(game, stg, false);
	//player = new CharaB(game, stg, true);
	//player = new CharaB(game, stg, false);
	//player = new CharaC(game, stg,true);
	//player = new CharaC(game, stg, false);
	//player = new CharaD(game, stg, true);
	//player = new CharaD(game, stg, false);
	//player = new EnemytestB(game, stg);

	//player = new CharaA(game, stg, true);
}

BattleScene::~BattleScene()
{
}

void BattleScene::Initialize(Game* game)
{
	
}

void BattleScene::HandleInput(Game* game)
{

	
}

void BattleScene::Update(Game* game)
{

}