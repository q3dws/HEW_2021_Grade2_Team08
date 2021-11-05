#include <memory>
#include "Window.h"

Window* gp_window;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return gp_window->MsgProc(hWnd, uMsg, wParam, lParam);
}

HRESULT Window::InitWindow(HINSTANCE hInstance, INT iX, INT iY, INT iWidth, INT iHeight, LPCWSTR lpClassName, LPCWSTR lpWindowName)
{
	gp_window = this;
	// ウィンドウの定義
	WNDCLASSEX window_class;
	ZeroMemory(&window_class, sizeof(window_class));
	window_class.cbSize			= sizeof(window_class);
	window_class.style			= CS_HREDRAW | CS_VREDRAW;
	window_class.lpfnWndProc	= WndProc;
	window_class.hInstance		= hInstance;
	window_class.hIcon			= LoadIcon(nullptr, IDI_APPLICATION);
	window_class.hCursor		= LoadCursor(nullptr, IDC_ARROW);
	window_class.hbrBackground	= (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	window_class.lpszClassName	= lpClassName;
	window_class.hIconSm		= LoadIcon(nullptr, IDI_APPLICATION);
	RegisterClassEx(&window_class);

	//ウィンドウの作成
	hwnd_ = CreateWindow
	(
		lpClassName,																	/* _In_		DWORD	dwExStyle,		*/
		lpWindowName, 																	/* _In_opt_	LPCWSTR	lpClassName,	*/
		WS_OVERLAPPEDWINDOW,															/* _In_opt_	LPCWSTR	lpWindowName,	*/
		CW_USEDEFAULT, 																	/* _In_		DWORD	dwStyle,		*/
		CW_USEDEFAULT, 																	/* _In_		int		X,				*/
		iWidth + GetSystemMetrics(SM_CXDLGFRAME) * 2,									/* _In_		int		Y,				*/
		iHeight + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),	/* _In_		int		nWidth,			*/
		nullptr,																		/* _In_		int		nHeight,		*/
		nullptr,																		/* _In_opt_ HWND	hWndParent,		*/
		hInstance, 																		/* _In_opt_ HMENU	hMenu,			*/
		nullptr																			/* _In_opt_ LPVOID	lpParam			*/
	);

	if (!hwnd_)
		return E_FAIL;

	// DirectXの初期化(ウィンドウを作成してから行う)
	//if (FAILED(Init(hInstance, m_hWnd, true)))
	//{
	//	return -1;
	//}

	//ウインドウの表示
	//ShowWindow(hwnd_, SW_SHOW);
	//UpdateWindow(hwnd_);

	return S_OK;
}

LRESULT Window::MsgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
	case WM_KEYDOWN:
		switch ((char)wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}