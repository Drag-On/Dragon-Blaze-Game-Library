#version 330 core

layout(location = 0) in vec3 vertexPos;
layout(location = 1) in vec2 vertexUV;
out vec2 uv;
uniform vec2 v2_screenRes;
uniform mat3 TRANSFORM_2D;

void main(){
	vec2 halfRes = v2_screenRes / 2;
	vec2 clipPos = vec2(TRANSFORM_2D * vec3(vertexPos.xy, 1)) - halfRes;
	clipPos /= halfRes;
	gl_Position = vec4(clipPos, 0, 1);
	uv = vertexUV;
}