#pragma once
#include "main.h"
#include <windows.h>
#include "xaudio2.h"


bool InitSound(HWND hWnd);
void UninitSound(void);

int LoadSound(wchar_t const* pFilename);
void PlaySound(int index, int loopCount);//255(-1)�����[�v�w�肷��Ɩ������[�v
void StopSound(int index);
void StopSoundAll(void);
void SetVolume(int index, float vol);