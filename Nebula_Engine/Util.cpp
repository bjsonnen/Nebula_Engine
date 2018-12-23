#include "Util.h"

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

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

unsigned int* Util::CalculateBitAngents(unsigned int * vertices, unsigned int UVoffset, unsigned int offset, unsigned int verticeCount)
{
	


	return 0;
}

void Util::CheckForErrors(NE_ERROR error, char * file, int line)
{
	if (!(error == NE_OK))
	{
		printf("%s(%d): Nebula Engine error %d - %s\n", file, line, error, NE_ErrorString(error));
	}
}

const char * Util::NE_ErrorString(NE_ERROR error)
{
	switch (error)
	{
	case NE_OK:			return "No errors.";
	case NE_WARNING:	return "Simple warning.";
	case NE_FATAL:		return "Important error, cant start game with this error.";
	case NE_RENDERER:	return "Renderer error, contact graphics programmer immediately";
	case NE_FALSE:		return "Simple false error";
	default:			return "Unknown error";
	}
}
