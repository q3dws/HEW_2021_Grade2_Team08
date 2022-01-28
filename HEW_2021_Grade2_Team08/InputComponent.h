#pragma once
#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H
#include "MoveComponent.h"
class InputComponent :
    public MoveComponent
{
public:
    InputComponent(class Actor* owner);
    //void ProcessInput(const 
protected:
};
#endif // !INPUTCOMPONENT_H