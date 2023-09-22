#pragma once

#include "engine_lib.h"
#include "glcorearb.h"
#include "platform.h"

// ###############################################################
//					  OpenGL Function Pointers
// ###############################################################

static PFNGLCREATEPROGRAMPROC glCreateProgram_ptr;

void gl_load_functions()
{
	glCreateProgram_ptr = reinterpret_cast<PFNGLCREATEPROGRAMPROC>(platform_load_gl_function("glCreateProgram"));
}

GLAPI GLuint APIENTRY glCreateProgram(void)
{
	return glCreateProgram_ptr();
}