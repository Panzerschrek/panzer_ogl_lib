#pragma once
#include "panzer_ogl_lib.hpp"

class r_PolygonBuffer
{
public:
	r_PolygonBuffer();
	r_PolygonBuffer( const r_PolygonBuffer& )= delete;
	r_PolygonBuffer( r_PolygonBuffer&& other ) noexcept;
	~r_PolygonBuffer();

	r_PolygonBuffer& operator=( const r_PolygonBuffer& )= delete;
	r_PolygonBuffer& operator=( r_PolygonBuffer&& other ) noexcept;

	void VertexData( const void* data, size_t d_size, size_t v_size );
	void VertexSubData( const void* data,size_t d_size, size_t shift );

	void IndexData( const void* data, size_t size, GLenum d_type, GLenum p_type );
	void IndexSubData( const void* data, size_t size, size_t shift );
	void VertexAttribPointer( int v_attrib, int components, GLenum type, bool normalize, size_t shift );
	void VertexAttribPointerInt( int v_attrib, int components, GLenum type, size_t stride );

	void Bind() const;

	void Draw() const;

	inline void SetPrimitiveType( GLenum t )
	{
		primitive_type_= t;
	}

	unsigned int GetVertexDataSize() const;
	unsigned int GetIndexDataSize() const;

private:
	unsigned int vertex_data_size_;
	unsigned int vertex_size_;

	GLenum index_data_type_;//type of index ( GL_UNSIGNED_INT / GL_UNSIGNED_SHORT )
	unsigned int index_data_size_;
	GLenum primitive_type_;

	GLuint v_buffer_, i_buffer_;
	GLuint v_array_object_;
};
