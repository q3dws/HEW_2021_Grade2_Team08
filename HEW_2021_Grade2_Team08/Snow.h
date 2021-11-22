#ifndef SNOW_H_
#define SNOW_H_

#include "Actor.h"
#include "Game.h"

#define SNOW_SIZE_X		148
#define SNOW_SIZE_Y		135
#define SNOW_POS_X		221
#define SNOW_POS_Y		246
#define SNOW_MAX		18
#define TIMER_MAX		120

class Snow : public Actor
{
public:
	Snow(Game* game);
	void UpdateActor(float deltatime) override;
	bool GetIsSnow() const { return is_snow_; }
	void SetTimer(int timer) 
	{ 
		/*delete sprite_actor_; 
		sprite_actor_ = nullptr; */
		sprite_actor_->SetScale(0);
		timer_ = timer;
	}
	Actor* GetSActor() { return sprite_actor_; }
	int index_;

private:
	bool is_snow_;
	int timer_;
	int tex_no_;
	Actor* sprite_actor_;
	SpriteComponent* sprite_;
};

#endif // !SNOW_H_