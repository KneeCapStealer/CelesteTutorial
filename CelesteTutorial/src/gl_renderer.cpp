#include "gl_renderer.h"

static void APIENTRY gl_debug_callback(GLenum source, GLenum type, GLuint id, GLenum severity,
	GLsizei length, const GLchar* message, const void* user)
{
	if (severity == GL_DEBUG_SEVERITY_LOW ||
		severity == GL_DEBUG_SEVERITY_MEDIUM ||
		severity == GL_DEBUG_SEVERITY_HIGH)
	{
		SM_ASSERT(false, "OpenGL Error: %s", message);
	}
	else
	{
		SM_TRACE(message);
	}
}

bool gl_init(BumpAllocator* transientStorage)
{
	load_gl_functions();

	glDebugMessageCallback(&gl_debug_callback, nullptr);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glEnable(GL_DEBUG_OUTPUT);

	GLuint vertShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);


	return true;
}
