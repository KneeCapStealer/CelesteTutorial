#pragma once

// ###############################################################
//						  Platform Globals
// ###############################################################
inline bool running = true;

// ###############################################################
//						  Platform Functions
// ###############################################################
bool platform_create_window(int width, int height, const wchar_t* title);
void platform_update_window();
void* platform_load_gl_function(const char* fnName);
void platform_swap_buffers();
