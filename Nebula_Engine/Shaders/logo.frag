#version 330

in vec4 vCol;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D sTexture;

void main()
{
	FragColor = vec4(1.0, 0.0, 0.0, 1.0); //vec4(texture(sTexture, TexCoord).rgb, 1.0);
}