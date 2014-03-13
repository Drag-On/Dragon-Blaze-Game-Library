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

layout(location = 0) in vec3 iPos_m;		// Vertex position in model space
layout(location = 1) in vec2 iUV;			// UV coordinate
layout(location = 2) in vec3 iNormal_m;		// Vertex normal in model space
layout(location = 3) in vec3 iTangent_m;	// Vertex tangent in model space
layout(location = 4) in vec3 iBitangent_m;	// Vertex bitangent in model space

out vec3 oNormal_w;		// Vertex normal in world space
out vec2 oUV;			// UV coordinate
out vec3 oPos_w;		// Vertex position in world space
out vec3 oEye_w;		// Eye vector in world space
out vec3 oLight_w;		// Light vector in world space
out mat3 oM_TBN;		// TBN matrix

uniform mat4 m_model;		// Model matrix
uniform mat4 m_view;		// View matrix
uniform mat4 m_mvp;			// Model-view-projection matrix
uniform mat4 m_mv;			// Model-view matrix
uniform mat4 m_itm;			// Inverse transposed model matrix
uniform mat4 m_itv;			// Inverse transposed view matrix
uniform vec3 v_lightPos_w;	// Light position in world space

// Main entry point
void main(){
	// Vertex position in clip space
	gl_Position =  m_mvp * vec4(iPos_m, 1);

	// Vertex position in world space
	oPos_w = (m_model * vec4(iPos_m, 1)).xyz;
	
	// Vertex normal in world space
	mat3 m_normal = mat3(m_itm);
	oNormal_w = m_normal * iNormal_m;
	
	// Vertex tangent and bitangent in world space
	//vec3 bitangent_m = cross(iNormal_m, iTangent_m);
	vec3 tangent_w = m_normal * iTangent_m;
	vec3 bitangent_w = m_normal * iBitangent_m;
	
	// Construct matrix from tangent to world space
	oM_TBN = mat3(
        tangent_w,
        bitangent_w,
        oNormal_w
    );

	// Eye vector, i.e. from vertex to camera in world space
	vec3 pos_c = (m_mv * vec4(iPos_m, 1)).xyz;
	vec3 eye_c = vec3(0,0,0) - pos_c;
	oEye_w = mat3(m_itv) * eye_c;

	// Light vector, i.e. from vertex to light in world space
	oLight_w = v_lightPos_w + oEye_w;
	
	// Pass UVs
	oUV = iUV;
}