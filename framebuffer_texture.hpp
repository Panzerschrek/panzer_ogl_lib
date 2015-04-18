#pragma once

#include "panzer_ogl_lib.hpp"

class r_FramebufferTexture
{
	friend class r_Framebuffer;

public:
	enum TextureFormat
	{
		FORMAT_UNKNOWN = 0,

		//one component formats:
		FORMAT_R8 , FORMAT_R8S , FORMAT_R8UI , FORMAT_R8I ,
		FORMAT_R16, FORMAT_R16S, FORMAT_R16UI, FORMAT_R16I, FORMAT_R16F,
								FORMAT_R32UI, FORMAT_R32I, FORMAT_R32F,

		//two component formats:
		FORMAT_RG8 , FORMAT_RG8S , FORMAT_RG8UI , FORMAT_RG8I ,
		FORMAT_RG16, FORMAT_RG16S, FORMAT_RG16UI, FORMAT_RG16I, FORMAT_RG16F,
		                           FORMAT_RG32UI, FORMAT_RG32I, FORMAT_RG32F,

		//four component formats:
		FORMAT_RGBA8 , FORMAT_RGBA8S , FORMAT_RGBA8UI , FORMAT_RGBA8I ,
		FORMAT_RGBA16, FORMAT_RGBA16S, FORMAT_RGBA16UI, FORMAT_RGBA16I, FORMAT_RGBA16F,
									   FORMAT_RGBA32UI, FORMAT_RGBA32I, FORMAT_RGBA32F,

		//depth formats:
		FORMAT_DEPTH16, FORMAT_DEPTH32, FORMAT_DEPTH32F, FORMAT_DEPTH24_STENCIL8
	};

	enum TextureWrapMode
	{
		WRAP_MODE_UNKNOWN = 0,
		WRAP_MODE_CLAMP,
		WRAP_MODE_REPEAT
	};

	enum TextureFiltration
	{
		FILTRATION_UNKNOWN = 0,
		FILTRATION_NEAREST,
		FILTRATION_LINEAR,
		FILTRATION_NEAREST_MIPMAP_NEAREST,
		FILTRATION_NEAREST_MIPMAP_LINEAR,
		FILTRATION_LINEAR_MIPMAP_NEAREST,
		FILTRATION_LINEAR_MIPMAP_LINEAR,
	};

	r_FramebufferTexture();
	~r_FramebufferTexture();

	//create and bind texture
	void Create( TextureFormat format, unsigned int width, unsigned int height );
	void Create( TextureFormat format, unsigned int width, unsigned int height, const unsigned char* data );
	void Create( TextureFormat format, unsigned int width, unsigned int height, const float* data );
	void Destroy();


	//load texture data into GPU. Texture must be created and binded before.
	template<class T> void SetData( const T* data );

	//texture params modification methods. Texture must be created and binded before it.
	void SetWrapMode( TextureWrapMode mode );
	void SetFiltration( TextureFiltration filter_min, TextureFiltration filter_mag );
	void BuildMips();

	//bind texture and set active texture unit.
	void Bind( unsigned int unit = 0 ) const;

	unsigned int Width() const;
	unsigned int Height() const;
	bool IsDepthTexture() const;
	bool Created() const;

private:
	static GLenum FormatToInternalFormat( TextureFormat format );
	static GLenum FormatToBaseFormat( TextureFormat format );
	static GLenum FiltrationToGLFiltration( TextureFiltration filtration );
	static GLenum WrapModeToGLWrapMode( TextureWrapMode mode );

private:
	bool created_;
	GLuint tex_id_;

	TextureFormat format_;
	TextureWrapMode wrap_mode_;
	TextureFiltration filter_min_, filter_mag_;

	unsigned int size_x_, size_y_;

};

template< class T >
void r_FramebufferTexture::SetData( const T* data )
{
	//hack to privent call of method with unknown type
	data->InvalidTypeForTextureData();
}


template<>
inline void r_FramebufferTexture::SetData<float>( const float* data )
{
	GLenum gl_format= FormatToInternalFormat( format_ );
	GLenum component_format= FormatToBaseFormat( format_ );

	glTexImage2D( GL_TEXTURE_2D, 0, gl_format,
				  size_x_, size_y_, 0,
				  component_format, GL_FLOAT, data );
}

template<>
inline void r_FramebufferTexture::SetData<unsigned char>( const unsigned char* data )
{
	GLenum gl_format= FormatToInternalFormat( format_ );
	GLenum component_format= FormatToBaseFormat( format_ );

	GLenum data_type;
	switch( format_ )
	{
		case FORMAT_DEPTH24_STENCIL8:
			data_type= GL_UNSIGNED_INT_24_8; break;
		default:
			data_type= GL_UNSIGNED_BYTE;
	};
	glTexImage2D( GL_TEXTURE_2D, 0, gl_format,
				  size_x_, size_y_, 0,
				  component_format, data_type, data );
}


inline unsigned int r_FramebufferTexture::Width() const
{
	return size_x_;
}

inline unsigned int r_FramebufferTexture::Height() const
{
	return size_y_;
}

inline bool r_FramebufferTexture::Created() const
{
	return created_;
}
