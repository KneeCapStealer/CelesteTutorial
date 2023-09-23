// Third party includes
#define APIENTRY // make sure glcorearb.h doesn't include windows.h
#define GL_GLEXT_PROTOTYPES
#include <glcorearb.h>

// Src code includes
#include "engine_lib.h"
#include "platform.h"
#include "gl_renderer.h"
#include "input.h"

// If the platform is windows
#ifdef _WIN32
#include "win32_platform.h"
#endif

int main()
{
	BumpAllocator transientStorage = make_bump_allocator(MB(50));
	input.screenSizeX = 1200;
	input.screenSizeY = 720;

	platform_create_window(input.screenSizeX, input.screenSizeY, L"Game");

	gl_init(&transientStorage);
	while (running)
	{
		//update
		platform_update_window();
		gl_render();

		platform_swap_buffers();
	}

	return 0;
}