#version 330

in vec4 vCol;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
in vec4 DirectionalLightSpacePos;

in vec3 NormalTangent;
in vec3 NormalBitangent;
in vec3 NormalNormal;

in mat3 TBN;

out vec4 color;

vec3 mainColor;

const int MAX_POINT_LIGHTS = 3;
const int MAX_SPOT_LIGHTS = 3;

struct Light
{
	vec3 color;
	float ambientIntensity;
	float diffuseIntensity;
};

struct DirectionalLight 
{
	Light base;
	vec3 direction;
};

struct PointLight
{
	Light base;
	vec3 position;
	float constant;
	float linear;
	float exponent;
};

struct SpotLight
{
	PointLight base;
	vec3 direction;
	float edge;
};

struct OmniShadowMap
{
	samplerCube shadowMap;
	float farPlane;
};

struct Material
{
	float specularIntensity;
	float shininess;
};

uniform int pointLightCount;
uniform int spotLightCount;

uniform bool renderNormalMaps;
uniform bool useNormalMap;

// Correct usage for jpg and png for example
uniform bool isNot4Channel;

uniform DirectionalLight directionalLight;
uniform PointLight pointLights[10];
uniform SpotLight spotLights[10];

uniform sampler2D dTexture;
uniform sampler2D nTexture;
uniform sampler2D directionalShadowMap;
uniform OmniShadowMap omniShadowMaps[10 + 10];

uniform Material material;

uniform vec3 eyePosition;
uniform vec3 primaryColor;

vec3 normal;

vec3 sampleOffsetDirections[20] = vec3[]
(
   vec3( 1,  1,  1), vec3( 1, -1,  1), vec3(-1, -1,  1), vec3(-1,  1,  1), 
   vec3( 1,  1, -1), vec3( 1, -1, -1), vec3(-1, -1, -1), vec3(-1,  1, -1),
   vec3( 1,  1,  0), vec3( 1, -1,  0), vec3(-1, -1,  0), vec3(-1,  1,  0),
   vec3( 1,  0,  1), vec3(-1,  0,  1), vec3( 1,  0, -1), vec3(-1,  0, -1),
   vec3( 0,  1,  1), vec3( 0, -1,  1), vec3( 0, -1, -1), vec3( 0,  1, -1)
); 

float CalculateDirectionalShadowFactor(DirectionalLight light)
{
	vec3 projCoords = DirectionalLightSpacePos.xyz / DirectionalLightSpacePos.w;
	projCoords = (projCoords * 0.5) + 0.5;
	
	float current = projCoords.z;
	
	vec3 lightDir = normalize(directionalLight.direction);
	
	float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.0005);
	
	float shadow = 0.0;
	vec2 texelSize = 1.0 / textureSize(directionalShadowMap, 0);
	for(int x = -1; x <= 1; ++x)
	{
		for(int y = -1; y <= 1; ++y)
		{
			float pcfDepth = texture(directionalShadowMap, projCoords.xy + vec2(x,y) * texelSize).r;
			shadow += current - bias > pcfDepth ? 1.0 : 0.0;
		}
	}

	shadow /= 9.0;
	
	if(projCoords.z > 1.0)
	{
		shadow = 0.0;
	}									
	
	return shadow;
}

float CalculateOmniShadowFactor(PointLight light, int shadowIndex)
{
	vec3 fragToLight = FragPos - light.position;
	float currentDepth = length(fragToLight);
	
	float shadow = 0.0;
	float bias = 0.05;
	int samples = 20;
	
	float viewDistance = length(eyePosition - FragPos);
	float diskRadius = (1.0 + (viewDistance/omniShadowMaps[shadowIndex].farPlane)) / 25.0;
	
	for(int i = 0; i < samples; i++)
	{
		float closestDepth = texture(omniShadowMaps[shadowIndex].shadowMap, fragToLight + sampleOffsetDirections[i] * diskRadius).r;
		closestDepth *= omniShadowMaps[shadowIndex].farPlane;
		if(currentDepth -  bias > closestDepth)
		{
			shadow += 1.0;
		}
	}
	
	
	shadow /= float(samples);
	return shadow;
}

