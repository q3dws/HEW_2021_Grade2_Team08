#include "IceWall.h"



IceWall::IceWall(Game* game, Vec2 playerpos,int layer) : Skill(game)
,k_wall_pos_(Vec2(playerpos.x_ + 35,playerpos.y_ + 55))
,k_wall_size_(Vec2(150,150))
,k_wall_tex_(LoadTexture(L"Data/Image/skill/IceWall.png"))
,k_wall_layer_(layer)
{
	this->SetPosition(k_wall_pos_);
	this->wall_asc_ = new AnimSpriteComponent(this, k_wall_layer_  + 1);
	wall_asc_->SetTexture(k_wall_tex_, k_wall_size_, Vec2(0, 0), Vec2(1, 1));
}

void IceWall::UpdateActor(float deltatime)
{
	Actor::UpdateActor(deltatime);
}
