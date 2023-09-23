#include "gl_renderer.h"
#include "input.h"

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

	int fileSize = 0;
	char* vertShader = read_file("assets/shaders/quad.vert", &fileSize, transientStorage);
	char* fragShader = read_file("assets/shaders/quad.frag", &fileSize, transientStorage);

	if (!vertShader || !fragShader)
	{
		SM_ASSERT(false, "Failed to load shaders");
		return false;
	}

	glShaderSource(vertShaderID, 1, &vertShader, nullptr);
	glShaderSource(fragShaderID, 1, &fragShader, nullptr);

	glCompileShader(vertShaderID);
	glCompileShader(fragShaderID);

	// Test if both shaders compiled correctly
	{
		int success;
		char shaderLog[2048]{};

		glGetShaderiv(vertShaderID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertShaderID, 2048, nullptr, shaderLog);
			SM_ASSERT(false, "Failed to compile vertex shader, GL Error: %s", shaderLog);
		}

		glGetShaderiv(fragShaderID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragShaderID, 2048, nullptr, shaderLog);
			SM_ASSERT(false, "Failed to compile vertex shader, GL Error: %s", shaderLog);
		}
	}

	glContext.programID = glCreateProgram();
	glAttachShader(glContext.programID, vertShaderID);
	glAttachShader(glContext.programID, fragShaderID);
	glLinkProgram(glContext.programID);

	glDetachShader(glContext.programID, vertShaderID);
	glDetachShader(glContext.programID, fragShaderID);
	glDeleteShader(vertShaderID);
	glDeleteShader(fragShaderID);

	// This has to be done, for some reason.
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Enable Depth Testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_GREATER);

	glUseProgram(glContext.programID);

	return true;
}

void gl_render()
{
	glClearColor(119.f / 255.f, 33.f / 255.f, 111.f / 255.f, 1.f);
	glClearDepth(0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, input.screenSizeX, input.screenSizeY);


	glDrawArrays(GL_TRIANGLES, 0, 6);
}

GLuint glCreateProgram()
{
	return glCreateProgram_ptr();
}

void glDeleteTextures(GLsizei n, const GLuint* textures)
{
	glDeleteTextures_ptr(n, textures);
}

void glGenTextures(GLsizei n, GLuint* textures)
{
	glGenTextures_ptr(n, textures);
}

void glBindTexture(GLenum target, GLuint texture)
{
	glBindTexture_ptr(target, texture);
}

void glDrawArrays(GLenum mode, GLint first, GLsizei count)
{
	glDrawArrays_ptr(mode, first, count);
}

GLuint glCreateShader(GLenum shaderType)
{
	return glCreateShader_ptr(shaderType);
}

GLint glGetUniformLocation(GLuint program, const GLchar* name)
{
	return glGetUniformLocation_ptr(program, name);
}

void glUniform1f(GLint location, GLfloat v0)
{
	glUniform1f_ptr(location, v0);
}

void glUniform2fv(GLint location, GLsizei count, const GLfloat* value)
{
	glUniform2fv_ptr(location, count, value);
}

void glUniform3fv(GLint location, GLsizei count, const GLfloat* value)
{
	glUniform3fv_ptr(location, count, value);
}

void glUniform1i(GLint location, GLint v0)
{
	glUniform1i_ptr(location, v0);
}

void glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	glUniformMatrix4fv_ptr(location, count, transpose, value);
}

void glVertexAttribDivisor(GLuint index, GLuint divisor)
{
	glVertexAttribDivisor_ptr(index, divisor);
}

void glActiveTexture(GLenum texture)
{
	glActiveTexture_ptr(texture);
}

void glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void* data)
{
	glBufferSubData_ptr(target, offset, size, data);
}

void glDrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei instanceCount)
{
	glDrawArraysInstanced_ptr(mode, first, count, instanceCount);
}

void glBindFramebuffer(GLenum target, GLuint framebuffer)
{
	glBindFramebuffer_ptr(target, framebuffer);
}

GLenum glCheckFramebufferStatus(GLenum target)
{
	return glCheckFramebufferStatus_ptr(target);
}

