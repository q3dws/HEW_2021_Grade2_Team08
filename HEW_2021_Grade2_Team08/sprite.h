//=============================================================================
//
// プレイヤー処理 [sprite.h]
// Author : 
//
//=============================================================================
#pragma once

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitSprite();
void UninitSprite();

void DrawSprite(int texNo, float X, float Y, float Width, float Height, float U, float V, float UW, float VH);
void DrawCenter(int tex_no, Vec2 top_left_, Vec2 texture_size_, Vec2 uv_, Vec2 uv_size);
void DrawSpriteLeftTop(int texNo, float X, float Y, float Width, float Height, float U, float V, float UW, float VH);
void DrawLeftTop(int tex_no, Vec2 top_left_, Vec2 texture_size_, Vec2 uv_, Vec2 uv_size);
void DrawSpriteColor(int texNo, float X, float Y, float Width, float Height, float U, float V, float UW, float VH, D3DXCOLOR color);
void DrawSpriteColorRotate(int texNo, float X, float Y, float Width, float Height, float U, float V, float UW, float VH, D3DXCOLOR Color, float Rot);
void DrawSpriteRotCntr(int tex_no, Vec2 topleft, Vec2 size, Vec2 uv, Vec2 uv_wh, float rot, float alfa = 1);
