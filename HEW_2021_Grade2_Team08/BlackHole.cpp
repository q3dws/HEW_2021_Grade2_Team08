#include "BlackHole.h"
#include "BlackHoleOut.h"
#include "Texture.h"
#include "Snow.h"

BlackHole::BlackHole(Game* game , ThirdStage* psta)
	:Actor(game), pStage_(psta)
{
	texno_ = LoadTexture(L"Data/Image/black hole_anime.png");
	/*BH_Sprite = new SpriteComponent(this, 110);
	BH_Sprite->SetTexture(texno_, Vec2(100, 100), Vec2(0, 0), Vec2(1, 1));*/

	BH_AnimSprite = new AnimSpriteComponent(this, 110);
	BH_AnimSprite->SetAnimTextures(texno_, Vec2(BLACKHOLE_SIZE, BLACKHOLE_SIZE), 8, 5);
	SetPosition(Vec2(BH_POS_X, BH_POS_Y));
}

void BlackHole::UpdateActor(float deltatime)
{
	timer_++;

	if(pStage_->GetSnows())
		pStage_-> AllSnowDelete();

	if (timer_ > BASEUSETIME)
	{
		SetState(Dead);
		pBHO = new BlackHoleOut(GetGame());
	}
}
