#include "engine_lib.h"

// ###############################################################
//						  Platform Globals
// ###############################################################
static bool running = true;

// ###############################################################
//						  Platform Functions
// ###############################################################
bool platform_create_window(int width, int height, const wchar_t* title);
void platform_update_window();

// ###############################################################
//						  Windows Platform
// ###############################################################
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include <Windows.h>

// ###############################################################
//						  Windows Globals
// ###############################################################

static HWND window;

// ###############################################################
//						  Windows Implementations
// ###############################################################

LRESULT CALLBACK windows_window_callback(const HWND window, const UINT msg, const WPARAM wParam, const LPARAM lParam)
{
	LRESULT result = 0;
	switch (msg)
	{
		case WM_CLOSE:
			running = false;
			break;

		default:
			result = DefWindowProc(window, msg, wParam, lParam);
			break;
	}

	return result;
}

bool platform_create_window(const int width, const int height, const wchar_t* title)
{
	HINSTANCE instance = GetModuleHandle(nullptr);
	WNDCLASS wc = {};
	wc.hInstance = instance;
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);	// Look of cursor
	wc.lpszClassName = title;						// This is not the title, just a unique identifier(ID)
	wc.lpfnWndProc = windows_window_callback;					// Callback for input into the window

	if (!RegisterClass(&wc))
		return false;

	// WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX
	constexpr int dwStyle = WS_OVERLAPPEDWINDOW;

	window = CreateWindowEx(0, title, title, dwStyle, 100, 100, width, height, nullptr,
	                        nullptr, instance, nullptr);

	if (window == nullptr)
		return false;

	ShowWindow(window, SW_SHOW);
	return true;
}

void platform_update_window()
{
	MSG msg;

	while (PeekMessage(&msg, window, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}


#endif



int main()
{
	platform_create_window(1200, 720, L"Game");
	while (running)
	{
		//update
		platform_update_window();

		SM_TRACE("test");
		SM_WARN("OH NO");
		SM_ERROR("FCK");
		SM_ASSERT(false, "Damn, this really asserted man");
	}

	return 0;
}