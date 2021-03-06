#include "Math.h"
#include "Actor.h"
const Vec2 Vec2::Zero(0.0f, 0.0f);
bool Probability(double prob)
{
    std::random_device rnd;
    std::mt19937 mt(rnd());
    if (static_cast<double>(mt()) / std::mt19937::_Max < prob * 0.01)
        return true;
    else
        return false;
}
//bool CollisionRC(Rect const& const rect, Rect const& const center, int rindex, int lindex)
//{
//    if (rindex == lindex)
//    {
//        float axmin = rect.topleft_.x_;
//        float axmax = rect.bottomright_.x_;
//        float aymin = rect.topleft_.y_;
//        float aymax = rect.bottomright_.y_;
//        Vec2  bcenter = center.center_;
//        if (axmax > bcenter.x_ && axmin < bcenter.x_)
//            if (aymax > bcenter.y_ && aymin < bcenter.y_)
//                return true;
//    }
//    return false;
//}
bool CollisionRC(Actor const* const rect, Actor const* const center)
{
#if 0
    if (rect->GetPosIndex() == center->GetPosIndex())
    {
        // float axmin = rect->GetCollision().topleft_.x_;
        // float axmax = rect->GetCollision().bottomright_.x_;
        // float aymin = rect->GetCollision().topleft_.y_;
        // float aymax = rect->GetCollision().bottomright_.y_;
        // Vec2  bcenter = center->GetCollision().center_;
        // if (axmax > bcenter.x_ && axmin < bcenter.x_)
        //     if (aymax > bcenter.y_ && aymin < bcenter.y_)
        //         return true;
        if (rect->GetCollision().bottomright_.x_ > center->GetCollision().center_.x_ && rect->GetCollision().topleft_.x_ < center->GetCollision().center_.x_)
            if (rect->GetCollision().bottomright_.y_ > center->GetCollision().center_.y_ && rect->GetCollision().topleft_.y_ < center->GetCollision().center_.y_)
                return true;
    }
#endif

    if (
        rect->GetPosIndex() == center->GetPosIndex() &&
        rect->GetCollision().bottomright_.x_ > center->GetCollision().center_.x_ &&
        rect->GetCollision().topleft_.x_      < center->GetCollision().center_.x_ &&
        rect->GetCollision().bottomright_.y_  > center->GetCollision().center_.y_ &&
        rect->GetCollision().topleft_.y_ < center->GetCollision().center_.y_)
        return true;
    return false;
}

bool CollisionRR(Actor const* const rect, Actor const* const center)
{
    if (
        rect->GetPosIndex() == center->GetPosIndex() &&
        rect->GetCollision().bottomright_.x_ > center->GetCollision().topleft_.x_ &&
        rect->GetCollision().topleft_.x_      < center->GetCollision().bottomright_.x_ &&
        rect->GetCollision().bottomright_.y_  > center->GetCollision().topleft_.y_ &&
        rect->GetCollision().topleft_.y_ < center->GetCollision().bottomright_.y_)
        return true;
    return false;
}


bool CollisionRC_NoInd(Actor const* const rect, Actor const* const center)
{

    if (

        rect->GetCollision().bottomright_.x_ > center->GetCollision().center_.x_ &&
        rect->GetCollision().topleft_.x_      < center->GetCollision().center_.x_ &&
        rect->GetCollision().bottomright_.y_  > center->GetCollision().center_.y_ &&
        rect->GetCollision().topleft_.y_ < center->GetCollision().center_.y_)
        return true;
    return false;
}

bool CollisionRR_NoInd(Actor const* const rect, Actor const* const center)
{
    if (
        
        rect->GetCollision().bottomright_.x_ > center->GetCollision().topleft_.x_ &&
        rect->GetCollision().topleft_.x_      < center->GetCollision().bottomright_.x_ &&
        rect->GetCollision().bottomright_.y_  > center->GetCollision().topleft_.y_ &&
        rect->GetCollision().topleft_.y_ < center->GetCollision().bottomright_.y_)
        return true;
    return false;
}

float Distance(const Vec2& l, const Vec2& r)
{
    return std::hypotf(l.x_ - r.x_, l.y_ - r.y_);
}

float Distance(Actor const* const l, Actor const* const r)
{
    return std::hypotf(
        l->GetPosition().x_ - r->GetPosition().x_,
        l->GetPosition().y_ - r->GetPosition().y_);
}