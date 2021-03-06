#include "StageBg.h"
#include "Window.h"
#include "BGSpriteComponent.h"

StageBg::StageBg(Game* game)
	:Actor(game)
{
    bgactor_ = new Actor(game);
    bgactor_->SetPosition(Vec2(WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f));
	BGSpriteComponent* bg = new BGSpriteComponent(bgactor_, 10);
	bg->SetScreenSize(Vec2(WINDOW_WIDTH, WINDOW_HEIGHT));
	std::vector<int > bgtexs = {
		game->GetTexture(L"Data/Image/BackGround_002.png")
	};
	bg->SetBGTextures(bgtexs);

	stgactor_ = new Actor(game);
    stgactor_->SetPosition(Vec2(WINDOW_WIDTH * 0.5, STAGE_HEIGHT));
	BGSpriteComponent* sbg = new BGSpriteComponent(stgactor_, 11);
	sbg = new BGSpriteComponent(stgactor_, 15);
	sbg->SetScreenSize(Vec2(WINDOW_WIDTH, WINDOW_HEIGHT));
	std::vector<int> sbgtexs = {
		game->GetTexture(L"Data/Image/stage_2.png")
	};

	sbg->SetBGTextures(sbgtexs);
}

StageBg::~StageBg()
{
    stgactor_->SetState(Dead);
    bgactor_->SetState(Dead);
}
