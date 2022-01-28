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
#include "ResultScene.h"
#include "VSResultScene.h"
#include "FirstStage.h"
#include "SecondStage.h"
#include "ThirdStage.h"
#include "Ponytail.h"
#include "Robot.h"
#include "Witch.h"
#include "ScoopLady.h"
#include <algorithm>
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
    StopSound(BGM_);
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
	BGM_ = LoadSound(L"Data/BGM/title.wav");
	SetVolume(BGM_, 0.15);
    SE_ = LoadSound(L"Data/SE/Scene/titlepush.wav");
	SetVolume(SE_, 0.6);
	PlaySound(BGM_, -1);
}

void StartScene::HandleInput(Game* game)
{
	
	if (GetKeyboardRelease(DIK_SPACE))
	{
        PlaySound(SE_, 0);
		game->GetGSM()->ChangeState(new ModeselectScene(game));
		//game->GetGSM()->ChangeState(new BattleScene(game, 6, 0, 1, 0));
		//game->GetGSM()->ChangeState(new ResultScene(game, 24,24 , 5, 0,0));
		//game->GetGSM()->ChangeState(new VSResultScene(game, 24, 24));
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
BattleScene::BattleScene(Game* game, int mode, int player1, int player2, int score)
{
    game_ = game;
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
	//auto temp = new Actor(game);
	//temp->SetPosition(Vec2(WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f));
	//BGSpriteComponent* bg = new BGSpriteComponent(temp, 10);
	//bg->SetScreenSize(Vec2(WINDOW_WIDTH, WINDOW_HEIGHT));
	//std::vector<int > bgtexs = {
	//	game->GetTexture(L"Data/Image/BackGround_2.png")
	//};
	//bg->SetBGTextures(bgtexs);

	/*auto bgsta = new Actor(game);
	bgsta->SetPosition(Vec2(WINDOW_WIDTH * 0.5, STAGE_HEIGHT));
	BGSpriteComponent* sbg = new BGSpriteComponent(temp, 11);
	sbg = new BGSpriteComponent(bgsta, 15);
	sbg->SetScreenSize(Vec2(WINDOW_WIDTH, WINDOW_HEIGHT));
	std::vector<int> sbgtexs = {
		game->GetTexture(L"Data/Image/stage1.png")
	};

	sbg->SetBGTextures(sbgtexs);*/
    inhertscore_ = score;
	mode_ = mode;
	if (mode_ == static_cast<int>(ModeselectScene::celectMODE::ARCADE))
		mode_ = static_cast<int>(ModeselectScene::celectMODE::STAGE1);

	//プレイヤー1生成
	p_ScoreManager = new ScoreManager(game);
	player1_num_ = player1;

	StopSoundAll();
	BGM_ = LoadSound(L"Data/BGM/battle.wav");

	switch (mode_)
	{
	case static_cast<int>(ModeselectScene::celectMODE::STAGE1):
		stg = new FirstStage(game);
		Setplayer(game, player1, true);
        game->SetThreeEnemy(player1);
		//敵AI生成
        enemy_ = RetEnemy();
		break;
	case static_cast<int>(ModeselectScene::celectMODE::STAGE2):
		//ステージ2生成
        stg = new SecondStage(game);
		Setplayer(game, player1, true);
		//敵AI生成
        enemy_ = RetEnemy();
		break;
	case static_cast<int>(ModeselectScene::celectMODE::STAGE3):
		StopSoundAll();
		BGM_ = LoadSound(L"Data/BGM/lastbattle.wav");
		//ステージ3生成
        stg = new ThirdStage(game);
		Setplayer(game, player1, true);
		//敵AI生成
        enemy_ = RetEnemy();
		break;
	case static_cast<int>(ModeselectScene::celectMODE::VERSUS):
		stg = new FirstStage(game);
		Setplayer(game, player1, true);
		Setplayer(game, player2, false);
		break;
	default:
		break;
	}

	SetVolume(BGM_, 0.15);
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
	p_ScoreManager->SetState(Actor::State::Dead);
    StopSound(BGM_);
	switch (mode_)
	{
	case static_cast<int>(ModeselectScene::celectMODE::STAGE1):
		player->SetState(Actor::State::Dead);
        enemy_->SetState(Actor::State::Dead);
		stg->SetState(Actor::State::Dead);
		//敵AI生成
		break;
	case static_cast<int>(ModeselectScene::celectMODE::STAGE2):
		//ステージ2生成
		player->SetState(Actor::State::Dead);
        enemy_->SetState(Actor::State::Dead);
        stg->SetState(Actor::State::Dead);
		//敵AI生成
		break;
	case static_cast<int>(ModeselectScene::celectMODE::STAGE3):
		player->SetState(Actor::State::Dead);
        enemy_->SetState(Actor::State::Dead);
        stg->SetState(Actor::State::Dead);
        StopSoundAll();
		break;
	case static_cast<int>(ModeselectScene::celectMODE::VERSUS):
		player->SetState(Actor::State::Dead);
		player2->SetState(Actor::State::Dead);
		stg->SetState(Actor::State::Dead);
		break;
	default:
		break;
	}
}

void BattleScene::Initialize(Game* game)
{
}

void BattleScene::HandleInput(Game* game)
{

	
}

void BattleScene::Update(Game* game)
{
	if (p_ScoreManager->GetTimeUP())
	{
		switch (mode_)
		{
		case static_cast<int>(ModeselectScene::celectMODE::STAGE1):
			game->GetGSM()->ChangeState(new ResultScene(game, p_ScoreManager->GetPlayerScore(), p_ScoreManager->GetEnemyScore()
				, mode_, player1_num_, 0, p_ScoreManager->GetPlayerScore() + inhertscore_));
			break;
		case static_cast<int>(ModeselectScene::celectMODE::STAGE2):
			game->GetGSM()->ChangeState(new ResultScene(game, p_ScoreManager->GetPlayerScore(), p_ScoreManager->GetEnemyScore()
				, mode_, player1_num_, 0, p_ScoreManager->GetPlayerScore() + inhertscore_));
			break;
		case static_cast<int>(ModeselectScene::celectMODE::STAGE3):
			game->GetGSM()->ChangeState(new ResultScene(game, p_ScoreManager->GetPlayerScore(), p_ScoreManager->GetEnemyScore()
				, mode_, player1_num_, 0, p_ScoreManager->GetPlayerScore() + inhertscore_));
			break;
		case static_cast<int>(ModeselectScene::celectMODE::VERSUS):
			game->GetGSM()->ChangeState(new VSResultScene(game, p_ScoreManager->GetPlayerScore(), p_ScoreManager->GetEnemyScore()));
			break;
		default:
			break;
		}
	}
	
}

void BattleScene::Setplayer(Game* game, int playernum,bool isplayer)
{
	switch (playernum)
	{
	case static_cast<int>(CharaselctScene::celectCHARA::CHARAA):
		if(isplayer)
			player = new CharaA(game, stg, isplayer);
		else
			player2 = new CharaA(game, stg, isplayer);
		break;
	case static_cast<int>(CharaselctScene::celectCHARA::CHARAB):
		if (isplayer)
			player = new CharaB(game, stg, isplayer);
		else
			player2 = new CharaB(game, stg, isplayer);
		break;
	case static_cast<int>(CharaselctScene::celectCHARA::CHARAC):
		if (isplayer)
			player = new CharaC(game, stg, isplayer);
		else
			player2 = new CharaC(game, stg, isplayer);
		break;
	case static_cast<int>(CharaselctScene::celectCHARA::CHARAD):
		if (isplayer)
			player = new CharaD(game, stg, isplayer);
		else
			player2 = new CharaD(game, stg, isplayer);
		break;
	default:
		break;
	}
}

Enemy* BattleScene::RetEnemy()
{
    auto num = game_->RetEnemyStack().back();
    game_->RetEnemyStack().pop_back();
    switch (num) {
    case SCOOPLADY:return new ScoopLady(game_, stg);
    case ROBOT:return new Robot(game_, stg);
    case PONYTAIL:return new Ponytail(game_, stg);
    case WITCH:return new Witch(game_, stg);
    }
}