void glGenFramebuffers(GLsizei n, GLuint* framebuffers)
{
	glGenFramebuffers_ptr(n, framebuffers);
}

void glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture,
	GLint level)
{
	glFramebufferTexture2D_ptr(target, attachment, textarget, texture, level);
}

void glDrawBuffers(GLsizei n, const GLenum* bufs)
{
	glDrawBuffers_ptr(n, bufs);
}

void glDeleteFramebuffers(GLsizei n, const GLuint* framebuffers)
{
	glDeleteFramebuffers_ptr(n, framebuffers);
}

void glBlendFunci(GLuint buf, GLenum src, GLenum dst)
{
	glBlendFunci_ptr(buf, src, dst);
}

void glBlendEquation(GLenum mode)
{
	glBlendEquation_ptr(mode);
}

void glClearBufferfv(GLenum buffer, GLint drawbuffer, const GLfloat* value)
{
	glClearBufferfv_ptr(buffer, drawbuffer, value);
}

void glShaderSource(GLuint shader, GLsizei count, const GLchar* const* strings, const GLint* lengths)
{
	glShaderSource_ptr(shader, count, strings, lengths);
}

void glCompileShader(GLuint shader)
{
	glCompileShader_ptr(shader);
}

void glGetShaderiv(GLuint shader, GLenum pname, GLint* params)
{
	glGetShaderiv_ptr(shader, pname, params);
}

void glGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* infoLog)
{
	glGetShaderInfoLog_ptr(shader, bufSize, length, infoLog);
}

void glAttachShader(GLuint program, GLuint shader)
{
	glAttachShader_ptr(program, shader);
}

void glLinkProgram(GLuint program)
{
	glLinkProgram_ptr(program);
}

void glValidateProgram(GLuint program)
{
	glValidateProgram_ptr(program);
}

void glGetProgramiv(GLuint program, GLenum pname, GLint* params)
{
	glGetProgramiv_ptr(program, pname, params);
}

void glGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei* length, GLchar* infoLog)
{
	glGetProgramInfoLog_ptr(program, bufSize, length, infoLog);
}

void glGenBuffers(GLsizei n, GLuint* buffers)
{
	glGenBuffers_ptr(n, buffers);
}

void glGenVertexArrays(GLsizei n, GLuint* arrays)
{
	glGenVertexArrays_ptr(n, arrays);
}

GLint glGetAttribLocation(GLuint program, const GLchar* name)
{
	return glGetAttribLocation_ptr(program, name);
}

void glBindVertexArray(GLuint array)
{
	glBindVertexArray_ptr(array);
}

void glEnableVertexAttribArray(GLuint index)
{
	glEnableVertexAttribArray_ptr(index);
}

void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized,
	GLsizei stride, const void* pointer)
{
	glVertexAttribPointer_ptr(index, size, type, normalized, stride, pointer);
}

void glBindBuffer(GLenum target, GLuint buffer)
{
	glBindBuffer_ptr(target, buffer);
}

void glBindBufferBase(GLenum target, GLuint index, GLuint buffer)
{
	glBindBufferBase_ptr(target, index, buffer);
}

void glBufferData(GLenum target, GLsizeiptr size, const void* data, GLenum usage)
{
	glBufferData_ptr(target, size, data, usage);
}

void glGetVertexAttribPointerv(GLuint index, GLenum pname, void** pointer)
{
	glGetVertexAttribPointerv_ptr(index, pname, pointer);
}

void glUseProgram(GLuint program)
{
	glUseProgram_ptr(program);
}

void glDeleteVertexArrays(GLsizei n, const GLuint* arrays)
{
	glDeleteVertexArrays_ptr(n, arrays);
}

void glDeleteBuffers(GLsizei n, const GLuint* buffers)
{
	glDeleteBuffers_ptr(n, buffers);
}

void glDeleteProgram(GLuint program)
{
	glDeleteProgram_ptr(program);
}

void glDetachShader(GLuint program, GLuint shader)
{
	glDetachShader_ptr(program, shader);
}

