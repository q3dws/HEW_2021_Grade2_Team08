#pragma once
#include "Actor.h"

//TIMEUPなどの表示を行うクラス
//作成者　君島朝日
// 作成日　2021/1/18
//

class Fight_Effects :
    public Actor
{
private:

public:
    Fight_Effects(Game* game, int inittime);
    ~Fight_Effects();
    void UpdateActor(float delttime)override;
    void Fight_Effects_texchange(int texnum);
    void SetTime(float deltatime);
};

