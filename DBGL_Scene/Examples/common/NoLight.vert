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

layout(location = 0) in vec3 i_v3_Pos_m; // Vertex position in model space

uniform mat4 MVP; // Model-view-projection matrix

// Main entry point
void main(){
	// Vertex position in clip space
	gl_Position =  MVP * vec4(i_v3_Pos_m, 1);
}