#version 330

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex;
layout (location = 2) in vec3 norm;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 bitangent;

out vec4 vCol;
out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;
out vec4 DirectionalLightSpacePos;

out mat3 TBN;

out vec3 TangentLightPos;
out vec3 TangentViewPos;
out vec3 TangentFragPos;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 directionalLightTransform;

void main()
{
	FragPos = (model * vec4(pos, 1.0)).xyz;
	DirectionalLightSpacePos = directionalLightTransform * model * vec4(pos, 1.0);
	vCol = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);
	TexCoord = tex;
	Normal = mat3(transpose(inverse(model))) * norm;
	
	vec3 T = normalize(vec3(projection * view * model * vec4(tangent, 0.0)));
	vec3 B = normalize(vec3(projection * view * model * vec4(bitangent, 0.0)));
	vec3 N = normalize(vec3(projection * view * model * vec4(norm, 0.0)));
	
	mat3 TBN = mat3(T, B, N);
	
	gl_Position = projection * view * model * vec4(pos, 1.0);
}