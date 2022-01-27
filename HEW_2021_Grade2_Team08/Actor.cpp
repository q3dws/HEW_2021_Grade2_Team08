#include <algorithm>
#include "Actor.h"
#include "Game.h"
#include "Component.h"


Actor::Actor(Game* game)
    :position_(Vec2())
    , scale_(1.0f)
    ,rotation_()
    ,game_(game)
    ,state_(Active)
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
