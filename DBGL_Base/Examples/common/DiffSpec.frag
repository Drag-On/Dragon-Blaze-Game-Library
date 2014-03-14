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

in vec3 v3_normal_c;	// Vertex normal in camera space
in vec2 v2_uv;			// UV coordinate
in vec3 v3_pos_w;		// Vertex position in world space
in vec3 v3_eye_c;		// Eye vector in camera space
in vec3 v3_light_c;		// Light vector in camera space

out vec3 color;			// Fragment color

uniform sampler2D tex_diffuse;	// Diffuse texture
uniform vec3 v3_lightPos_w;		// Light position in world space
uniform vec3 v3_lightColor;		// Light color
uniform vec3 v3_ambientLight;	// Ambient light color
uniform vec3 v3_matSpecColor;	// Material specular color
uniform float f_matSpecWidth;	// Width of specular highlight, the higher, the thinner

// Main entry point
void main(){
	// Calculate diffuse component
	vec3 n = normalize(v3_normal_c);
	vec3 l = normalize(v3_light_c);
	float cosTheta = clamp(dot(n, l), 0, 1);
	
	// Calculate specular component
	vec3 e = normalize(v3_eye_c);
	vec3 r = reflect(-l, n);
	float cosAlpha = clamp(dot(e, r), 0, 1);
 
	vec3 matDiffuse = texture(tex_diffuse, v2_uv).rgb;
	float dist = length(v3_lightPos_w - v3_pos_w);
	color = 
		// Ambient
		v3_ambientLight * matDiffuse +
		// Diffuse
		matDiffuse * v3_lightColor * cosTheta / (dist * dist) +
		// Specular
		v3_matSpecColor * v3_lightColor * pow(cosAlpha, f_matSpecWidth) / (dist * dist);

}