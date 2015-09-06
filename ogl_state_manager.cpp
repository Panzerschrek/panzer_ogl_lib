#include "ogl_state_manager.hpp"

const float r_OGLState::default_clear_color[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
const float r_OGLState::default_clear_depth= 1.0f;
const GLenum r_OGLState::default_cull_face_mode= GL_FRONT;
const bool r_OGLState::default_depth_mask= true;

r_OGLState r_OGLStateManager::state_;

void r_OGLState::InitialState()
{
	blend= false;
	cull_face= false;
	depth_test= false;
	program_point_size= false;

	blend_func[0]= blend_func[1]= GL_ONE;
	clear_color[0]= clear_color[1]= clear_color[2]= clear_color[3]= 0.0f;
	clear_depth= 1.0f;
	cull_face_mode= GL_BACK;
	depth_func= GL_LEQUAL;
	depth_mask= true;
}

r_OGLState::r_OGLState(
	bool blend_in, bool cull_face_in, bool depth_test_in, bool program_point_size_in,
	const GLenum* blend_func_in, const float* clear_color_in, float clear_depth_in, GLenum cull_face_mode_in, bool depth_mask_in )
	: blend(blend_in), cull_face(cull_face_in), depth_test(depth_test_in), program_point_size(program_point_size_in)
	,clear_depth(clear_depth_in), cull_face_mode(cull_face_mode_in), depth_mask(depth_mask_in)
	,depth_func(GL_LEQUAL)
{
	blend_func[0]= blend_func_in[0];
	blend_func[1]= blend_func_in[1];
	clear_color[0]= clear_color_in[0];
	clear_color[1]= clear_color_in[1];
	clear_color[2]= clear_color_in[2];
	clear_color[3]= clear_color_in[3];
}

void r_OGLStateManager::SetState( const r_OGLState& state )
{
	state_= state;
	glBlendFunc( state.blend_func[0], state.blend_func[1] );
	glClearColor( state.clear_color[0], state.clear_color[1], state.clear_color[2], state.clear_color[3] );
	glClearDepth( state.clear_depth );
	glCullFace( state.cull_face_mode );
	glDepthFunc( state.depth_func );
	glDepthMask( state.depth_mask );

	if( state.blend )
		glEnable( GL_BLEND );
	else
		glDisable( GL_BLEND );

	if( state.cull_face )
		glEnable( GL_CULL_FACE );
	else
		glDisable( GL_CULL_FACE );

	if( state.depth_test )
		glEnable( GL_DEPTH_TEST );
	else
		glDisable( GL_DEPTH_TEST );

	if( state.program_point_size )
		glEnable( GL_PROGRAM_POINT_SIZE );
	else
		glDisable( GL_PROGRAM_POINT_SIZE );
}


void r_OGLStateManager::UpdateState( const r_OGLState& state )
{
	if( state_.blend != state.blend )
		( state.blend ? glEnable : glDisable )( GL_BLEND );

	if( state_.cull_face != state.cull_face )
		( state.cull_face ? glEnable : glDisable )( GL_CULL_FACE );

	if( state_.depth_test != state.depth_test )
		( state.depth_test ? glEnable : glDisable )( GL_DEPTH_TEST );

	if( state_.program_point_size != state.program_point_size )
		( state.program_point_size ? glEnable : glDisable )( GL_PROGRAM_POINT_SIZE );

	if( state_.blend_func[0] != state.blend_func[0] || state_.blend_func[1] != state.blend_func[1] )
		glBlendFunc( state.blend_func[0], state.blend_func[1] );

	if( state_.clear_color[0] != state.clear_color[0] || state_.clear_color[1] != state.clear_color[1] ||
			state_.clear_color[2] != state.clear_color[2] || state_.clear_color[2] != state.clear_color[2] )
		glClearColor( state.clear_color[0], state.clear_color[1], state.clear_color[2], state.clear_color[3] );

	if( state_.clear_depth != state.clear_depth )
		glClearDepth( state.clear_depth );

	if( state_.cull_face_mode != state.cull_face_mode )
		glCullFace( state.cull_face_mode );

	if( state_.depth_func != state.depth_func )
		glDepthFunc( state.depth_func );
	if( state_.depth_mask != state.depth_mask )
		glDepthMask( state.depth_mask );

	state_= state;
}

const r_OGLState& r_OGLStateManager::GetState()
{
	return state_;
}
