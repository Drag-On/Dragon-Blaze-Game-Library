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
//	* Normal mapping
//////////////////////////////////////////////////////////////////////

#version 330 core

//////////////////////////////////////////////////////////////////////
// Variables
//////////////////////////////////////////////////////////////////////
layout(location = 0) in vec3 i_v3_Pos_m;		// Vertex position in model space
layout(location = 1) in vec2 i_v2_UV;			// UV coordinate
layout(location = 2) in vec3 i_v3_Normal_m;		// Vertex normal in model space
layout(location = 3) in vec3 i_v3_Tangent_m;	// Vertex tangent in model space
layout(location = 4) in vec3 i_v3_Bitangent_m;	// Vertex bitangent in model space

out vec3 v3_normal_w;	// Vertex normal in world space
out vec2 v2_uv;			// UV coordinate
out vec3 v3_pos_w;		// Vertex position in world space
out vec3 v3_eye_w;		// Eye vector in world space
out mat3 TBN;			// TBN matrix

uniform mat4 M;				// Model matrix
uniform mat4 MVP;			// Model-view-projection matrix
uniform mat4 ITM;			// Inverse transposed model matrix
uniform mat4 ITV;			// Inverse transposed view matrix

//////////////////////////////////////////////////////////////////////
// Main entry point
//////////////////////////////////////////////////////////////////////
void main()
{
	// Vertex position in clip space
	gl_Position =  MVP * vec4(i_v3_Pos_m, 1);

	// Vertex position in world space
	v3_pos_w = (M * vec4(i_v3_Pos_m, 1)).xyz;
	
	// Vertex normal in world space
	mat3 NORMAL = mat3(ITM);
	v3_normal_w = NORMAL * i_v3_Normal_m;
	
	// Vertex tangent and bitangent in world space
	//vec3 bitangent_m = cross(iNormal_m, iTangent_m);
	vec3 tangent_w = NORMAL * i_v3_Tangent_m;
	vec3 bitangent_w = NORMAL * i_v3_Bitangent_m;
	
	// Construct matrix from tangent to world space
	TBN = mat3(
        tangent_w,
        bitangent_w,
        v3_normal_w
    );

	// Eye vector, i.e. from vertex to camera in world space
	vec3 cam_w = (vec4(0,0,0,1) * ITV).xyz;
	v3_eye_w = normalize(cam_w - v3_pos_w);
	
	// Pass UVs
	v2_uv = i_v2_UV;
}