#include "polygon_buffer.hpp"

#define BUFFER_NOT_CREATED 0xffffffff

r_PolygonBuffer::r_PolygonBuffer()
	: vertex_data_size_(0), vertex_size_(0)
	, index_data_type_(GL_NONE), index_data_size_(0)
	, primitive_type_(GL_NONE)
	, v_buffer_(BUFFER_NOT_CREATED), i_buffer_(BUFFER_NOT_CREATED)
	, v_array_object_(BUFFER_NOT_CREATED)
{
}

r_PolygonBuffer::~r_PolygonBuffer()
{
}

void r_PolygonBuffer::VertexData( const void* data, unsigned int d_size, unsigned int v_size )
{
	if( v_array_object_ == BUFFER_NOT_CREATED )
		glGenVertexArrays( 1, &v_array_object_ );
	glBindVertexArray( v_array_object_ );

	if( v_buffer_ == BUFFER_NOT_CREATED )
		glGenBuffers( 1, &v_buffer_ );

	glBindBuffer( GL_ARRAY_BUFFER, v_buffer_ );
	glBufferData( GL_ARRAY_BUFFER, d_size, data, GL_STATIC_DRAW );

	vertex_data_size_= d_size;
	vertex_size_= v_size;
}

void r_PolygonBuffer::VertexSubData( const void* data, unsigned int d_size, unsigned int shift )
{
	if( v_buffer_ == BUFFER_NOT_CREATED || v_array_object_ == BUFFER_NOT_CREATED )
		return;
	glBindVertexArray( v_array_object_ );

	glBindBuffer( GL_ARRAY_BUFFER, v_buffer_ );
	glBufferSubData( GL_ARRAY_BUFFER, shift, d_size, data );
}

void r_PolygonBuffer::IndexData( const void* data, unsigned int size, GLenum d_type, GLenum p_type )
{
	if( v_array_object_ == BUFFER_NOT_CREATED )
		glGenVertexArrays( 1, &v_array_object_ );
	glBindVertexArray( v_array_object_ );

	if( i_buffer_ == BUFFER_NOT_CREATED )
		glGenBuffers( 1, &i_buffer_ );

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, i_buffer_ );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW );

	index_data_size_= size;
	index_data_type_= d_type;
	primitive_type_= p_type;
}

void r_PolygonBuffer::IndexSubData( const void* data, unsigned int size, int shift )
{
	if( i_buffer_ == BUFFER_NOT_CREATED || v_array_object_ == BUFFER_NOT_CREATED  )
		return;

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, i_buffer_ );
	glBufferSubData( GL_ELEMENT_ARRAY_BUFFER, shift, size, data );
}

void r_PolygonBuffer::Bind() const
{
	if( v_array_object_ != BUFFER_NOT_CREATED )
		glBindVertexArray( v_array_object_ );
	//glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, i_buffer_ );
}

void r_PolygonBuffer::Destroy()
{
	if( v_buffer_ != BUFFER_NOT_CREATED )
	{
		glDeleteBuffers( 1, &v_buffer_ );
		v_buffer_= BUFFER_NOT_CREATED;
	}
	if( i_buffer_ != BUFFER_NOT_CREATED )
	{
		glDeleteBuffers( 1, &i_buffer_ );
		i_buffer_= BUFFER_NOT_CREATED;
	}
	if( v_array_object_ != BUFFER_NOT_CREATED )
	{
		glDeleteVertexArrays( 1, &v_array_object_ );
		v_array_object_= BUFFER_NOT_CREATED;
	}
}

void r_PolygonBuffer::Show() const
{
	Bind();

	int s;
	if( i_buffer_ == BUFFER_NOT_CREATED )
	{
		if( v_buffer_ == BUFFER_NOT_CREATED )
			return;
		s= vertex_data_size_ / vertex_size_;
		glDrawArrays( primitive_type_, 0, s );
	}
	else
	{
		if( v_buffer_ == BUFFER_NOT_CREATED )
			return;
		s= index_data_type_ == GL_UNSIGNED_INT ? 4 : 2;
		s= index_data_size_ / s;
		glDrawElements( primitive_type_, s, index_data_type_, NULL );
	}
}

void r_PolygonBuffer::VertexAttribPointer( int v_attrib, int components, GLenum type, bool normalize, int shift )
{
	if( v_array_object_ == BUFFER_NOT_CREATED || v_buffer_ == BUFFER_NOT_CREATED )
		return;

	glBindVertexArray( v_array_object_ );
	glBindBuffer( GL_ARRAY_BUFFER, v_buffer_ );

	glEnableVertexAttribArray( v_attrib );
	glVertexAttribPointer( v_attrib, components, type, normalize, vertex_size_, (void*) shift );
}

void r_PolygonBuffer::VertexAttribPointerInt( int v_attrib, int components, GLenum type, int shift )
{
	if( v_array_object_ == BUFFER_NOT_CREATED || v_buffer_ == BUFFER_NOT_CREATED )
		return;

	glBindVertexArray( v_array_object_ );
	glBindBuffer( GL_ARRAY_BUFFER, v_buffer_ );

	glEnableVertexAttribArray( v_attrib );
	glVertexAttribIPointer( v_attrib, components, type, vertex_size_, (void*) shift );
}