vec4 CalculateLightByDirection(Light light, vec3 direction, float shadowFactor)
{
	vec4 ambientColor = vec4(light.color, 1.0f) * light.ambientIntensity;
	
	float diffuseFactor = max(dot(normalize(normal), normalize(direction)), 0.0f);
	vec4 diffuseColor = vec4(light.color * light.diffuseIntensity * diffuseFactor, 1.0f);
	
	vec4 specularColor = vec4(0, 0, 0, 0);
	
	float test = 0;
	
	test = step(0.0, sin(diffuseFactor));
	
	vec3 fragToEye = normalize(eyePosition - FragPos);
	vec3 reflectedVertex = normalize(reflect(direction, normalize(normal)));
		
	float specularFactor = dot(fragToEye, reflectedVertex);
		
	//test = sin(specularFactor);
	//test = step(0.0, specularFactor);
		
	//specularFactor = pow(specularFactor, material.shininess);
	//specularColor = vec4(light.color * material.specularIntensity * specularFactor, 1.0f);
		
	if(specularFactor > 0.0)
	{
		specularFactor = pow(specularFactor, material.shininess);
		specularColor = vec4(light.color * material.specularIntensity * specularFactor, 1.0f);
	}

	return (ambientColor + (1.0 - shadowFactor) * (diffuseColor + specularColor));
}

vec4 CalculateDirectionalLight()
{
	float shadowFactor = CalculateDirectionalShadowFactor(directionalLight);
	return CalculateLightByDirection(directionalLight.base, directionalLight.direction, shadowFactor);
}

vec4 CalculatePointLight(PointLight pLight, int shadowIndex)
{
	vec3 direction = FragPos - pLight.position;
	float distance = length(direction);
	direction = normalize(direction);
	
	float shadowFactor = CalculateOmniShadowFactor(pLight, shadowIndex);
	
	vec4 color = CalculateLightByDirection(pLight.base, direction, shadowFactor);
	float attenuation = pLight.exponent * distance * distance +
						pLight.linear * distance +
						pLight.constant;
	
	return (color / attenuation);
}

vec4 CalculateSpotLight(SpotLight sLight, int shadowIndex)
{
	vec3 rayDirection = normalize(FragPos - sLight.base.position);
	float slFactor = dot(rayDirection, sLight.direction);
	
	if(slFactor > sLight.edge)
	{
		vec4 color = CalculatePointLight(sLight.base, shadowIndex);
		
		return color * (1.0f - (1.0f - slFactor)*(1.0f/(1.0f - sLight.edge)));
		
	} else {
		return vec4(0, 0, 0, 0);
	}
}

vec4 CalculatePointLights()
{
	vec4 totalColor = vec4(0, 0, 0, 0);
	for(int i = 0; i < pointLightCount; i++)
	{		
		totalColor += CalculatePointLight(pointLights[i], i);
	}
	
	return totalColor;
}

vec4 CalculateSpotLights()
{
	vec4 totalColor = vec4(0, 0, 0, 0);
	for(int i = 0; i < spotLightCount; i++)
	{		
		totalColor += CalculateSpotLight(spotLights[i], i + pointLightCount);
	}
	
	return totalColor;
}

void main()
{
	// use normals or normal texture
	if(textureSize(nTexture, 0).x < 1 || textureSize(nTexture, 0).y < 1 || !useNormalMap)
		normal = normalize(Normal);
	else
	{
		normal = texture(nTexture, TexCoord).rgb;
		normal = normalize(normal * 2.0 - 1.0);
		normal = normalize(TBN * normal);
	}

	vec4 finalColor = CalculateDirectionalLight();
	finalColor += CalculatePointLights();
	finalColor += CalculateSpotLights();
	
	vec4 texColor = texture(dTexture, TexCoord);
	
	color = vec4(texColor.xyz * finalColor.xyz, 0.0);
	color = vec4(color.rgb * primaryColor, texColor.w);
	
	// if there is no texture
	if(textureSize(dTexture, 0).x < 1 || textureSize(dTexture, 0).y < 1)
		color.rgb = vec3(1.0, 0.412, 0.705);
	
	// gamme correction
	color.rgb = pow(color.rgb, vec3(1.0/2.2));
}