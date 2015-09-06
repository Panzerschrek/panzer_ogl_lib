#pragma once

#include "panzer_ogl_lib.hpp"

class r_OGLState
{
public:

	static const float default_clear_color[4];
	static const float default_clear_depth;
	static const GLenum default_cull_face_mode;
	static const bool default_depth_mask;

	r_OGLState(){}
	~r_OGLState(){}
	//constructor for full initialazing
	r_OGLState(
		bool blend, bool cull_face, bool depth_test, bool program_point_size,
		const GLenum* blend_func,
		const float* clear_color= default_clear_color,
		float clear_depth= default_clear_depth,
		GLenum cull_face_mode= default_cull_face_mode,
		bool depth_mask= default_depth_mask );

	// State on OpenGL startup
	void InitialState();

	bool blend;
	bool cull_face;
	bool depth_test;
	bool program_point_size;

	GLenum blend_func[2];
	float clear_color[4];
	float clear_depth;
	GLenum cull_face_mode;
	GLenum depth_func;
	bool depth_mask;
};

class r_OGLStateManager
{
public:
	static void SetState( const r_OGLState& state );//FORCE set state
	static void UpdateState( const r_OGLState& state );

	static const r_OGLState& GetState();

private:
	static r_OGLState state_;
};
