#include "MoveComponent.h"
#include "Math.h"
#include "Actor.h"
void MoveComponent::Update(float delta_time)
{
    if (!NearZero(angular_speed_))
    {
        float rot = owner_->GetRotation();
        rot += angular_speed_ * delta_time;
        owner_->SetRotation(rot);
    }

    if (!NearZero(forward_speed_))
    {
        Vec2 pos = owner_->GetPosition();
        pos += owner_->GetForward() * forward_speed_ * delta_time;
    }
}
