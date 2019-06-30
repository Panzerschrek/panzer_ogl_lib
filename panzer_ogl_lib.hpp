#pragma once

#ifdef _MSC_VER
#define NOMINMAX
#include <windows.h>
#endif // _MSC_VER

#ifdef __ANDROID__
#include <GLES/gl.h>
#else
#include <GL/gl.h>
#endif

// Catch system gl.h OpenGL version.
// glcorearb.h redefines them all.

#ifdef GL_VERSION_1_1
#define R_SYSTEM_GL_VERSION_1_1
#endif
#ifdef GL_VERSION_1_2
#define R_SYSTEM_GL_VERSION_1_2
#endif
#ifdef GL_VERSION_1_3
#define R_SYSTEM_GL_VERSION_1_3
#endif
#ifdef GL_VERSION_1_4
#define R_SYSTEM_GL_VERSION_1_4
#endif
#ifdef GL_VERSION_ES_CM_1_0
#define R_SYSTEM_GL_VERSION_ES
#endif

#ifdef __ANDROID__
#define GL_VERSION_1_5
#endif
#include "glcorearb.h"

#include "func_declarations.hpp"
