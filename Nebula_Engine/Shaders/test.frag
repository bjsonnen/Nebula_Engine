#version 330
out vec4 FragColor;

in vec4 vCol;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
in vec4 DirectionalLightSpacePos;

void main()
{
	FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}