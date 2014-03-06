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
in vec3 oEye_t;		// Eye vector in tangent space
in vec3 oLight_t;	// Light vector in tangent space

out vec3 oColor;	// Fragment color

uniform sampler2D tex_diffuse;	// Diffuse texture
uniform sampler2D tex_normal;	// Diffuse texture
uniform vec3 v_lightPos_w;		// Light position in world space
uniform vec3 v_lightColor;		// Light color
uniform vec3 v_ambientLight;	// Ambient light color
uniform vec3 v_matSpecColor;	// Material specular color
uniform float f_matSpecWidth;	// Width of specular highlight, the higher, the thinner

// Main entry point
void main(){
	// Calculate normal in tangent space
	vec3 normal_t = normalize(texture2D(tex_normal, oUV).rgb * 2.0 - 1.0);

	// Calculate diffuse component
	vec3 n = normalize(normal_t);
	vec3 l = normalize(oLight_t);
	float cosTheta = clamp(dot(n, l), 0, 1);
	
	// Calculate specular component
	vec3 e = normalize(oEye_t);
	vec3 r = reflect(-l, n);
	float cosAlpha = clamp(dot(e, r), 0, 1);
 
	vec3 matDiffuse = texture(tex_diffuse, oUV).rgb;
	float dist = length(v_lightPos_w - oPos_w);
	oColor = 
		// Ambient
		v_ambientLight * matDiffuse +
		// Diffuse
		matDiffuse * v_lightColor * cosTheta / (dist * dist) +
		// Specular
		v_matSpecColor * v_lightColor * pow(cosAlpha, f_matSpecWidth) / (dist * dist);

}