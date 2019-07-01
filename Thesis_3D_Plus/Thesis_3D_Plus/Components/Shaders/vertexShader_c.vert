#version 450 core

layout (location = 1) in vec4 vec_position;
layout (location = 2) in vec4 vec_normal;
layout(location = 19) uniform vec4 vec_color;
layout(location = 21) uniform mat4 proj;
layout(location = 22) uniform mat4 model;
layout(location = 20) uniform mat4 view;


out vec4 vs_color;
out vec4 pos;

void main(void)
{
	gl_Position =  view * vec_position;
	vs_color = vec_color;
}