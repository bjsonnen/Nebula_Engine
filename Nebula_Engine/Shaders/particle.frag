#version 330

in vec4 vCol;
in vec2 TexCoord;
in vec4 Color;

out vec4 FragColor;

uniform sampler2D sTexture;

void main()
{
	FragColor = texture(sTexture, TexCoord) * Color;
}