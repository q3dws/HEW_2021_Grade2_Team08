#pragma once
#ifndef SKILL_H
#include "Actor.h"
#include "StateContext.h"
#include <memory>
class Skill :
    public Actor
{
public:
    Skill(Game* game)
        :Actor(game)
        ,cost_()
    {
        skill_context_ = new StateContext<Skill>(this);
    }
protected:
    void SetCost(float cost) { cost_ = cost; }
    float GetCost() { return cost_; }
    StateContext<Skill> * GetSkillContext() const { return skill_context_; }
private:
    float cost_;
    StateContext<Skill> * skill_context_ = nullptr;
};
#endif // !SKILL_H


