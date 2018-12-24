#pragma once

#include <iostream>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

// All nebula engine errors
enum NE_ERROR
{
	NE_OK,						// all fine
	NE_WARNING,					// simple warning
	NE_FATAL,					// fatal error, unable to start
	NE_RENDERER,				// fatal renderer error, unable to start
	NE_TEXTURE,					// unable to load texture
	NE_SHADER,					// unable to compile shader
	NE_OBJECT,					// unable to load object / render object
	NE_COMPONENT_ALREADY,		// Already added the component
	NE_COMPONENT_NOT_FOUND,		// Unable to find Entity component
	NE_FALSE					// simple false
};

// Check for errors, simple debug error message
#define NE_ERROR_CHECK(_result) Util::CheckForErrors(_result, __FILE__, __LINE__);
// Delete specific object
#define NE_DELETE_OBJECT(_type) Util::DeletePointer(_type);
#define NE_FORCE_INLINE __forceinline
#define NE_INLINE inline

class Util
{
public:
	// Calculate normals directly in arrays
	static void CalculateNormals(unsigned int * indices, unsigned int indiceCount, float * vertices, unsigned int verticeCount,
		unsigned int vLength, unsigned int normalOffset);

	// Calculate bitangents and return a pointer to the array
	static unsigned int* CalculateBitAngents(unsigned int * vertices, unsigned int UVoffset, unsigned int offset, unsigned int verticeCount);

	// Check for errors, called via NE_ERROR_CHECK
	static void CheckForErrors(NE_ERROR error, char* file, int line);

	template<typename T>
	static void DeletePointer(T* t) { if(t) delete t; }

private:
	// Returns error message
	static const char* NE_ErrorString(NE_ERROR error);

};

class Math
{
public:
	// Lerp a 3D Position slowly from one point another
	static glm::vec3 Lerp(glm::vec3 start, glm::vec3 target, float time)
	{
		float x = start.x + time * (target.x - start.x);
		float y = start.y + time * (target.y - start.y);
		float z = start.z + time * (target.z - start.z);

		return glm::vec3(x, y, z);
	}
	// Lerp a 2D Position slowly from one point another
	static glm::vec2 Lerp(glm::vec3 start, glm::vec2 target, float time)
	{
		float x = start.x + time * (target.x - start.x);
		float y = start.y + time * (target.y - start.y);

		return glm::vec2(x, y);
	}
};