#pragma once

#include "engine_lib.h"

#define APIENTRY // make sure glcorearb.h doesn't include windows.h
#define GL_GLEXT_PROTOTYPES
#include "glcorearb.h"
#include "platform.h"

// #############################################################################
//                           OpenGL Constants
// #############################################################################

constexpr const char* TEXTURE_PATH = "assets/textures/TEXTURE_ATLAS.png";

// ###############################################################
//						  OpenGL Structs
// ###############################################################

struct GLContext
{
    GLuint programID;
    GLuint textureID;
    GLuint transformSBOID;
    GLuint screenSizeID;
};

// ###############################################################
//						  OpenGL Globals 
// ###############################################################

inline GLContext glContext;

// #############################################################################
//                              OpenGL Functions
// #############################################################################
void load_gl_functions();

static void APIENTRY gl_debug_callback(GLenum source, GLenum type, GLuint id, GLenum severity,
    GLsizei length, const GLchar* message, const void* user);

bool gl_init(BumpAllocator* transientStorage);

void gl_render();

// #############################################################################
//                           OpenGL Function Pointers
// #############################################################################
static PFNGLCREATEPROGRAMPROC glCreateProgram_ptr;
static PFNGLDELETETEXTURESPROC glDeleteTextures_ptr;
static PFNGLGENTEXTURESPROC glGenTextures_ptr;
static PFNGLBINDTEXTUREPROC glBindTexture_ptr;
static PFNGLDRAWBUFFERPROC glDrawBuffer_ptr;
static PFNGLDRAWARRAYSPROC glDrawArrays_ptr;
static PFNGLCREATESHADERPROC glCreateShader_ptr;
static PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation_ptr;
static PFNGLUNIFORM1FPROC glUniform1f_ptr;
static PFNGLUNIFORM2FVPROC glUniform2fv_ptr;
static PFNGLUNIFORM3FVPROC glUniform3fv_ptr;
static PFNGLUNIFORM1IPROC glUniform1i_ptr;
static PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv_ptr;
static PFNGLVERTEXATTRIBDIVISORPROC glVertexAttribDivisor_ptr;
static PFNGLACTIVETEXTUREPROC glActiveTexture_ptr;
static PFNGLBUFFERSUBDATAPROC glBufferSubData_ptr;
static PFNGLDRAWARRAYSINSTANCEDPROC glDrawArraysInstanced_ptr;
static PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer_ptr;
static PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus_ptr;
static PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers_ptr;
static PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D_ptr;
static PFNGLDRAWBUFFERSPROC glDrawBuffers_ptr;
static PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers_ptr;
static PFNGLBLENDFUNCIPROC glBlendFunci_ptr;
static PFNGLBLENDEQUATIONPROC glBlendEquation_ptr;
static PFNGLCLEARBUFFERFVPROC glClearBufferfv_ptr;
static PFNGLSHADERSOURCEPROC glShaderSource_ptr;
static PFNGLCOMPILESHADERPROC glCompileShader_ptr;
static PFNGLGETSHADERIVPROC glGetShaderiv_ptr;
static PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog_ptr;
static PFNGLATTACHSHADERPROC glAttachShader_ptr;
static PFNGLLINKPROGRAMPROC glLinkProgram_ptr;
static PFNGLVALIDATEPROGRAMPROC glValidateProgram_ptr;
static PFNGLGETPROGRAMIVPROC glGetProgramiv_ptr;
static PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog_ptr;
static PFNGLGENBUFFERSPROC glGenBuffers_ptr;
static PFNGLGENVERTEXARRAYSPROC glGenVertexArrays_ptr;
static PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation_ptr;
static PFNGLBINDVERTEXARRAYPROC glBindVertexArray_ptr;
static PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray_ptr;
static PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer_ptr;
static PFNGLBINDBUFFERPROC glBindBuffer_ptr;
static PFNGLBINDBUFFERBASEPROC glBindBufferBase_ptr;
static PFNGLBUFFERDATAPROC glBufferData_ptr;
static PFNGLGETVERTEXATTRIBPOINTERVPROC glGetVertexAttribPointerv_ptr;
static PFNGLUSEPROGRAMPROC glUseProgram_ptr;
static PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays_ptr;
static PFNGLDELETEBUFFERSPROC glDeleteBuffers_ptr;
static PFNGLDELETEPROGRAMPROC glDeleteProgram_ptr;
static PFNGLDETACHSHADERPROC glDetachShader_ptr;
static PFNGLDELETESHADERPROC glDeleteShader_ptr;
static PFNGLDRAWELEMENTSINSTANCEDPROC glDrawElementsInstanced_ptr;
static PFNGLGENERATEMIPMAPPROC glGenerateMipmap_ptr;
static PFNGLDEBUGMESSAGECALLBACKPROC glDebugMessageCallback_ptr;

