#pragma once


#include "renderer.h"

int LoadTexture(wchar_t const * fileName);
void UninitTexture(void);

ID3D11ShaderResourceView** GetTexture(int index);