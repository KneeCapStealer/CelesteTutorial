
#include "platform.h"
#include "engine_lib.h"

#include "win32_platform.h"

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

void* platform_load_gl_function(const char* fnName)
{
	PROC proc = wglGetProcAddress(fnName);
	if (!proc)
	{
		static HMODULE openglDLL = LoadLibrary(L"opnegl32.dll");
		proc = GetProcAddress(openglDLL, fnName);

		if (!proc)
		{
			SM_ASSERT(false, "Failed to load glCreateProgram");
			return nullptr;
		}
	}

	return reinterpret_cast<void*>(proc);
}