void glDeleteShader(GLuint shader)
{
	glDeleteShader_ptr(shader);
}

void glDrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, const void* indices,
	GLsizei instancecount)
{
	glDrawElementsInstanced_ptr(mode, count, type, indices, instancecount);
}

void glGenerateMipmap(GLenum target)
{
	glGenerateMipmap_ptr(target);
}

void glDebugMessageCallback(GLDEBUGPROC callback, const void* userParam)
{
	glDebugMessageCallback_ptr(callback, userParam);
}

void load_gl_functions()
{
	// Load OpenGL Functions from the Operating System / Graphics Card
	glCreateProgram_ptr = (PFNGLCREATEPROGRAMPROC)platform_load_gl_function("glCreateProgram");
	glDeleteTextures_ptr = (PFNGLDELETETEXTURESPROC)platform_load_gl_function("glDeleteTextures");
	glGenTextures_ptr = (PFNGLGENTEXTURESPROC)platform_load_gl_function("glGenTextures");
	glBindTexture_ptr = (PFNGLBINDTEXTUREPROC)platform_load_gl_function("glBindTexture");
	glDrawArrays_ptr = (PFNGLDRAWARRAYSPROC)platform_load_gl_function("glDrawArrays");
	glCreateShader_ptr = (PFNGLCREATESHADERPROC)platform_load_gl_function("glCreateShader");
	glGetUniformLocation_ptr = (PFNGLGETUNIFORMLOCATIONPROC)platform_load_gl_function("glGetUniformLocation");
	glUniform1f_ptr = (PFNGLUNIFORM1FPROC)platform_load_gl_function("glUniform1f");
	glUniform2fv_ptr = (PFNGLUNIFORM2FVPROC)platform_load_gl_function("glUniform2fv");
	glUniform3fv_ptr = (PFNGLUNIFORM3FVPROC)platform_load_gl_function("glUniform3fv");
	glUniform1i_ptr = (PFNGLUNIFORM1IPROC)platform_load_gl_function("glUniform1i");
	glUniformMatrix4fv_ptr = (PFNGLUNIFORMMATRIX4FVPROC)platform_load_gl_function("glUniformMatrix4fv");
	glVertexAttribDivisor_ptr = (PFNGLVERTEXATTRIBDIVISORPROC)platform_load_gl_function("glVertexAttribDivisor");
	glActiveTexture_ptr = (PFNGLACTIVETEXTUREPROC)platform_load_gl_function("glActiveTexture");
	glBufferSubData_ptr = (PFNGLBUFFERSUBDATAPROC)platform_load_gl_function("glBufferSubData");
	glDrawArraysInstanced_ptr = (PFNGLDRAWARRAYSINSTANCEDPROC)platform_load_gl_function("glDrawArraysInstanced");
	glBindFramebuffer_ptr = (PFNGLBINDFRAMEBUFFERPROC)platform_load_gl_function("glBindFramebuffer");
	glCheckFramebufferStatus_ptr = (PFNGLCHECKFRAMEBUFFERSTATUSPROC)platform_load_gl_function("glCheckFramebufferStatus");
	glGenFramebuffers_ptr = (PFNGLGENFRAMEBUFFERSPROC)platform_load_gl_function("glGenFramebuffers");
	glFramebufferTexture2D_ptr = (PFNGLFRAMEBUFFERTEXTURE2DPROC)platform_load_gl_function("glFramebufferTexture2D");
	glDrawBuffers_ptr = (PFNGLDRAWBUFFERSPROC)platform_load_gl_function("glDrawBuffers");
	glDeleteFramebuffers_ptr = (PFNGLDELETEFRAMEBUFFERSPROC)platform_load_gl_function("glDeleteFramebuffers");
	glBlendFunci_ptr = (PFNGLBLENDFUNCIPROC)platform_load_gl_function("glBlendFunci");
	glBlendEquation_ptr = (PFNGLBLENDEQUATIONPROC)platform_load_gl_function("glBlendEquation");
	glClearBufferfv_ptr = (PFNGLCLEARBUFFERFVPROC)platform_load_gl_function("glClearBufferfv");
	glShaderSource_ptr = (PFNGLSHADERSOURCEPROC)platform_load_gl_function("glShaderSource");
	glCompileShader_ptr = (PFNGLCOMPILESHADERPROC)platform_load_gl_function("glCompileShader");
	glGetShaderiv_ptr = (PFNGLGETSHADERIVPROC)platform_load_gl_function("glGetShaderiv");
	glGetShaderInfoLog_ptr = (PFNGLGETSHADERINFOLOGPROC)platform_load_gl_function("glGetShaderInfoLog");
	glAttachShader_ptr = (PFNGLATTACHSHADERPROC)platform_load_gl_function("glAttachShader");
	glLinkProgram_ptr = (PFNGLLINKPROGRAMPROC)platform_load_gl_function("glLinkProgram");
	glValidateProgram_ptr = (PFNGLVALIDATEPROGRAMPROC)platform_load_gl_function("glValidateProgram");
	glGetProgramiv_ptr = (PFNGLGETPROGRAMIVPROC)platform_load_gl_function("glGetProgramiv");
	glGetProgramInfoLog_ptr = (PFNGLGETPROGRAMINFOLOGPROC)platform_load_gl_function("glGetProgramInfoLog");
	glGenBuffers_ptr = (PFNGLGENBUFFERSPROC)platform_load_gl_function("glGenBuffers");
	glGenVertexArrays_ptr = (PFNGLGENVERTEXARRAYSPROC)platform_load_gl_function("glGenVertexArrays");
	glGetAttribLocation_ptr = (PFNGLGETATTRIBLOCATIONPROC)platform_load_gl_function("glGetAttribLocation");
	glBindVertexArray_ptr = (PFNGLBINDVERTEXARRAYPROC)platform_load_gl_function("glBindVertexArray");
	glEnableVertexAttribArray_ptr = (PFNGLENABLEVERTEXATTRIBARRAYPROC)platform_load_gl_function("glEnableVertexAttribArray");
	glVertexAttribPointer_ptr = (PFNGLVERTEXATTRIBPOINTERPROC)platform_load_gl_function("glVertexAttribPointer");
	glBindBuffer_ptr = (PFNGLBINDBUFFERPROC)platform_load_gl_function("glBindBuffer");
	glBindBufferBase_ptr = (PFNGLBINDBUFFERBASEPROC)platform_load_gl_function("glBindBufferBase");
	glBufferData_ptr = (PFNGLBUFFERDATAPROC)platform_load_gl_function("glBufferData");
	glGetVertexAttribPointerv_ptr = (PFNGLGETVERTEXATTRIBPOINTERVPROC)platform_load_gl_function("glGetVertexAttribPointerv");
	glUseProgram_ptr = (PFNGLUSEPROGRAMPROC)platform_load_gl_function("glUseProgram");
	glDeleteVertexArrays_ptr = (PFNGLDELETEVERTEXARRAYSPROC)platform_load_gl_function("glDeleteVertexArrays");
	glDeleteBuffers_ptr = (PFNGLDELETEBUFFERSPROC)platform_load_gl_function("glDeleteBuffers");
	glDeleteProgram_ptr = (PFNGLDELETEPROGRAMPROC)platform_load_gl_function("glDeleteProgram");
	glDetachShader_ptr = (PFNGLDETACHSHADERPROC)platform_load_gl_function("glDetachShader");
	glDeleteShader_ptr = (PFNGLDELETESHADERPROC)platform_load_gl_function("glDeleteShader");
	glDrawElementsInstanced_ptr = (PFNGLDRAWELEMENTSINSTANCEDPROC)platform_load_gl_function("glDrawElementsInstanced");
	glGenerateMipmap_ptr = (PFNGLGENERATEMIPMAPPROC)platform_load_gl_function("glGenerateMipmap");
	glDebugMessageCallback_ptr = (PFNGLDEBUGMESSAGECALLBACKPROC)platform_load_gl_function("glDebugMessageCallback");
}
