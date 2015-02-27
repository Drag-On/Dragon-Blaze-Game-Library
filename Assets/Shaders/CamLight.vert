#version 330 core
layout(location = 0) in vec3 vertexPos;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 normal;
out vec3 normal_cam;
out vec2 uv;
uniform mat4 MVP;
uniform mat4 ITMV;
void main(){
	gl_Position = MVP * vec4(vertexPos, 1);
	uv = vertexUV;
	normal_cam = normalize((ITMV * vec4(normal, 0)).xyz);
}