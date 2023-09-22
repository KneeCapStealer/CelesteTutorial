#pragma once

// ###############################################################
//						  Platform Globals
// ###############################################################
static bool running = true;

// ###############################################################
//						  Platform Functions
// ###############################################################
bool platform_create_window(int width, int height, const wchar_t* title);
void platform_update_window();