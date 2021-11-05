#pragma once
#ifndef STATECONTEXT_H
#define STATECONTEXT_H
#include "State.h"

template<class T>
class StateContext
{
public:
    StateContext(T* owner)
        :p_owner_(owner)
        , p_current_state_(nullptr)
        , p_previous_state_(nullptr)
        , p_global_state_(nullptr){}
    virtual ~StateContext(){}

    void HandleInput()
    {
        if (p_global_state_) p_global_state_->HandleInput(p_owner_);
        if (p_current_state_) p_current_state_->HandleInput(p_owner_);
    }

    void Update() const
    {
        if (p_global_state_) p_global_state_->Update(p_owner_);
        if (p_current_state_) p_current_state_->Update(p_owner_);
    }

    void ChangeState(State<T>* p_new_state)
    {
        //p_previous_state_ = p_current_state_;
        //p_current_state_->Exit(p_owner_);
        if(p_current_state_) delete p_current_state_;
        p_current_state_ = p_new_state;
    }

    void RevertToPreviousState()
    {
        ChangeState(p_previous_state_);
    }

    bool IsInState(const State<T>& st) const
    {
        return typeid(*p_current_state_) == typeid(st);
    }

    void SetCurrentState(State<T>* s) { p_current_state_ = s; }
    void SetPreviousState(State<T>* s) { p_previous_state_ = s; }
    void SetGlobalState(State<T>* s) { p_global_state_ = s; }
private:
    T* p_owner_;
    State<T>* p_current_state_;
    State<T>* p_previous_state_;
    State<T>* p_global_state_;
};
#endif // !STATEMACHINE_H