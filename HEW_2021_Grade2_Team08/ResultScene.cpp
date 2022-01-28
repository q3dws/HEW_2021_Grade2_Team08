#include "ResultScene.h"
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
#include "Fight_Effects.h"
/////////////////////////////////////////////////////////
//  ResultScene                                         //
/////////////////////////////////////////////////////////
ResultScene::ResultScene(Game* game, int score, int enemyscore, int mode, int player1, int player2)
{
	Initialize(game);

    score_ = score;
	mode_ = mode;
	p1_ = player1;
	p2_ = player2;

	temp = new Actor(game);
	temp->SetPosition(Vec2(WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f));
	// Create the "far back" background
	BGSpriteComponent* bg = new BGSpriteComponent(temp, 10);
	bg->SetScreenSize(Vec2(WINDOW_WIDTH, WINDOW_HEIGHT));
	std::vector<int > bgtexs = {
		game->GetTexture(L"Data/Image/Scene/chara_select/chara_select_BG3.png"),
		//game->GetTexture(L"Data/Image/Farback02.png")
	};
	bg->SetBGTextures(bgtexs);
	//bg->SetScrollSpeed(-100.0f);

	

	Vec2 scorelogopos = Vec2(WINDOW_WIDTH / 2 - 150, WINDOW_HEIGHT / 2 + 100);

	waku_ =  new Fight_Effects(game, Vec2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 150)
		, Vec2(700, 700), 10
		, static_cast<int>(Fight_Effects::fight_effects_Motion::WAKU_IN));

	win_ = false;

	if (score > enemyscore)
	{
		if (mode_ != static_cast<int>(ModeselectScene::celectMODE::STAGE3))
			youwinlogo_ = new Fight_Effects(game, Vec2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 150)
				, Vec2(700, 700), 10
				, static_cast<int>(Fight_Effects::fight_effects_Motion::WIN_ANIM));
		else
		{
			youwinlogo_ = new Fight_Effects(game, Vec2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 150)
				, Vec2(700, 700), 10
				, static_cast<int>(Fight_Effects::fight_effects_Motion::CLEAR_ANIM));
		}
		win_ = true;
	}
	else if(score == enemyscore)
		youwinlogo_ = new Fight_Effects(game, Vec2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 150)
			, Vec2(700, 700), 10
			, static_cast<int>(Fight_Effects::fight_effects_Motion::DRAW_IN));
	else
		youwinlogo_ = new Fight_Effects(game, Vec2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 150)
			, Vec2(700, 700), 10
			, static_cast<int>(Fight_Effects::fight_effects_Motion::LOSE_ANIM));
	
	

	scorelogo_ = new Fight_Effects(game, scorelogopos
		, Vec2(500, 500), 10
		, static_cast<int>(Fight_Effects::fight_effects_Motion::SCORE));

	Vec2 difitsize = Vec2(150, 150);

	digit_ = new PlayerScore(game, Vec2(scorelogopos.x_ +  430, scorelogopos.y_), difitsize);
	second_digit_ = new PlayerScore(game, Vec2(scorelogopos.x_ + 350, scorelogopos.y_), difitsize);
	third_digit_ = new PlayerScore(game, Vec2(scorelogopos.x_ + 270, scorelogopos.y_), difitsize);

	int a = (score % 10);
	digit_->AddScore(a);

	int b = score / 10;
	second_digit_->AddScore(b);

	int c = (score / 100);
	third_digit_->AddScore(c);
}
ResultScene::~ResultScene()
{
	temp->SetState(Actor::State::Dead);
	
	youwinlogo_->SetState(Actor::State::Dead);
	scorelogo_->SetState(Actor::State::Dead);
	digit_->SetState(Actor::State::Dead);
	second_digit_->SetState(Actor::State::Dead);
	third_digit_->SetState(Actor::State::Dead);
	waku_->SetState(Actor::State::Dead);
}
void ResultScene::Initialize(Game* game)
{
	iconsize_ = (Vec2(300, 300));

	charapos = Vec2(150, WINDOW_HEIGHT / 2 + 30);
	bar = 330;

	charaUIsize = Vec2(50, 50);
	charaUIpos = Vec2(WINDOW_WIDTH - charaUIsize.x_ / 2, charapos.y_);
	exitsize_ = Vec2(150, 150);
}

void ResultScene::HandleInput(Game* game)
{
	if (GetKeyboardRelease(DIK_SPACE))
	{
		if(mode_ != static_cast<int>(ModeselectScene::celectMODE::STAGE3) && win_ == true)
			game->GetGSM()->ChangeState(new BattleScene(game, mode_ + 1, p1_, p2_, score_));
		else
			game->GetGSM()->ChangeState(new ModeselectScene(game));

		//game->GetGSM()->ChangeState(new BattleScene(game, 0, 0, 1));


	}
	
}

void ResultScene::Update(Game* game)
{
	
}


