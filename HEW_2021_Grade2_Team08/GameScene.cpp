#include "GameScene.h"
#include "Math.h"
#include "Actor.h"
#include "SpriteComponent.h"
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
	bg->SetScreenSize(Vec2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
	bgtexs = {
		game->GetTexture(L"Data/Image/titlelogo_2.png")
	};
	bg->SetBGTextures(bgtexs);

	temp1 = new Actor(game);
	temp1->SetPosition(Vec2(WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f + 200));
	asc = new SpriteComponent(temp1, 21);
	asc->SetTexture(game->GetTexture(L"Data/Image/title_start2.png"), Vec2(WINDOW_WIDTH * 0.25f, WINDOW_HEIGHT * 0.25f), Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));
	fadecheck_ = true;

	
}
StartScene::~StartScene()
{
	delete temp;
	delete temp2;
	delete arcade;
	delete vs;
	delete tutorial;
	delete exit;
	delete cursor;
}
void StartScene::Initialize(Game* game)
{
	texsize_ = (Vec2(600, 600));

	texpos = Vec2(100, WINDOW_HEIGHT / 2 + 20);
	texbar = 150;
}

void StartScene::HandleInput(Game* game)
{
	if (GetKeyboardTrigger(DIK_S) && checkspece == true)
	{
		++modecursor;
		if (modecursor >= 4)
		{
			modecursor = 4;
		}
	}
	if (GetKeyboardTrigger(DIK_W) && checkspece == true)
	{
		--modecursor;
		if (modecursor < 0)
		{
			modecursor = 0;
		}
	}

	if (GetKeyboardRelease(DIK_SPACE) && checkspece == true)
	{
		game->GetGSM()->ChangeState(new CharaselctScene(game));
	}
	if (GetKeyboardRelease(DIK_SPACE)&& checkspece == false)
	{
		//game->GetGSM()->ChangeState(new CharaselctScene(game));
		delete temp1;

		//モード選択
		//Arcadeモード
		arcade = new Actor(game);
		arcade->SetPosition(Vec2(texpos.x_, texpos.y_));
		arcadetex = new SpriteComponent(arcade, 21);
		arcadetex->SetTexture(game->GetTexture(L"Data/Image/Scene/chara_select_UIgirl1.png"), texsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));

		//VSモード
		vs = new Actor(game);
		vs->SetPosition(Vec2(texpos.x_, texpos.y_ + texbar * 1));
		vstex = new SpriteComponent(vs, 21);
		vstex->SetTexture(game->GetTexture(L"Data/Image/Scene/chara_select_UIgirl1.png"), texsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));

		//Tutorialモード
		tutorial = new Actor(game);
		tutorial->SetPosition(Vec2(texpos.x_, texpos.y_ + texbar * 2));
		tutorialtex = new SpriteComponent(tutorial, 21);
		tutorialtex->SetTexture(game->GetTexture(L"Data/Image/Scene/chara_select_UIgirl1.png"), texsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));

		//Exitモード
		exit = new Actor(game);
		exit->SetPosition(Vec2(texpos.x_, texpos.y_ + texbar * 3));
		exittex = new SpriteComponent(exit, 21);
		exittex->SetTexture(game->GetTexture(L"Data/Image/Scene/chara_select_UIgirl1.png"), texsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));

		checkspece = true;

		//カーソル
		cursor = new Actor(game);
		cursor->SetPosition(Vec2(texpos.x_, texpos.y_));
		cursortex = new SpriteComponent(cursor, 23);
		cursortex->SetTexture(game->GetTexture(L"Data/Image/Scene/yukimemori_tte.png"), Vec2(50.0f, 50.0f), Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));

	}

	
}

void StartScene::Update(Game* game)
{
	if (checkspece == false)
	{
		if (asc->alfa_ <= 0.0f)
		{
			fadecheck_ = false;
		}
		if (asc->alfa_ >= 1.0f)
		{
			fadecheck_ = true;
		}

		if (fadecheck_)
		{
			asc->alfa_ -= 0.3 * 0.05;
		}
		else
		{
			asc->alfa_ += 0.3 * 0.05;
		}
		asc->SetAlfa(asc->alfa_);

	}
	else
	{
		switch (modecursor)
		{
		case 0:
			//Arcadeモード
			cursor->SetPosition(Vec2(texpos.x_, texpos.y_ + 50));
			break;
		case 1:
			//VSモード
			cursor->SetPosition(Vec2(texpos.x_, texpos.y_ + 100));
			break;
		case 2:
			//Tutorialモード
			cursor->SetPosition(Vec2(texpos.x_, texpos.y_ + 150));
			break;
		case 3:
			//Exitモード
			cursor->SetPosition(Vec2(texpos.x_, texpos.y_ + 200));
			break;
		default:
			break;
		}
	}
}

/////////////////////////////////////////////////////////
//  BattleScene                                        //
/////////////////////////////////////////////////////////
BattleScene::BattleScene(Game* game)
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
	sbg->SetScreenSize(Vec2(STAGESCREEN_X, STAGESCREEN_Y));
	std::vector<int> sbgtexs = {
		game->GetTexture(L"Data/Image/Stage_normal_edited.png")
	};

	sbg->SetBGTextures(sbgtexs);

	//auto Scoretest = new ScoreManager(game);

	stg = new Stage(game);
	player = new Player(game, stg);

	

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

