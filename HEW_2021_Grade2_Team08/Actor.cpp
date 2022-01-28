#include <algorithm>
#include "Actor.h"
#include "Game.h"
#include "Component.h"


Actor::Actor(Game* game)
    :position_(Vec2())
    , scale_(1.0f)
    , rotation_()
    , game_(game)
    , state_(Idle)
    , position_index_(-1)
    , collision_()
{
    game->AddActor(this);
}

Actor::~Actor()
{
    game_->RemoveActor(this);
    while (!components_.empty())
        delete components_.back();

}

void Actor::Update(float deltatime)
{
    UpdateComponents(deltatime);
    UpdateActor(deltatime);
}

void Actor::UpdateComponents(float deltatime)
{
    for (auto comp : components_)
        comp->Update(deltatime);
}

void Actor::UpdateActor(float deltatime)
{
}

void Actor::AddComponent(Component* component)
{
    int myOrder = component->GetUpdateOrder();
    auto iter = components_.begin();
    for (; iter != components_.end(); ++iter)
        if (myOrder < (*iter)->GetUpdateOrder())
            break;

    components_.insert(iter, component);
}

void Actor::RemoveComponent(Component* component)
{
    auto iter = std::find(components_.begin(), components_.end(), component);
    if (iter != components_.end())
        components_.erase(iter);
}
#if 0
bool CollisionRC(Actor const& const rect, Actor const& const center)
{
    if (rect->GetPosIndex() == center->GetPosIndex())
    {
        float axmin = rect->GetCollision().topleft_.x_;
        float axmax = rect->GetCollision().bottomright_.x_;
        float aymin = rect->GetCollision().topleft_.y_;
        float aymax = rect->GetCollision().bottomright_.y_;
        Vec2  bcenter = center->GetCollision().center_;
        if (axmax > bcenter.x_ && axmin < bcenter.x_)
            if (aymax > bcenter.y_ && aymin < bcenter.y_)
                return true;
        return false;
    }
}
#else

#endif