// Third party includes
#include <glcorearb.h>
#include <wglext.h>

// Src code includes
#include "platform.h"
#include "engine_lib.h"
#include "win32_platform.h"
#include "input.h"

// ###############################################################
//						  Windows Globals
// ###############################################################
HDC deviceContext;

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

	case WM_SIZE:
		{
			RECT rect{};
			GetClientRect(window, &rect);

			input.screenSizeX = rect.right - rect.left;
			input.screenSizeY = rect.bottom - rect.top;
			break;
		}

	default:
		result = DefWindowProc(window, msg, wParam, lParam);
		break;
	}

	return result;
}

bool platform_create_window(int width, int height, const wchar_t* title)
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

	PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB;
	PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;


	// WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX
	constexpr int dwStyle = WS_OVERLAPPEDWINDOW;

	// Fake window initializing OpenGL
	{

		window = CreateWindowEx(0, title, title, dwStyle, 100, 100, width, height, nullptr,
		                        nullptr, instance, nullptr);

		if (window == nullptr)
		{
			SM_ASSERT(false, "Failed to create Windows Window");
			return false;
		}

		HDC fakeDC = GetDC(window);
		if(!fakeDC)
		{
			SM_ASSERT(false, "Failed to get HDC");
			return false;
		}

		PIXELFORMATDESCRIPTOR pfd{};
		pfd.nSize = sizeof(pfd);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cAlphaBits = 8;
		pfd.cDepthBits = 24;

		const int pixelFormat = ChoosePixelFormat(fakeDC, &pfd);
		if (!pixelFormat)
		{
			SM_ASSERT(false, "Failed to choose pixel format");
			return false;
		}

		if (!SetPixelFormat(fakeDC, pixelFormat, &pfd))
		{
			SM_ASSERT(false, "Failed to set pixelformat");
			return false;
		}

		HGLRC fakeRC = wglCreateContext(fakeDC);
		if (!fakeRC)
		{
			SM_ASSERT(false, "Failed to create render context");
			return false;
		}

		if (!wglMakeCurrent(fakeDC, fakeRC))
		{
			SM_ASSERT(false, "Failed to make current");
			return false;
		}

		wglChoosePixelFormatARB = reinterpret_cast<PFNWGLCHOOSEPIXELFORMATARBPROC>(
			platform_load_gl_function("wglChoosePixelFormatARB"));

		wglCreateContextAttribsARB = reinterpret_cast<PFNWGLCREATECONTEXTATTRIBSARBPROC>(
			platform_load_gl_function("wglCreateContextAttribsARB"));

		if (!wglChoosePixelFormatARB || !wglCreateContextAttribsARB)
		{
			SM_ASSERT(false, "Failed to load OpenGL functions");
			return false;
		}

		// Clean up the fake window context
		wglMakeCurrent(fakeDC, nullptr); //set the current rendering context to null
		wglDeleteContext(fakeRC);
		ReleaseDC(window, fakeDC);

		// Can't reuse the same device context
		// because we already called 'SetPixelFormat()'
		DestroyWindow(window);
	}

	// Actual OpenGL initialization
	{
		// Add in the border size of the window
		RECT borderRect{};
		AdjustWindowRectEx(&borderRect, dwStyle, NULL, NULL);

		width += borderRect.right - borderRect.left;
		height += borderRect.bottom - borderRect.top;

		window = CreateWindowEx(0, title, title, dwStyle, 100, 100, width, height, nullptr,
		                        nullptr, instance, nullptr);

		if (window == nullptr)
		{
			SM_ASSERT(false, "Failed to create Windows Window");
			return false;
		}

		deviceContext = GetDC(window);
		if (!deviceContext)
		{
			SM_ASSERT(false, "Failed to get HDC");
			return false;
		}

		const int pixelAttribs[] =
		{
			WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
			WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
			WGL_DOUBLE_BUFFER_ARB,	GL_TRUE,
			WGL_SWAP_METHOD_ARB,	WGL_SWAP_COPY_ARB,
			WGL_PIXEL_TYPE_ARB,		WGL_TYPE_RGBA_ARB,
			WGL_ACCELERATION_ARB,	WGL_FULL_ACCELERATION_ARB,
			WGL_COLOR_BITS_ARB,		32,
			WGL_ALPHA_BITS_ARB,		8,
			WGL_DEPTH_BITS_ARB,		24,
			0						// Terminate with 0, otherwise OpenGL will throw an error!
		};

		UINT numPixelFormats;
		int pixelFormat = 0;
		if (!wglChoosePixelFormatARB(
			deviceContext, pixelAttribs,
			nullptr, // Float list
			1, // Max formats
			&pixelFormat,
			&numPixelFormats))
		{
			SM_ASSERT(false, "Failed to wglChoosePixelFormatARB");
			return false;
		}

		PIXELFORMATDESCRIPTOR pfd{};
		DescribePixelFormat(deviceContext, pixelFormat, sizeof(pfd), &pfd);

		if (!SetPixelFormat(deviceContext, pixelFormat, &pfd))
		{
			SM_ASSERT(false, "Failed to set pixel format");
			return false;
		}

		const int contextAttribs[] =
		{
			WGL_CONTEXT_MAJOR_VERSION_ARB,	4,
			WGL_CONTEXT_MINOR_VERSION_ARB,	3,
			WGL_CONTEXT_PROFILE_MASK_ARB,	WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
			WGL_CONTEXT_FLAGS_ARB,			WGL_CONTEXT_DEBUG_BIT_ARB,
			0								// Terminate with 0
		};

		HGLRC renderContext = wglCreateContextAttribsARB(deviceContext, nullptr, contextAttribs);
		if (!renderContext)
		{
			SM_ASSERT(false, "Failed to create rendering context");
			return false;
		}

		if (!wglMakeCurrent(deviceContext, renderContext))
		{
			SM_ASSERT(false, "Failed to make current");
			return false;
		}
	}

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

void platform_swap_buffers()
{
	SwapBuffers(deviceContext);
}
