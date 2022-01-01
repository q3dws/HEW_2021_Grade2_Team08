#pragma once
#include "Actor.h"
#include "Game.h"
#include "Texture.h"
#include <vector>
#include "Stage.h"
#include "AnimSpriteComponent.h"
#include "SpriteComponent.h"
#include "Player.h"

//スキルのアイコンを表示、ならびに管理するクラス
//作成者　君島朝日
// 作成日　2021/12/08
//

class Skillicon :
    public Actor
{
private:
    std::vector<class Icon*> icons_; //メモリオブジェクトを作る動的配列
    const int k_snowcost_[4];           //スキルのコスト

    const int k_Skillicon_tex_[18];                         //Skilliconのテクスチャ

    const int k_Skillicon_num_;                              //Skilliconの数
    Vec2 k_Skillicon_pos_;                            //一番左のSkilliconの位置
    const Vec2 k_Skillicon_size_;                           //Skilliconの大きさ
    const float k_Skillicon_var_;                            //Skillicon間の幅

    const int k_who_player_;
    const bool k_Is_player_;
public:
    Skillicon(Game* game, bool Is_player,int who, int skillcost0, int skillcost1, int skillcost2, int skillcost3);
    ~Skillicon();
    void UpdateActor(float deltatime) override;
    void SetSnownum(int snownum);
};


//アイコン側のクラス
class Icon :
    public Actor
{
public:
    Icon(class Game* game, Vec2 pos, Vec2 size, int layer, int lighttex, int darktex);
    ~Icon();
    void UpdateActor(float delta_time) override;
    
   // void Icon_texchange(int texnum);
    void Icon_inset();
    void Icon_outset();
private:
    class SpriteComponent* Icon_asc_;
    
    const Vec2 k_Icon_size_;
    const Vec2 k_Icon_pos_;
    const int k_Icon_layer_;

    //int Icon_state_;
    
    const int k_Icon_tex_[2];                       //Iconのテクスチャ

    enum class Icon_frame_num : int
    {
        light = 1,
        dark = 1,
        LEAVE = 4,
    };

    enum class Icon_Motion :int
    {
        light,     //光る
        dark,     //光らない
    };

};
