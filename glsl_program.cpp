#include "panzer_ogl_lib.hpp"

#include "glsl_program.hpp"

#define HANDLE_NOT_CREATED 0x7fffffff

static bool LoadShader( const char* file_name, std::string& out_string )
{
	unsigned int f_size;
	FILE* file;

	file= fopen( file_name, "rb" );
	if( file == nullptr )
		return false;

	fseek( file, 0, SEEK_END );
	f_size= ftell( file );
	fseek( file, 0, SEEK_SET );

	out_string.resize( f_size+1, 0 );

	fread( (char*)out_string.data(), 1, f_size, file );
	fclose( file );

	return true;
}

r_GLSLProgram::r_GLSLProgram()
	: prog_handle_(HANDLE_NOT_CREATED)
	, frag_handle_(HANDLE_NOT_CREATED), vert_handle_(HANDLE_NOT_CREATED), geom_handle_(HANDLE_NOT_CREATED)
{}

r_GLSLProgram::~r_GLSLProgram()
{
	Destroy();
}

bool r_GLSLProgram::Load( const char* frag_file, const char* vert_file, const char* geom_file )
{
	bool ok= true;
	if( frag_file != nullptr )
		ok|= LoadShader( frag_file, frag_text_ );

	if( vert_file != nullptr )
		ok|= LoadShader( vert_file, vert_text_ );

	if( geom_file != nullptr )
		ok|= LoadShader( geom_file, geom_text_ );

	return ok;
}

void r_GLSLProgram::ShaderSource( const char* frag_src, const char* vert_src, const char* geom_src )
{
	if( frag_src != nullptr )
		frag_text_= frag_src;
	else
		frag_text_= "";

	if( vert_src != nullptr )
		vert_text_= vert_src;
	else
		vert_text_= "";

	if( geom_src != nullptr )
		geom_text_= geom_src;
	else
		geom_text_= "";
}

void r_GLSLProgram::SetAttribLocation( const char* name, unsigned int location )
{
	Attrib_s a;
	a.name= name;
	a.location= location;
	attribs_.push_back(a);
}

void r_GLSLProgram::Define( const char* def )
{
	std::string str( "#define " );
	str+= def;
	str+= "\n";
	defines_.push_back( str );
}

void r_GLSLProgram::Create()
{
	int len;
	int compile_status;
	char build_log[4096];

	const unsigned int max_shader_substrings= 128;
	const char* shader_text_buf[ max_shader_substrings ];
	GLint shader_strings_len[ max_shader_substrings ];

	for( unsigned int i= 0; i < defines_.size(); i++ )
	{
		shader_text_buf[i]= defines_[i].data();
		shader_strings_len[i]= defines_[i].length();
	}

	prog_handle_= glCreateProgram();

	if( frag_text_.length() != 0 )
	{
		frag_handle_= glCreateShader( GL_FRAGMENT_SHADER );

		shader_text_buf[ defines_.size() ]= frag_text_.data();
		shader_strings_len[ defines_.size() ]= frag_text_.length();
		glShaderSource( frag_handle_, defines_.size() + 1, shader_text_buf, shader_strings_len );

		glCompileShader( frag_handle_ );
		glGetShaderiv( frag_handle_ , GL_COMPILE_STATUS, &compile_status );
		if( !compile_status )
		{
			glGetShaderInfoLog( frag_handle_, sizeof(build_log), &len, build_log );
			printf( "fragment shader error:\n\n%s\nerrors:\n%s\n", frag_text_.data(), build_log );
			compile_status= 1;
		}
		glAttachShader( prog_handle_, frag_handle_ );
	}

	if( vert_text_.length() != 0 )
	{
		vert_handle_= glCreateShader( GL_VERTEX_SHADER );

		shader_text_buf[ defines_.size() ]= vert_text_.data();
		shader_strings_len[ defines_.size() ]= vert_text_.length();
		glShaderSource( vert_handle_, defines_.size() + 1, shader_text_buf, shader_strings_len );

		glCompileShader( vert_handle_ );
		glGetShaderiv( vert_handle_ , GL_COMPILE_STATUS, &compile_status );
		if( !compile_status )
		{
			glGetShaderInfoLog( vert_handle_, sizeof(build_log), &len, build_log );
			printf( "vertex shader error:\n\n%s\nerrors:\n%s\n", vert_text_.data(), build_log );
			compile_status= 1;
		}
		glAttachShader( prog_handle_, vert_handle_ );
	}

	if( geom_text_.length() != 0 )
	{
		geom_handle_= glCreateShader( GL_GEOMETRY_SHADER );

		shader_text_buf[ defines_.size() ]= geom_text_.data();
		shader_strings_len[ defines_.size() ]= geom_text_.length();
		glShaderSource( geom_handle_, defines_.size() + 1, shader_text_buf, shader_strings_len );

		glCompileShader( geom_handle_ );
		glGetShaderiv( geom_handle_ , GL_COMPILE_STATUS, &compile_status );
		if( !compile_status )
		{
			glGetShaderInfoLog( geom_handle_, sizeof(build_log), &len, build_log );
			printf( "gemetry shader error:\n\n%s\nerrors:\n%s\n", geom_text_.data(), build_log );
			compile_status= 1;
		}
		glAttachShader( prog_handle_, geom_handle_ );
	}

	for( const Attrib_s& attrib : attribs_ )
		glBindAttribLocation( prog_handle_, attrib.location, attrib.name.data() );

	glLinkProgram( prog_handle_ );
	glGetProgramiv( prog_handle_, GL_LINK_STATUS, &compile_status );
	if( !compile_status )
	{
		glGetProgramInfoLog( prog_handle_, sizeof(build_log), &len, build_log );
		printf( "shader link error:\n %s\n", build_log );
		return;
	}

	FindUniforms();
}

