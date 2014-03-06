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

out vec3 oNormal_c;		// Vertex normal in camera space
out vec3 oTangent_c;	// Vertex tangent in camera space
out vec3 oBitangent_c;	// Vertex bitangent in camera space
out vec2 oUV;			// UV coordinate
out vec3 oPos_w;		// Vertex position in world space
out vec3 oEye_c;		// Eye vector in camera space
out vec3 oLight_c;		// Light vector in camera space
out vec3 oEye_t;		// Eye vector in tangent space
out vec3 oLight_t;		// Light vector in tangent space

uniform mat4 m_model;		// Model matrix
uniform mat4 m_view;		// View matrix
uniform mat4 m_mvp;			// Model-view-projection matrix
uniform mat4 m_itmv;		// Inverse transposed model-view matrix
uniform vec3 v_lightPos_w;	// Light position in world space

// Main entry point
void main(){
	// Vertex position in clip space
	gl_Position =  m_mvp * vec4(iPos_m, 1);

	// Vertex position in world space
	oPos_w = (m_model * vec4(iPos_m, 1)).xyz;
	
	// Vertex normal in camera space
	oNormal_c = (m_itmv * vec4(normalize(iNormal_m), 0)).xyz;
	
	// Vertex tangent and bitangent in camera space
	oTangent_c = (m_itmv * vec4(normalize(iTangent_m), 0)).xyz;
	oBitangent_c = (m_itmv * vec4(normalize(iBitangent_m), 0)).xyz;
	
	// Construt matrix from camera to tangent space
	mat3 TBN = transpose(mat3(
        oTangent_c,
        oBitangent_c,
        oNormal_c
    ));

	// Eye vector, i.e. from vertex to camera in tangent space
	vec3 pos_c = (m_view * m_model * vec4(iPos_m, 1)).xyz;
	oEye_c = vec3(0,0,0) - pos_c;
    oEye_t =  TBN * oEye_c;

	// Light vector, i.e. from vertex to light in tangent space
	vec3 lightPos_c = (m_view * vec4(v_lightPos_w, 1)).xyz;
	oLight_c = lightPos_c + oEye_c;
	oLight_t = TBN * oLight_c;
	
	// Pass UVs
	oUV = iUV;
}