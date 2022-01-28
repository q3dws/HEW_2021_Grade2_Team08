#include "ModeselectScene.h"
#include "CharaselectScene.h"
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
#include "sound.h"
/////////////////////////////////////////////////////////
//  ModeselectScene                                         //
/////////////////////////////////////////////////////////
ModeselectScene::ModeselectScene(Game* game)
{
	Initialize(game);
	temp = new Actor(game);
	temp->SetPosition(Vec2(WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f));
	// Create the "far back" background
	BGSpriteComponent* bg = new BGSpriteComponent(temp, 10);
	bg->SetScreenSize(Vec2(WINDOW_WIDTH, WINDOW_HEIGHT));
	std::vector<int > bgtexs = {
		game->GetTexture(L"Data/Image/Scene/gamemode/gamemode_BG.png"),
		//game->GetTexture(L"Data/Image/Farback02.png")
	};
	bg->SetBGTextures(bgtexs);
	//bg->SetScrollSpeed(-100.0f);

	//アーケード
	arcade_ = new Actor(game);
	arcade_->SetPosition(Vec2(charapos.x_, charapos.y_));
	arcade_asc_ = new SpriteComponent(arcade_, 21);

	arcade_asc_->SetTexture(game->GetTexture(L"Data/Image/Scene/gamemode/gamemode_arcade_dark.png"), iconsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));

	//UI表示
	tempUI1 = new Actor(game);
	tempUI1->SetPosition(charaUIpos);
	charaUI1 = new SpriteComponent(tempUI1, 21);
	charaUI1->SetTexture(game->GetTexture(L"Data/Image/Scene/chara_skill1.png"), charaUIsize, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));

	//対戦
	versus_ = new Actor(game);
	versus_->SetPosition(Vec2(charapos.x_ + bar, charapos.y_));
	versus_asc_ = new SpriteComponent(versus_, 21);
	versus_asc_->SetTexture(game->GetTexture(L"Data/Image/Scene/gamemode/gamemode_2p_dark.png"), iconsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));

	//チュートリアル
	tutrial_ = new Actor(game);
	tutrial_->SetPosition(Vec2(charapos.x_ + bar * 2, charapos.y_));
	tutrial_asc_ = new SpriteComponent(tutrial_, 21);
	tutrial_asc_->SetTexture(game->GetTexture(L"Data/Image/Scene/gamemode/gamemode_tutorial_dark.png"), iconsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));


	//exit
	exit_ = new Actor(game);
	exit_->SetPosition(Vec2(WINDOW_WIDTH + 12 - exitsize_.x_ / 2, WINDOW_HEIGHT + 53 - (exitsize_.y_ / 2)));
	exit_asc_ = new SpriteComponent(exit_, 21);
	exit_asc_->SetTexture(game->GetTexture(L"Data/Image/Scene/gamemode/gamemode_exit_dark.png"), exitsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));


	logo = new Actor(game);
	logo->SetPosition(Vec2(140, 25));
	logotex = new SpriteComponent(logo, 24);
	logotex->SetTexture(game->GetTexture(L"Data/Image/Scene/gamemode/gamemode.png"), Vec2(300, 300), Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));

}
ModeselectScene::~ModeselectScene()
{
    StopSound(BGM_);
	temp->SetState(Actor::State::Dead);
	arcade_->SetState(Actor::State::Dead);
	versus_->SetState(Actor::State::Dead);
	tutrial_->SetState(Actor::State::Dead);
	exit_->SetState(Actor::State::Dead);
	tempUI1->SetState(Actor::State::Dead);
	logo->SetState(Actor::State::Dead);

	StopSound(BGM_);
}
void ModeselectScene::Initialize(Game* game)
{
    SE_[0] = LoadSound(L"Data/SE/Scene/push.wav");
    SE_[1] = LoadSound(L"Data/SE/Scene/cursormove.wav");
    SE_[2] = LoadSound(L"Data/SE/Scene/exir.wav");
    BGM_ = LoadSound(L"Data/BGM/modeselect.wav");
	SetVolume(BGM_, 0.2);
	PlaySound(BGM_, -1);

	iconsize_ = (Vec2(300, 300));

	charapos = Vec2(150, WINDOW_HEIGHT / 2 + 30);
	bar = 330;

	charaUIsize = Vec2(50, 50);
	charaUIpos = Vec2(WINDOW_WIDTH - charaUIsize.x_ / 2, charapos.y_);
	exitsize_ = Vec2(150, 150);
}

