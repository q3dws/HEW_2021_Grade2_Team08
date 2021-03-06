#ifndef STAGE_H_
#define STAGE_H_

#include "Actor.h"
#include "Game.h"
#include "Snow.h"
#include "StageBg.h"//#include "Icicle.h"

#define STAGE_X  6
#define STAGE_Y  3

#if 0
class Stage : public Actor
{
public:
	Stage(class Game* game);
	void UpdateActor(float deltatime) override;
	void SetSnow(int index, int timer = 0) { snows_[index]->SetTimer(timer); }

	bool GetUseSnow(int index) { return snows_[index]->GetIsSnow(); }

private:
	int timer_ = 0;
	int icicle_index = -1;
	Snow* snows_[SNOW_MAX];
};
#else
class Stage : public Actor
{
public:
    Stage(class Game* game);
    ~Stage();
    void UpdateActor(float deltatime) override;
    virtual void SetSnow(int index, int timer = 0) { snows_[index]->SetTimer(timer); }
    virtual bool GetUseSnow(int index) { return snows_[index]->GetIsSnow(); }
    auto GetSnows() const { return snows_; }

protected:
    class Snow* snows_[SNOW_MAX];

};
#endif
#endif // !STAGE_H_