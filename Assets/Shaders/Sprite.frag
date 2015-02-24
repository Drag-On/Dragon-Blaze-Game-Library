#version 330 core

in vec2 uv;
out vec4 color;
uniform sampler2D tex_diffuse;

void main(){
	color = texture(tex_diffuse, uv).rgba;
}