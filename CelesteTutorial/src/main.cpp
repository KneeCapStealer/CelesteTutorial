#include "engine_lib.h"
#include "platform.h"

// ###############################################################
//						  Windows Platform
// ###############################################################
#ifdef _WIN32
#include "win32_platform.h"
#endif

#include "gl_renderer.h"


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