#pragma once

/*shaders*/
extern PFNGLCREATESHADERPROC			glCreateShader;
extern PFNGLDELETESHADERPROC			glDeleteShader;
extern PFNGLSHADERSOURCEPROC			glShaderSource;
extern PFNGLCOMPILESHADERPROC			glCompileShader;
extern PFNGLRELEASESHADERCOMPILERPROC	glReleaseShaderCompiler;
extern PFNGLSHADERBINARYPROC			glShaderBinary;
extern PFNGLGETSHADERIVPROC				glGetShaderiv;
extern PFNGLGETSHADERINFOLOGPROC		glGetShaderInfoLog;

/*programs*/
extern PFNGLCREATEPROGRAMPROC		glCreateProgram;
extern PFNGLDELETEPROGRAMPROC		glDeleteProgram;
extern PFNGLDETACHSHADERPROC		glDetachShader;
extern PFNGLATTACHSHADERPROC		glAttachShader;
extern PFNGLLINKPROGRAMPROC			glLinkProgram;
extern PFNGLUSEPROGRAMPROC			glUseProgram;
extern PFNGLGETPROGRAMIVPROC		glGetProgramiv;
extern PFNGLGETPROGRAMINFOLOGPROC	glGetProgramInfoLog;
extern PFNGLGETATTRIBLOCATIONPROC	glGetAttribLocation;

/*attributes*/
extern PFNGLVERTEXATTRIBPOINTERPROC		glVertexAttribPointer;
extern PFNGLVERTEXATTRIBIPOINTERPROC		glVertexAttribIPointer;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC	glEnableVertexAttribArray;
extern PFNGLDISABLEVERTEXATTRIBARRAYPROC 	glDisableVertexAttribArray;
extern PFNGLBINDATTRIBLOCATIONPROC			glBindAttribLocation;

/*VBO*/
extern PFNGLGENBUFFERSPROC			glGenBuffers;
extern PFNGLBINDBUFFERPROC			glBindBuffer;
extern PFNGLBUFFERDATAPROC			glBufferData;
extern PFNGLBUFFERSUBDATAPROC		glBufferSubData;
extern PFNGLGENVERTEXARRAYSPROC		glGenVertexArrays;
extern PFNGLBINDVERTEXARRAYPROC		glBindVertexArray;
extern PFNGLDELETEVERTEXARRAYSPROC	glDeleteVertexArrays;
extern PFNGLDELETEBUFFERSPROC		glDeleteBuffers;
extern PFNGLMULTIDRAWELEMENTSPROC  glMultiDrawElements;
extern PFNGLDRAWELEMENTSBASEVERTEXPROC glDrawElementsBaseVertex;
extern PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC glMultiDrawElementsBaseVertex;
extern PFNGLMULTIDRAWARRAYSPROC glMultiDrawArrays;
extern PFNGLTEXBUFFERPROC glTexBuffer;

/*uniforms*/
extern PFNGLGETUNIFORMLOCATIONPROC	glGetUniformLocation;
extern PFNGLUNIFORM1IPROC			glUniform1i;
extern PFNGLUNIFORMMATRIX4FVPROC	glUniformMatrix4fv;
extern PFNGLUNIFORMMATRIX3FVPROC	glUniformMatrix3fv;
extern PFNGLUNIFORM3FPROC			glUniform3f;
extern PFNGLUNIFORM4FPROC			glUniform4f;
extern PFNGLUNIFORM1FPROC          glUniform1f;
extern PFNGLDRAWBUFFERSPROC         glDrawBuffers;


/*textures*/
extern PFNGLACTIVETEXTUREPROC	glActiveTexture;
extern PFNGLGENERATEMIPMAPPROC	glGenerateMipmap;
extern PFNGLTEXIMAGE3DPROC      glTexImage3D;
extern PFNGLTEXSUBIMAGE3DPROC  glTexSubImage3D;


/*FBO*/
extern PFNGLGENFRAMEBUFFERSPROC			glGenFramebuffers;
extern PFNGLBINDFRAMEBUFFERPROC			glBindFramebuffer;
extern PFNGLFRAMEBUFFERTEXTUREPROC		glFramebufferTexture;
extern PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D;
extern PFNGLFRAMEBUFFERTEXTURELAYERPROC	glFramebufferTextureLayer;
extern PFNGLBINDFRAGDATALOCATIONPROC	glBindFragDataLocation;
extern PFNGLMINSAMPLESHADINGPROC			glMinSampleShading;

extern PFNGLDRAWELEMENTSINSTANCEDPROC	glDrawElementsInstanced;

extern PFNGLWAITSYNCPROC glWaitSync;
extern PFNGLFENCESYNCPROC glFenceSync;

void GetGLFunctions( void* (*GetProcAddressFunc)(const char*) );
