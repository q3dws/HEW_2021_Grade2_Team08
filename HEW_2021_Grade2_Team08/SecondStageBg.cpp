#include "SecondStageBg.h"
#include "Window.h"
#include "BGSpriteComponent.h"
#include "Actor.h"
SecondStageBg::SecondStageBg(Game* game)
	:StageBg(game)
{
    bgactor_ = new Actor(game);
    bgactor_->SetPosition(Vec2(WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f));
	BGSpriteComponent* bg = new BGSpriteComponent(bgactor_, 10);
	bg->SetScreenSize(Vec2(WINDOW_WIDTH, WINDOW_HEIGHT));
	std::vector<int > bgtexs = {
		game->GetTexture(L"Data/Image/BackGround_01.png")
	};
	bg->SetBGTextures(bgtexs);
}

SecondStageBg::~SecondStageBg()
{
    bgactor_->SetState(Dead);
}
