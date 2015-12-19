#include "panzer_ogl_lib.hpp"
#include "func_declarations.hpp"

/*shaders*/
PFNGLCREATESHADERPROC			glCreateShader= NULL;
PFNGLDELETESHADERPROC			glDeleteShader= NULL;
PFNGLSHADERSOURCEPROC			glShaderSource= NULL;
PFNGLCOMPILESHADERPROC			glCompileShader= NULL;
PFNGLRELEASESHADERCOMPILERPROC	glReleaseShaderCompiler= NULL;
PFNGLSHADERBINARYPROC			glShaderBinary= NULL;
PFNGLGETSHADERIVPROC			glGetShaderiv= NULL;
PFNGLGETSHADERINFOLOGPROC		glGetShaderInfoLog= NULL;

/*programs*/
PFNGLCREATEPROGRAMPROC			glCreateProgram= NULL;
PFNGLDELETEPROGRAMPROC			glDeleteProgram= NULL;
PFNGLDETACHSHADERPROC			glDetachShader= NULL;
PFNGLATTACHSHADERPROC			glAttachShader= NULL;
PFNGLLINKPROGRAMPROC			glLinkProgram= NULL;
PFNGLUSEPROGRAMPROC				glUseProgram= NULL;
PFNGLGETPROGRAMIVPROC			glGetProgramiv= NULL;
PFNGLGETPROGRAMINFOLOGPROC		glGetProgramInfoLog= NULL;
PFNGLGETATTRIBLOCATIONPROC		glGetAttribLocation= NULL;

/*attributes*/
PFNGLBINDATTRIBLOCATIONPROC			glBindAttribLocation= NULL;
PFNGLVERTEXATTRIBPOINTERPROC		glVertexAttribPointer= NULL;
PFNGLVERTEXATTRIBIPOINTERPROC		glVertexAttribIPointer= NULL;
PFNGLENABLEVERTEXATTRIBARRAYPROC	glEnableVertexAttribArray= NULL;
PFNGLDISABLEVERTEXATTRIBARRAYPROC	glDisableVertexAttribArray= NULL;

/*VBO*/
PFNGLGENBUFFERSPROC			glGenBuffers= NULL;
PFNGLBINDBUFFERPROC			glBindBuffer= NULL;
PFNGLBUFFERDATAPROC			glBufferData= NULL;
PFNGLBUFFERSUBDATAPROC		glBufferSubData= NULL;
PFNGLGENVERTEXARRAYSPROC	glGenVertexArrays= NULL;
PFNGLBINDVERTEXARRAYPROC	glBindVertexArray= NULL;
PFNGLDELETEVERTEXARRAYSPROC	glDeleteVertexArrays= NULL;
PFNGLDELETEBUFFERSPROC		glDeleteBuffers= NULL;
PFNGLMULTIDRAWELEMENTSPROC	glMultiDrawElements= NULL;
PFNGLDRAWELEMENTSBASEVERTEXPROC	glDrawElementsBaseVertex= NULL;
PFNGLDRAWELEMENTSINSTANCEDPROC	glDrawElementsInstanced= NULL;
PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC	glMultiDrawElementsBaseVertex= NULL;
PFNGLMULTIDRAWARRAYSPROC	glMultiDrawArrays= NULL;
PFNGLTEXBUFFERPROC			glTexBuffer= NULL;

/*uniforms*/
PFNGLGETUNIFORMLOCATIONPROC	glGetUniformLocation= NULL;
PFNGLUNIFORM1IPROC			glUniform1i= NULL;
PFNGLUNIFORM3FPROC			glUniform3f= NULL;
PFNGLUNIFORM4FPROC			glUniform4f= NULL;
PFNGLUNIFORMMATRIX4FVPROC	glUniformMatrix4fv= NULL;
PFNGLUNIFORMMATRIX3FVPROC	glUniformMatrix3fv= NULL;
PFNGLUNIFORM1FPROC			glUniform1f= NULL;

/*textures*/
PFNGLACTIVETEXTUREPROC	glActiveTexture= NULL;
PFNGLGENERATEMIPMAPPROC	glGenerateMipmap= NULL;
PFNGLTEXIMAGE3DPROC		glTexImage3D= NULL;
PFNGLTEXSUBIMAGE3DPROC	glTexSubImage3D= NULL;

/*FBO*/
PFNGLGENFRAMEBUFFERSPROC			glGenFramebuffers= NULL;
PFNGLDELETEFRAMEBUFFERSPROC			glDeleteFramebuffers= NULL;
PFNGLBINDFRAMEBUFFERPROC			glBindFramebuffer= NULL;
PFNGLFRAMEBUFFERTEXTUREPROC			glFramebufferTexture= NULL;
PFNGLFRAMEBUFFERTEXTURE2DPROC		glFramebufferTexture2D= NULL;
PFNGLFRAMEBUFFERTEXTURELAYERPROC	glFramebufferTextureLayer= NULL;
PFNGLBINDFRAGDATALOCATIONPROC		glBindFragDataLocation= NULL;
PFNGLMINSAMPLESHADINGPROC			glMinSampleShading= NULL;
PFNGLDRAWBUFFERSPROC				glDrawBuffers= NULL;

