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
// This vertex shader implements
//	* Diffuse light
//	* Specular highlights
//	* Ambient light
//////////////////////////////////////////////////////////////////////

#version 330 core

layout(location = 0) in vec3 i_v3_Pos_m;	// Vertex position in model space
layout(location = 1) in vec2 i_v2_UV;		// UV coordinate
layout(location = 2) in vec3 i_v3_Normal_m;	// Vertex normal in model space

out vec3 v3_normal_c;	// Vertex normal in camera space
out vec2 v2_uv;			// UV coordinate
out vec3 v3_pos_w;		// Vertex position in world space
out vec3 v3_eye_c;		// Eye vector in camera space
out vec3 v3_light_c;	// Light vector in camera space

uniform mat4 M;				// Model matrix
uniform mat4 V;				// View matrix
uniform mat4 MV;			// Model-view matrix
uniform mat4 MVP;			// Model-view-projection matrix
uniform mat4 ITMV;			// Inversed transposed model-view matrix
uniform vec3 v3_lightPos_w;	// Light position in world space

// Main entry point
void main(){
	// Vertex position in clip space
	gl_Position =  MVP * vec4(i_v3_Pos_m, 1);

	// Vertex position in world space
	v3_pos_w = (M * vec4(i_v3_Pos_m, 1)).xyz;

	// Eye vector, i.e. from vertex to camera in camera space
	vec3 v3_pos_c = (MV * vec4(i_v3_Pos_m, 1)).xyz;
	v3_eye_c = vec3(0,0,0) - v3_pos_c;

	// Light vector, i.e. from vertex to light in camera space
	vec3 v3_lightPos_c = (V * vec4(v3_lightPos_w, 1)).xyz;
	v3_light_c = v3_lightPos_c + v3_eye_c;

	// Vertex normal in camera space
	v3_normal_c = (ITMV * vec4(i_v3_Normal_m, 0)).xyz;
	
	// Pass UVs
	v2_uv = i_v2_UV;
}