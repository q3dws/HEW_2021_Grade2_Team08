#pragma once
#ifndef MOVECOMPONENT_H
#define MOVECOMPONENT_H 
#include "Component.h"
class MoveComponent :
    public Component
{
    MoveComponent(class Actor* owner, int update_order = 10);

    void Update(float delta_time) override;

    float GetAngularSpeed(           ) const { return angular_speed_; }
    void  SetAngularSpeed(float speed)       { angular_speed_ = speed; }
    float GetForwardSpeed(           ) const { return forward_speed_; }
    void  SetForwardSpeed(float speed)       { forward_speed_ = speed; }
private:
    float angular_speed_;
    float forward_speed_;
};
#endif // !MOVECOMPONENT_H



