#include "Util.h"

const int MAX_POINT_LIGHTS = 3;
const int MAX_SPOT_LIGHTS = 3;

void Util::CalculateNormals(unsigned int * indices, unsigned int indiceCount, float * vertices, unsigned int verticeCount, unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}

void Util::CheckForErrors(NE_ERROR error, char * file, int line)
{
	if (!(error == NE_OK))
	{
		printf("%s(%d): Nebula Engine error: %s\n", file, line, NE_ErrorString(error));
	}
}

const char * Util::NE_ErrorString(NE_ERROR error)
{
	switch (error)
	{
	case NE_OK:						return "No errors.";
	case NE_WARNING:				return "Simple warning.";
	case NE_FATAL:					return "Important error, cant start game with this error.";
	case NE_RENDERER:				return "Renderer error, contact graphics programmer immediately";
	case NE_OBJECT:					return "Unable to load Gameobject. Is the path correct?";
	case NE_TEXTURE:				return "Unable to load Texture. Is the path/file ending correct?";
	case NE_SHADER:					return "Unable to compile shader. ";
	case NE_COMPONENT_ALREADY:		return "Already added the component!";
	case NE_COMPONENT_NOT_FOUND:	return "There is no component on the object!";
	case NE_FALSE:					return "Simple false error";
	case NE_UNABLE_BITANGENT:		return "Unable to create Tangents and Bitangents!";
	default:						return "Unknown error";
	}
}

float Math::ToRadians(float degrees)
{
	return (degrees * (3.14159265f / 180.0f));
}

float Math::ToDegrees(float radians)
{
	return (radians / (3.14159265f / 180.0f));
}
