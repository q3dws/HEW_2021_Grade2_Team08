#pragma once
#ifndef MAIN_H
#define MAIN_H
#include <Windows.h>
#include <wchar.h>
#include <memory>
#include "Game.h"
#include "Window.h"
#include "Math.h"
// DirectX11 関連
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <d3dx9.h>

#define DIRECTINPUT_VERSION 0x0800		// 警告対処
#include "dinput.h"
#include "mmsystem.h"

#pragma warning(pop)

//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************
#pragma comment (lib, "d3d11.lib")		
#pragma comment (lib, "d3dcompiler.lib")
#pragma comment (lib, "d3dx11.lib")	
#pragma comment (lib, "d3dx9.lib")	
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "dxerr.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dinput8.lib")
//*****************************************************************************

using Vector2 = D3DXVECTOR2;


//// ウインドウのパラメータ                                    //
//#define WINDOW_WIDTH 960
//#define WINDOW_HEIGHT 540
//#define WIN_APP_NAME L"ゲームの題名"
//#define WIN_CLASS_NAME WIN_APP_NAME
///// ///////////////////////////////////////////////////////////

//class WinApp
//{
//public:
//	HRESULT InitWindow(HINSTANCE, INT, INT, INT, INT, LPCWSTR, LPCWSTR);
//	LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);
//	void MessageLoop();
//	void Application();
//
//	HWND hwnd_;
//	WNDCLASSEX  m_wc;
//
//	DWORD m_dwExecLastTime;
//	DWORD m_dwFPSLastTime;
//	DWORD m_dwCurrentTime;
//	DWORD m_dwFrameCount;
//
//	static Game game;
//};
//
//Game WinApp::game = Game();
#endif // !MAIN_H
