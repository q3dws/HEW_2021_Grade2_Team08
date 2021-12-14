#include "Icicle.h"
#include "Texture.h"
#include "SpriteComponent.h"

Icicle::Icicle(Game* game, int icicle_index)
	:Actor(game)
	,texno_(icicle_index)
{
	texno_ = LoadTexture(L"Data/Image/13558.png");

	Icicle_Actor_ = new Actor(game);

	Icicle_Sprite_ = new SpriteComponent(this, 120);
	Icicle_Sprite_->SetTexture(texno_, Vec2(ICICLE_SIZE, ICICLE_SIZE), Vec2(0, 0), Vec2(1, 1));

}

void Icicle::UpdateActor(float deltatime)
{	
	SetPosition(Vec2(GetPosition().x_, GetPosition().y_ + move_));
}


