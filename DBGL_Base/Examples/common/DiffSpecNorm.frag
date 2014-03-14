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
//	* Normal mapping
//////////////////////////////////////////////////////////////////////

#version 330 core

in vec3 v3_normal_w;// Vertex normal in world space
in vec2 v2_uv;		// UV coordinate
in vec3 v3_pos_w;	// Vertex position in world space
in vec3 v3_eye_w;	// Eye vector in world space
in vec3 v3_light_w;	// Light vector in world space
in mat3 TBN;		// TBN matrix from tangent- into world space

out vec3 color;	// Fragment color

uniform sampler2D tex_diffuse;	// Diffuse texture
uniform sampler2D tex_normal;	// Normal texture
uniform vec3 v3_lightPos_w;		// Light position in world space
uniform vec3 v3_lightColor;		// Light color
uniform vec3 v3_ambientLight;	// Ambient light color
uniform vec3 v3_matSpecColor;	// Material specular color
uniform float f_matSpecWidth;	// Width of specular highlight, the higher, the thinner

// Main entry point
void main(){
	// Calculate normal in camera space
	vec3 v3_normal_t = texture2D(tex_normal, v2_uv).rgb * 2.0 - 1.0;
	vec3 v3_normal_w = TBN * v3_normal_t;

	// Calculate diffuse component
	vec3 n = normalize(v3_normal_w);
	vec3 l = normalize(v3_light_w);
	float cosTheta = clamp(dot(n, l), 0, 1);
	
	// Calculate specular component
	vec3 e = normalize(v3_eye_w);
	vec3 r = reflect(-l, n);
	float cosAlpha = clamp(dot(e, r), 0, 1);
 
	vec3 matDiffuse = texture(tex_diffuse, v2_uv).rgb;
	float dist = length(v3_lightPos_w - v3_pos_w);
	float distSquare = dist * dist;
	color = 
		// Ambient
		v3_ambientLight * matDiffuse +
		// Diffuse
		matDiffuse * v3_lightColor * cosTheta / distSquare +
		// Specular
		v3_matSpecColor * v3_lightColor * pow(cosAlpha, f_matSpecWidth) / distSquare;

}