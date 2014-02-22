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
// This fragment shader implements
//	* Diffuse light
//	* Specular highlights
//	* Ambient light
//////////////////////////////////////////////////////////////////////

#version 330 core

in vec3 oNormal_c;	// Vertex normal in camera space
in vec2 oUV;		// UV coordinate
in vec3 oPos_w;		// Vertex position in world space
in vec3 oEye_c;		// Eye vector in camera space
in vec3 oLight_c;	// Light vector in camera space

out vec3 oColor;	// Fragment color

uniform sampler2D tex_diffuse;	// Diffuse texture
uniform vec3 v_lightPos_w;		// Light position in world space
uniform vec3 v_lightColor;		// Light color
uniform vec3 v_ambientLight;	// Ambient light color

// Main entry point
void main(){
	// Calculate diffuse component
	vec3 n = normalize(oNormal_c);
	vec3 l = normalize(oLight_c);
	float cosTheta = clamp(dot(n, l), 0, 1);
 
	vec3 matDiffuse = texture(tex_diffuse, oUV).rgb;
	float dist = length(v_lightPos_w - oPos_w);
	oColor = v_ambientLight + matDiffuse * v_lightColor * cosTheta / (dist * dist);
}