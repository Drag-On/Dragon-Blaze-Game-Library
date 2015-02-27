#version 330 core
in vec3 normal_cam;
in vec2 uv;
out vec4 color;
uniform sampler2D tex_diffuse;
void main(){
	float variance = max(0.0, dot(vec3(0, 0, 1), normal_cam));
	variance += max(0.0, dot(vec3(0, 0, 1), -normal_cam));
	color = texture(tex_diffuse, uv).rgba * variance;
};