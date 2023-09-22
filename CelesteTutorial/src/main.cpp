// Third party includes
#define APIENTRY // make sure glcorearb.h doesn't include windows.h
#include <glcorearb.h>

// Src code includes
#include "engine_lib.h"
#include "platform.h"
#include "gl_renderer.h"

// If the platform is windows
#ifdef _WIN32
#include "win32_platform.h"
#endif



int main()
{
	platform_create_window(1200, 720, L"Game");
	while (running)
	{
		//update
		platform_update_window();
	}

	return 0;
}