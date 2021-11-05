#pragma once
#ifndef WINDOW_H
#define WINDOW_H
#include <Windows.h>
// �E�C���h�E�̃p�����[�^                                    //
#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 540
#define WIN_APP_NAME L"�Q�[���̑薼"
#define WIN_CLASS_NAME WIN_APP_NAME
/// ///////////////////////////////////////////////////////////

class Window
{
public:
    HRESULT InitWindow(HINSTANCE, INT, INT, INT, INT, LPCWSTR, LPCWSTR);
    LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);

    HWND hwnd_;
};

#endif // !WINDOW_H