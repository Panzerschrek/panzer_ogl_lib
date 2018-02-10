#pragma once

#ifdef _MSC_VER
#define NOMINMAX
#include <windows.h>
#endif // _MSC_VER

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else // !__APPLE__

#include <GL/gl.h>

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

#endif // __APPLE__

#include "glcorearb.h"

#include "func_declarations.hpp"
