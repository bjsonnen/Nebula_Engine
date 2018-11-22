#version 330

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex;
layout (location = 2) in vec3 norm;

out vec2 TexCoord;
out vec4 Color;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;
uniform vec4 color;

void main()
{
	gl_Position = projection * view * model * vec4(pos, 1.0);
	TexCoord = tex;
	Color = color;
}