PFNGLWAITSYNCPROC glWaitSync= NULL;
PFNGLFENCESYNCPROC glFenceSync= NULL;

//GLAPI void APIENTRY  ( * glClampColor ) (GLenum target, GLenum clamp);

//GLAPI const GLubyte * APIENTRY (*glGetStringi) (GLenum name, GLuint index);

void GetGLFunctions(
	void* (*GetProcAddressFunc)(const char* func_name),
	void (*FuncNotFoundCallback)(const char* func_name) )
{
	#define GET_PROC_ADDRESS(x) \
	x= reinterpret_cast<decltype(x)>( GetProcAddressFunc(#x) ); \
	if( !x && FuncNotFoundCallback ) \
		FuncNotFoundCallback(#x); \

	GET_PROC_ADDRESS( glCreateShader )
	GET_PROC_ADDRESS( glDeleteShader )
	GET_PROC_ADDRESS( glShaderSource )
	GET_PROC_ADDRESS( glCompileShader )
	GET_PROC_ADDRESS( glReleaseShaderCompiler )
	GET_PROC_ADDRESS( glGetShaderiv )
	GET_PROC_ADDRESS( glGetShaderInfoLog )

	GET_PROC_ADDRESS( glCreateProgram )
	GET_PROC_ADDRESS( glDeleteProgram )
	GET_PROC_ADDRESS( glDetachShader )
	GET_PROC_ADDRESS( glAttachShader )
	GET_PROC_ADDRESS( glLinkProgram )
	GET_PROC_ADDRESS( glUseProgram )
	GET_PROC_ADDRESS( glGetProgramiv )
	GET_PROC_ADDRESS( glGetProgramInfoLog )

	GET_PROC_ADDRESS( glGetAttribLocation )
	GET_PROC_ADDRESS( glVertexAttribPointer )
	GET_PROC_ADDRESS( glVertexAttribIPointer )
	GET_PROC_ADDRESS( glEnableVertexAttribArray )
	GET_PROC_ADDRESS( glDisableVertexAttribArray )
	GET_PROC_ADDRESS( glBindAttribLocation )

	GET_PROC_ADDRESS( glGenBuffers )
	GET_PROC_ADDRESS( glBindBuffer )
	GET_PROC_ADDRESS( glBufferData )
	GET_PROC_ADDRESS( glBufferSubData )
	GET_PROC_ADDRESS( glDeleteBuffers )
	GET_PROC_ADDRESS( glTexBuffer )

	GET_PROC_ADDRESS( glGenVertexArrays )
	GET_PROC_ADDRESS( glBindVertexArray )
	GET_PROC_ADDRESS( glDeleteVertexArrays )

	GET_PROC_ADDRESS( glMultiDrawElements )
	GET_PROC_ADDRESS( glMultiDrawElementsBaseVertex )
	GET_PROC_ADDRESS( glMultiDrawArrays )
	GET_PROC_ADDRESS( glDrawElementsBaseVertex )

	GET_PROC_ADDRESS( glGetUniformLocation )
	GET_PROC_ADDRESS( glUniform1i )
	GET_PROC_ADDRESS( glUniformMatrix4fv )
	GET_PROC_ADDRESS( glUniformMatrix3fv )
	GET_PROC_ADDRESS( glUniform3f )
	GET_PROC_ADDRESS( glUniform4f )
	GET_PROC_ADDRESS( glUniform1f )

	GET_PROC_ADDRESS( glActiveTexture )
	GET_PROC_ADDRESS( glGenerateMipmap )
	GET_PROC_ADDRESS( glTexImage3D )
	GET_PROC_ADDRESS( glTexSubImage3D )

	GET_PROC_ADDRESS( glGenFramebuffers )
	GET_PROC_ADDRESS( glDeleteFramebuffers )
	GET_PROC_ADDRESS( glBindFramebuffer )
	GET_PROC_ADDRESS( glFramebufferTexture )
	GET_PROC_ADDRESS( glFramebufferTexture2D )
	GET_PROC_ADDRESS( glFramebufferTextureLayer )
	GET_PROC_ADDRESS( glBindFragDataLocation )
	GET_PROC_ADDRESS( glMinSampleShading )
	GET_PROC_ADDRESS( glDrawBuffers )

	GET_PROC_ADDRESS( glDrawElementsInstanced )

	GET_PROC_ADDRESS( glWaitSync )
	GET_PROC_ADDRESS( glFenceSync )

#undef GET_PROC_ADDRESS
}
