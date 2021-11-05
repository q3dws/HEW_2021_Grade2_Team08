#pragma once
#ifndef COMPONENT_H
#define COMPONENT_H
class Component
{
public:
    Component(class Actor* owner, int update_order);
    virtual ~Component();
    virtual void Update(float deltatime);
    int GetUpdateOrder() const { return update_order_; }
protected:
    class Actor* owner_;
    int update_order_;
};
#endif // !COMPONENT_H
