#pragma once

#include <iostream>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

// All nebula engine errors
enum NE_ERROR
{
	NE_FATAL,					// fatal error, unable to start
	NE_OK,						// all fine
	NE_WARNING,					// simple warning
	NE_RENDERER,				// fatal renderer error, unable to start
	NE_TEXTURE,					// unable to load texture
	NE_SHADER,					// unable to compile shader
	NE_OBJECT,					// unable to load object / render object
	NE_COMPONENT_ALREADY,		// Already added the component
	NE_COMPONENT_NOT_FOUND,		// Unable to find Entity component
	NE_UNABLE_BITANGENT,		// Unable to create tangents and bitangents
	NE_FALSE					// simple false
};

#ifndef _DEBUG 
#define NE_ASSERT static_assert
#else
#define NE_ASSERT assert
#endif

// Check for errors, simple debug error message
#define NE_ERROR_CHECK(_result) Util::CheckForErrors(_result, __FILE__, __LINE__);
// Delete specific object
#define NE_DELETE_OBJECT(_type) Util::DeletePointer(_type);
#define NE_DEBUG_LOG(_variable) Util::DebugLog(__variable);
#define NE_FORCE_INLINE __forceinline
#define NE_INLINE inline

class Util
{
public:
	// Calculate normals directly in arrays
	static void CalculateNormals(unsigned int * indices, unsigned int indiceCount, float * vertices, unsigned int verticeCount,
		unsigned int vLength, unsigned int normalOffset);

	// Calculate bitangents and return a pointer to the array
	static void CalculateBitAngents(unsigned int * vertices, const unsigned int UVoffset, const unsigned int verticeOffset, const unsigned int verticeCount, const unsigned int tangentOffset);

	// Check for errors, called via NE_ERROR_CHECK
	static void CheckForErrors(NE_ERROR error, char* file, int line);

	template<typename T>
	static void DeletePointer(T* t) { if(t) delete t; }

	template<typename T>
	static void DebugLog(T t)
	{
		// -> Use objects!

		/*if (std::is_same<T, int>::value)
			printf("%d\n", (int)t);*/
		//	std::cout << (int)T << std::endl;
		//if(std::is_same<T, float>::value)
		//	std::cout << (float)T << std::endl;
		//if(std::is_same<T, unsigned int>::value)
		//	std::cout << (unsigned int)T << std::endl;
		//if(std::is_same<T, double>::value)
		//	std::cout << (double)T << std::endl;

		

		//if (std::is_same<T, glm::vec2>::value)
		//{
		//	printf("Vector2 (%d / %d)\n", ((glm::vec2)t).x, ((glm::vec2)t).y);
		//	return;
		//}
		//if (std::is_same<T, glm::vec3>::value)
		//{
		//	printf("Vector3 (%d / %d / %d)\n", ((glm::vec3)t).x, ((glm::vec3)t).y, ((glm::vec3)t).z);
		////	printf("Vector3 (%d / %d / %d)\n", t.x, t.y, t.z);
		//	return;
		//}
		//if (std::is_same<T, glm::vec4>::value)
		//{
		//	std::cout << "t" << std::endl;
		//	return;
		//}
	}

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
	// Convert degrees to radians
	static float ToRadians(float degrees);
	// Convert radians to degrees
	static float ToDegrees(float radians);
};