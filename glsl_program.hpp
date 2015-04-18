#pragma once

#include <string>
#include <vector>

#include "panzer_ogl_lib.hpp"

#include "vec.hpp"
#include "matrix.hpp"

class r_GLSLProgram
{
public:
	 r_GLSLProgram();
    ~r_GLSLProgram();

	// returns false, if something wrong
    bool Load( const char* frag_file, const char* vert_file, const char* geom_file = NULL );
    void ShaderSource( const char* frag_src, const char* vert_src, const char* geom_src );

	void Create(); // compiles shader and link program object
	void Destroy(); // deletes shaders and program object

    void SetAttribLocation( const char* name, unsigned int location );

    void Uniform( const char* name, const m_Vec3& v);
    void Uniform( const char* name, int i );
	void Uniform( const char* name, int* i, unsigned int count );
    void Uniform( const char* name, const m_Mat4& m );
	void Uniform( const char* name, const m_Mat4* m, unsigned int count );
    void Uniform( const char* name, const m_Mat3& m );
    void Uniform( const char* name, float f );
    void Uniform( const char* name, float f0, float f1, float f2, float f3 );

    void Define( const char* def );

    void Bind() const;

private:
    void FindAllUniforms();
    void FindAllUniformsInShader( const char* shader_text );
    int FindUniform( const char* name );
    int GetUniform( const char* name );

private:
    GLuint prog_handle_;
    GLuint frag_handle_, vert_handle_, geom_handle_;
    std::string vert_text_;
    std::string frag_text_;
    std::string geom_text_;

    std::vector< std::string > defines_;

    struct Uniform_s
    {
    	std::string name;
    	GLint id;
    };
    std::vector<Uniform_s> uniforms_;

	struct Attrib_s
	{
		std::string name;
		GLint location;
	};
    std::vector<Attrib_s> attribs_;

};
