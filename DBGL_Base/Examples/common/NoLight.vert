//////////////////////////////////////////////////////////////////////
/// Dragon Blaze Game Library
///
/// Copyright (c) 2014 by Jan Moeller
///
/// This software is provided "as-is" and does not claim to be
/// complete or free of bugs in any way. It should work, but
/// it might also begin to hurt your kittens.
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// This vertex shader implements nothing spectacular ;)
//////////////////////////////////////////////////////////////////////

#version 330 core

layout(location = 0) in vec3 iPos_m;	// Vertex position in model space

uniform mat4 m_mvp;		// Model-view-projection matrix

// Main entry point
void main(){
	// Vertex position in clip space
	gl_Position =  m_mvp * vec4(iPos_m, 1);
}