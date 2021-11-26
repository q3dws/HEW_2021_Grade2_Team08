#pragma once
#include "State.h"
#include "Wall.h"
class WallStart :
    public State<Wall>
{
};

class WallActive :
    public State<Wall>
{
};

class WallDestroy :
    public State<Wall>
{
};