// #############################################################################
//                           OpenGL Function Wrappers
// #############################################################################
GLAPI GLuint APIENTRY glCreateProgram(void);

GLAPI void APIENTRY glDeleteTextures(GLsizei n, const GLuint* textures);

GLAPI void APIENTRY glGenTextures(GLsizei n, GLuint* textures);

GLAPI void APIENTRY glBindTexture(GLenum target, GLuint texture);

void glDrawArrays(GLenum mode, GLint first, GLsizei count);

GLuint glCreateShader(GLenum shaderType);

GLint glGetUniformLocation(GLuint program, const GLchar* name);

void glUniform1f(GLint location, GLfloat v0);

void glUniform2fv(GLint location, GLsizei count, const GLfloat* value);

void glUniform3fv(GLint location, GLsizei count, const GLfloat* value);

void glUniform1i(GLint location, GLint v0);

void glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);

void glVertexAttribDivisor(GLuint index, GLuint divisor);

void glActiveTexture(GLenum texture);

void glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void* data);

void glDrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei instanceCount);

void glBindFramebuffer(GLenum target, GLuint framebuffer);

GLenum glCheckFramebufferStatus(GLenum target);

void glGenFramebuffers(GLsizei n, GLuint* framebuffers);

void glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);

void glDrawBuffers(GLsizei n, const GLenum* bufs);

void glDeleteFramebuffers(GLsizei n, const GLuint* framebuffers);

void glBlendFunci(GLuint buf, GLenum src, GLenum dst);

void glBlendEquation(GLenum mode);

void glClearBufferfv(GLenum buffer, GLint drawbuffer, const GLfloat* value);

void glShaderSource(GLuint shader, GLsizei count, const GLchar* const* strings, const GLint* lengths);

void glCompileShader(GLuint shader);

void glGetShaderiv(GLuint shader, GLenum pname, GLint* params);

void glGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* infoLog);

void glAttachShader(GLuint program, GLuint shader);

void glLinkProgram(GLuint program);

void glValidateProgram(GLuint program);

void glGetProgramiv(GLuint program, GLenum pname, GLint* params);

void glGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei* length, GLchar* infoLog);

void glGenBuffers(GLsizei n, GLuint* buffers);

void glGenVertexArrays(GLsizei n, GLuint* arrays);

GLint glGetAttribLocation(GLuint program, const GLchar* name);

void glBindVertexArray(GLuint array);

void glEnableVertexAttribArray(GLuint index);

void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);

void glBindBuffer(GLenum target, GLuint buffer);

void glBindBufferBase(GLenum target, GLuint index, GLuint buffer);

void glBufferData(GLenum target, GLsizeiptr size, const void* data, GLenum usage);

void glGetVertexAttribPointerv(GLuint index, GLenum pname, void** pointer);

void glUseProgram(GLuint program);

void glDeleteVertexArrays(GLsizei n, const GLuint* arrays);

void glDeleteBuffers(GLsizei n, const GLuint* buffers);

void glDeleteProgram(GLuint program);

void glDetachShader(GLuint program, GLuint shader);

void glDeleteShader(GLuint shader);

void glDrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei instancecount);

void glGenerateMipmap(GLenum target);

void glDebugMessageCallback(GLDEBUGPROC callback, const void* userParam);

