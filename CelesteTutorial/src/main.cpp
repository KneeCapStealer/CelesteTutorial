// ###############################################################
//						  Platform Globals
// ###############################################################
static bool running = true;

// ###############################################################
//						  Platform Functions
// ###############################################################
bool platform_create_window(int width, int height, const wchar_t* title);
bool platform_update_window();

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

// ###############################################################
//						  Windows Globals
// ###############################################################

bool platform_create_window(const int width, const int height, const wchar_t* title)
{
	HINSTANCE instance = GetModuleHandle(nullptr);
	WNDCLASS wc = {};
	wc.hInstance = instance;
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);	// Look of cursor
	wc.lpszClassName = title;						// This is not the title, just a unique identifier(ID)
	wc.lpfnWndProc = DefWindowProc;					// Callback for input into the window

	if (!RegisterClass(&wc))
		return false;

	// WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX
	constexpr int dwStyle = WS_OVERLAPPEDWINDOW;

	HWND window = CreateWindowEx(0, title, title, dwStyle, 100, 100, width, height, nullptr,
	                             nullptr, instance, nullptr);

	if (window == nullptr)
		return false;

	ShowWindow(window, SW_SHOW);
	return true;
}

#endif



int main()
{
	platform_create_window(1200, 720, L"Game");
	while (running)
	{
		// do shit
	}

	return 0;
}