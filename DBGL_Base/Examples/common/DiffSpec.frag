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

//////////////////////////////////////////////////////////////////////
// Structure definitions
//////////////////////////////////////////////////////////////////////
struct lightSource
{
	vec3 v3_position_w;		// Coordinates in world space
	vec3 v3_color;			// Light color (and power)
	float f_spotCutoff;		// Cutoff (if spotlight)
	vec3 v3_direction_w;	// Direction (if spot or directional)
};
struct material
{
	vec3 v3_specColor;	// Material specular color
	float f_specWidth;	// Width of specular highlight, the higher, the thinner
};

//////////////////////////////////////////////////////////////////////
// Variables
//////////////////////////////////////////////////////////////////////
in vec3 v3_normal_w;	// Vertex normal in world space
in vec2 v2_uv;			// UV coordinate
in vec3 v3_pos_w;		// Vertex position in world space
in vec3 v3_eye_w;		// Eye vector in world space

out vec3 color;			// Fragment color

const int c_MAXLIGHTS = 10;

uniform int i_numLights;					// Number of lights to process
uniform lightSource lights[c_MAXLIGHTS];	// Lights
uniform material mat;						// Material
uniform sampler2D tex_diffuse;				// Diffuse texture
uniform sampler2D tex_specular;				// Specular texture
uniform vec3 v3_ambientLight;				// Ambient light color

//////////////////////////////////////////////////////////////////////
// Functions
//////////////////////////////////////////////////////////////////////
//
// Ambient part of lighting
//	color = color (and intensity)
//
vec3 calcAmbient(vec3 color)
{
	return color * v3_ambientLight;
}
//
// Diffuse part of lighting
// 	i = index of light
//	normal_w = normal to use for calculation in world space
//	light_w = vector from vertex to light in world space
//	matColor = material diffuse color (and intensity)
//
vec3 calcDiffuse(int i, vec3 normal_w, vec3 light_w, vec3 matColor)
{
	float cosTheta = clamp(dot(normal_w, light_w), 0, 1);
	return matColor * lights[i].v3_color * cosTheta;
}
//
// Specular part of lighting
//	i = index of light
//	normal_w = normal to use for calculation in world space
//	light_w = vector from vertex to light in world space
//	intensity = specular intensity
//
vec3 calcSpecular(int i, vec3 normal_w, vec3 light_w, vec3 intensity)
{
	vec3 e = normalize(v3_eye_w);
	vec3 r = normalize(reflect(-light_w, normal_w));
	float cosAlpha = clamp(dot(e, r), 0, 1);
	return mat.v3_specColor * intensity * lights[i].v3_color * pow(cosAlpha, mat.f_specWidth);
}

//////////////////////////////////////////////////////////////////////
// Main entry point
//////////////////////////////////////////////////////////////////////
void main()
{
	// Calculate lights
	vec3 diffuseColor = texture(tex_diffuse, v2_uv).rgb;
	vec3 specularInt = texture(tex_specular, v2_uv).rgb;
	vec3 ambient = calcAmbient(diffuseColor);
	vec3 diffuse = vec3(0.0, 0.0, 0.0);
	vec3 specular = vec3(0.0, 0.0, 0.0);
	for(int i = 0; i < i_numLights; i++)
	{
		// Calculate light vector, i.e. from vertex to light in world space
		vec3 vertToLight_w = lights[i].v3_position_w - v3_pos_w;
		vec3 light_w = normalize(vertToLight_w);
		// Calculate attenuation
		float dist = length(vertToLight_w);
		float attenuation = dist * dist;
		// Calculate diffuse component
		diffuse += calcDiffuse(i, v3_normal_w, light_w, diffuseColor) / attenuation;
		// Calculate specular component
		specular += calcSpecular(i, v3_normal_w, light_w, specularInt) / attenuation;
	}
	
	// Final color
	color = ambient + diffuse + specular;
}