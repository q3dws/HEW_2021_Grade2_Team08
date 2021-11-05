#pragma once
#ifndef STATE_H
#define STATE_H
template <class T>
class State
{
public:
    virtual ~State() = default;

    virtual void Initialize(T*) = 0;
    virtual void HandleInput(T*) = 0;
    virtual void Update(T*) = 0;
    //virtual void Draw(T*) = 0;
};
#endif // !STATE_H