void ModeselectScene::HandleInput(Game* game)
{
	if (GetKeyboardRelease(DIK_SPACE))
	{
		if (cursor == static_cast<int>(celectMODE::EXIT))
		{
            PlaySound(SE_[static_cast<int>(SE::EXIT)], 0);
			game->GetGSM()->ChangeState(new StartScene(game));
		}
		else
		{
            PlaySound(SE_[static_cast<int>(SE::PUSH)], 0);
			game->GetGSM()->ChangeState(new CharaselctScene(game, cursor));
			//game->GetGSM()->ChangeState(new BattleScene(game, 0, 0, 1));
		}
		
	}
	if (GetKeyboardTrigger(DIK_D) || GetKeyboardTrigger(DIK_RIGHT))
	{
        PlaySound(SE_[static_cast<int>(SE::CURSORMOVE)], 0);
		++cursor;
		if (cursor >= 2)
		{
			cursor = 2;
		}
	}
	if (GetKeyboardTrigger(DIK_A) || GetKeyboardTrigger(DIK_LEFT))
	{
        PlaySound(SE_[static_cast<int>(SE::CURSORMOVE)], 0);
		--cursor;
		if (cursor < 0)
		{
			cursor = 0;
		}
	}

	if (GetKeyboardTrigger(DIK_S) || GetKeyboardTrigger(DIK_DOWN))
	{
        if (cursor != static_cast<int>(celectMODE::EXIT))
        {
            PlaySound(SE_[static_cast<int>(SE::CURSORMOVE)], 0);
	        cursorbuffer_ = cursor;
        }

		cursor = static_cast<int>(celectMODE::EXIT);
	}

	if ( (GetKeyboardTrigger(DIK_W) || GetKeyboardTrigger(DIK_UP) ) && cursor == static_cast<int>(celectMODE::EXIT))
	{
        PlaySound(SE_[static_cast<int>(SE::CURSORMOVE)], 0);
		cursor = cursorbuffer_;
	}
}

void ModeselectScene::Update(Game* game)
{
	switch (cursor)
	{
	case 0:
		//キャラ1選択
		arcade_asc_->SetTexture(game->GetTexture(L"Data/Image/Scene/gamemode/gamemode_arcade.png"), iconsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));
		versus_asc_->SetTexture(game->GetTexture(L"Data/Image/Scene/gamemode/gamemode_2p_dark.png"), iconsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));
		tutrial_asc_->SetTexture(game->GetTexture(L"Data/Image/Scene/gamemode/gamemode_tutorial_dark.png"), iconsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));
		exit_asc_->SetTexture(game->GetTexture(L"Data/Image/Scene/gamemode/gamemode_exit_dark.png"), exitsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));

		charaUI1->SetTexture(game->GetTexture(L"Data/Image/Scene/chara_skill4.png"), charaUIsize, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));

		break;
	case 1:
		//versus選択
		arcade_asc_->SetTexture(game->GetTexture(L"Data/Image/Scene/gamemode/gamemode_arcade_dark.png"), iconsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));
		versus_asc_->SetTexture(game->GetTexture(L"Data/Image/Scene/gamemode/gamemode_2p.png"), iconsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));
		tutrial_asc_->SetTexture(game->GetTexture(L"Data/Image/Scene/gamemode/gamemode_tutorial_dark.png"), iconsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));
		exit_asc_->SetTexture(game->GetTexture(L"Data/Image/Scene/gamemode/gamemode_exit_dark.png"), exitsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));

		charaUI1->SetTexture(game->GetTexture(L"Data/Image/Scene/chara_skill3.png"), charaUIsize, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));

		break;
	case 2:
		//tutorial選択
		arcade_asc_->SetTexture(game->GetTexture(L"Data/Image/Scene/gamemode/gamemode_arcade_dark.png"), iconsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));
		versus_asc_->SetTexture(game->GetTexture(L"Data/Image/Scene/gamemode/gamemode_2p_dark.png"), iconsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));
		tutrial_asc_->SetTexture(game->GetTexture(L"Data/Image/Scene/gamemode/gamemode_tutorial.png"), iconsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));
		exit_asc_->SetTexture(game->GetTexture(L"Data/Image/Scene/gamemode/gamemode_exit_dark.png"), exitsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));

		charaUI1->SetTexture(game->GetTexture(L"Data/Image/Scene/chara_skill1.png"), charaUIsize, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));

		break;
	case static_cast<int>(celectMODE::EXIT):
		//exit選択
		arcade_asc_->SetTexture(game->GetTexture(L"Data/Image/Scene/gamemode/gamemode_arcade_dark.png"), iconsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));
		versus_asc_->SetTexture(game->GetTexture(L"Data/Image/Scene/gamemode/gamemode_2p_dark.png"), iconsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));
		tutrial_asc_->SetTexture(game->GetTexture(L"Data/Image/Scene/gamemode/gamemode_tutorial_dark.png"), iconsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));
		exit_asc_->SetTexture(game->GetTexture(L"Data/Image/Scene/gamemode/gamemode_exit.png"), exitsize_, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));

		charaUI1->SetTexture(game->GetTexture(L"Data/Image/Scene/chara_skill2.png"), charaUIsize, Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f));

		break;
	default:
		break;
	}
}