void r_GLSLProgram::Destroy()
{
	if( prog_handle_ != HANDLE_NOT_CREATED )
	{
		glDeleteProgram( prog_handle_ );
		prog_handle_= HANDLE_NOT_CREATED;
	}
	if( frag_handle_ != HANDLE_NOT_CREATED )
	{
		glDeleteShader( frag_handle_ );
		frag_handle_= HANDLE_NOT_CREATED;
	}
	if( vert_handle_ != HANDLE_NOT_CREATED )
	{
		glDeleteShader( vert_handle_ );
		vert_handle_= HANDLE_NOT_CREATED;
	}
	if( geom_handle_ != HANDLE_NOT_CREATED )
	{
		glDeleteShader( geom_handle_ );
		geom_handle_= HANDLE_NOT_CREATED;
	}

	vert_text_.clear();
	frag_text_.clear();
	geom_text_.clear();

	defines_.clear();
	uniforms_.clear();
	attribs_.clear();
}

void r_GLSLProgram::Bind() const
{
	if( prog_handle_ != HANDLE_NOT_CREATED )
		glUseProgram( prog_handle_ );
}

void r_GLSLProgram::Uniform( const char* name, int i )
{
	int u= GetUniform( name );
	if( u == -1 ) return;

	glUniform1i( u, i );
}

void r_GLSLProgram::Uniform( const char* name, int* i, unsigned int count )
{
	int u= GetUniform( name );
	if( u == -1 ) return;

	for( unsigned int c= 0; c< count; c++ )
		glUniform1i( u + c, i[c] );
}

void r_GLSLProgram::Uniform( const char* name, float f )
{
	int u= GetUniform( name );
	if( u == -1 ) return;

	glUniform1f( u, f );
}

void r_GLSLProgram::Uniform( const char* name, const float* f, unsigned int count )
{
	int u= GetUniform( name );
	if( u == -1 ) return;

	// TODO - use something, like glUniformfv
	for( unsigned int i= 0; i < count; i++ )
		glUniform1f( u + i, f[i] );
}

void r_GLSLProgram::Uniform( const char* name, const m_Vec2& v )
{
	int u= GetUniform( name );
	if( u == -1 ) return;

	glUniform2f( u, v.x, v.y );
}

void r_GLSLProgram::Uniform( const char* name, const m_Vec2* v, unsigned int count )
{
	int u= GetUniform( name );
	if( u == -1 ) return;

	// TODO - use something, like glUniformfv
	for( unsigned int i= 0; i < count; i++ )
		glUniform2f( u + i, v[i].x, v[i].y );
}

void r_GLSLProgram::Uniform( const char* name, const m_Vec3& v )
{
	int u= GetUniform( name );
	if( u == -1 ) return;

	glUniform3f( u, v.x, v.y, v.z );
}

void r_GLSLProgram::Uniform( const char* name, const m_Vec3* v, unsigned int count )
{
	int u= GetUniform( name );
	if( u == -1 ) return;

	// TODO - use something, like glUniformfv
	for( unsigned int i= 0; i < count; i++ )
		glUniform3f( u + i, v[i].x, v[i].y, v[i].z );
}

void r_GLSLProgram::Uniform( const char* name, const m_Mat3& m )
{
	int u= GetUniform( name );
	if( u == -1 ) return;

	glUniformMatrix3fv( u, 1, GL_FALSE, m.value );
}

void r_GLSLProgram::Uniform( const char* name, const m_Mat3* m, unsigned int count )
{
	int u= GetUniform( name );
	if( u == -1 ) return;

	glUniformMatrix3fv( u, count, GL_FALSE, m->value );
}

void r_GLSLProgram::Uniform( const char* name, const m_Mat4& m )
{
	int u= GetUniform( name );
	if( u == -1 ) return;

	glUniformMatrix4fv( u, 1, GL_FALSE, m.value );
}

void r_GLSLProgram::Uniform( const char* name, const m_Mat4* m, unsigned int count )
{
	int u= GetUniform( name );
	if( u == -1 ) return;

	glUniformMatrix4fv( u, count, GL_FALSE, m->value );
}

void r_GLSLProgram::Uniform( const char* name, float f0, float f1, float f2, float f3 )
{
	int u= GetUniform( name );
	if( u == -1 )
		return;

	glUniform4f( u, f0, f1, f2, f3 );
}

void r_GLSLProgram::FindUniforms()
{
	int uniform_count;
	glGetProgramiv( prog_handle_, GL_ACTIVE_UNIFORMS, &uniform_count );

	int max_uniform_length;
	glGetProgramiv( prog_handle_, GL_ACTIVE_UNIFORM_MAX_LENGTH, &max_uniform_length );
	std::vector<char> buff( max_uniform_length + 2 );

	for( int i= 0; i < uniform_count; i++ )
	{
		int length;
		int size;
		GLenum type;

		glGetActiveUniform(
			prog_handle_, i,
			buff.size(), &length,
			&size, &type,
			buff.data() );

		// HACK. Arrays have name like "my_array_uniform[0]". Delete indexation from name.
		for( int j= 0; j < length; j++ )
			if( buff[j] == '[' )
			{
				length= j;
				break;
			}

		uniforms_.emplace_back();
		uniforms_.back().name= std::string( buff.data(), length );
		uniforms_.back().id= glGetUniformLocation( prog_handle_, uniforms_.back().name.data() );
	}
}

int r_GLSLProgram::GetUniform( const char* name )
{
	for( const Uniform_s& uniform : uniforms_ )
	{
		if( strcmp( uniform.name.data(), name ) == 0 )
			return uniform.id;
	}
	return -1;
}
