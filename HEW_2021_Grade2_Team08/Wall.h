#pragma once
#include "Skill.h"
class Wall :
    public Skill
{
public:
    Wall(Game* game)
       :Skill(game)
    {}
    void UpdateActor(float deltatime) override;
private:

};

