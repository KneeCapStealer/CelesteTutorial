#include "engine_lib.h"
#include "platform.h"

// ###############################################################
//						  Windows Platform
// ###############################################################
#ifdef _WIN32
#include "win32_platform.cpp"
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