// Loaded by default it seems, but I kept them here, just in case, must be OpenGL 1.0, and static linking
/*
static PFNGLTEXIMAGE2DPROC glTexImage2D_ptr;
static PFNGLTEXPARAMETERIPROC glTexParameteri_ptr;
static PFNGLTEXPARAMETERFVPROC glTexParameterfv_ptr;
static PFNGLCLEARPROC glClear_ptr;
static PFNGLCLEARCOLORPROC glClearColor_ptr;
static PFNGLREADBUFFERPROC glReadBuffer_ptr;
static PFNGLDEPTHMASKPROC glDepthMask_ptr;
static PFNGLDISABLEPROC glDisable_ptr;
static PFNGLENABLEPROC glEnable_ptr;
static PFNGLSCISSORPROC glScissor_ptr;
static PFNGLVIEWPORTPROC glViewport_ptr;
static PFNGLDEPTHFUNCPROC glDepthFunc_ptr;
static PFNGLCULLFACEPROC glCullFace_ptr;
static PFNGLBLENDFUNCPROC glBlendFunc_ptr;
static PFNGLFRONTFACEPROC glFrontFace_ptr;

glTexImage2D_ptr = (PFNGLTEXIMAGE2DPROC)platform_load_gl_function("glTexImage2D");
glTexParameteri_ptr = (PFNGLTEXPARAMETERIPROC)platform_load_gl_function("glTexParameteri");
glTexParameterfv_ptr = (PFNGLTEXPARAMETERFVPROC)platform_load_gl_function("glTexParameterfv");
glClear_ptr = (PFNGLCLEARPROC)platform_load_gl_function("glClear");
glClearColor_ptr = (PFNGLCLEARCOLORPROC)platform_load_gl_function("glClearColor");
glReadBuffer_ptr = (PFNGLREADBUFFERPROC)platform_load_gl_function("glReadBuffer");
glDepthMask_ptr = (PFNGLDEPTHMASKPROC)platform_load_gl_function("glDepthMask");
glDisable_ptr = (PFNGLDISABLEPROC)platform_load_gl_function("glDisable");
glEnable_ptr = (PFNGLENABLEPROC)platform_load_gl_function("glEnable");
glScissor_ptr = (PFNGLSCISSORPROC)platform_load_gl_function("glScissor");
glViewport_ptr = (PFNGLVIEWPORTPROC)platform_load_gl_function("glViewport");
glDepthFunc_ptr = (PFNGLDEPTHFUNCPROC)platform_load_gl_function("glDepthFunc");
glCullFace_ptr = (PFNGLCULLFACEPROC)platform_load_gl_function("glCullFace");
glBlendFunc_ptr = (PFNGLBLENDFUNCPROC)platform_load_gl_function("glBlendFunc");
glFrontFace_ptr = (PFNGLFRONTFACEPROC)platform_load_gl_function("glFrontFace");

GLAPI void APIENTRY glTexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width,
                                  GLsizei height, GLint border, GLenum format, GLenum type,
                                  const void *pixels)
{
  glTexImage2D_ptr(target, level, internalformat, width, height,
                   border, format, type, pixels);
}

GLAPI void APIENTRY glTexParameteri (GLenum target, GLenum pname, GLint param)
{
  glTexParameteri_ptr(target, pname, param);
}

GLAPI void APIENTRY glTexParameterfv (GLenum target, GLenum pname, const GLfloat *params)
{
  glTexParameterfv_ptr(target, pname, params);
}

GLAPI void APIENTRY glClear (GLbitfield mask)
{
  glClear_ptr(mask);
}

GLAPI void APIENTRY glClearColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
  glClearColor_ptr(red, green, blue, alpha);
}

void glReadBuffer(GLenum mode)
{
    glReadBuffer_ptr(mode);
}

void glDepthMask(GLboolean flag)
{
    glDepthMask_ptr(flag);
}

void glDisable(GLenum cap)
{
    glDisable_ptr(cap);
}

void glEnable(GLenum cap)
{
    glEnable_ptr(cap);
}

void glScissor(GLint x, GLint y, GLsizei width, GLsizei height)
{
    glScissor_ptr(x, y, width, height);
}

void glViewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
    glViewport_ptr(x, y, width, height);
}

void glDepthFunc(GLenum func)
{
    glDepthFunc_ptr(func);
}

void glCullFace(GLenum mode)
{
    glCullFace_ptr(mode);
}

void glBlendFunc(GLenum sfactor, GLenum dfactor)
{
    glBlendFunc_ptr(sfactor, dfactor);
}

void glFrontFace(GLenum mode)
{
    glFrontFace_ptr(mode);
}
*/