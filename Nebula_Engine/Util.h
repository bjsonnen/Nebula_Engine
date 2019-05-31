#pragma once

#include <iostream>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <vector>

#include "Vector2.h"
#include "Vector3.h"

//! All nebula engine errors
enum NE_ERROR
{
	NE_FATAL,					//! fatal error, unable to start
	NE_OK,						//! all fine
	NE_WARNING,					//! simple warning
	NE_RENDERER,				//! fatal renderer error, unable to start
	NE_TEXTURE,					//! unable to load texture
	NE_SHADER,					//! unable to compile shader
	NE_OBJECT,					//! unable to load object / render object
	NE_COMPONENT_ALREADY,		//! Already added the component
	NE_COMPONENT_NOT_FOUND,		//! Unable to find Entity component
	NE_UNABLE_BITANGENT,		//! Unable to create tangents and bitangents
	NE_FALSE					//! simple false
};

#ifndef _DEBUG 
#define NE_BREAK(val) if(val) __debugbreak();
#else
#define NE_BREAK(val)
#endif

//! Check for errors, simple debug error message
#define NE_ERROR_CHECK(_result) NE::Util::CheckForErrors(_result, __FILE__, __LINE__);
//! Delete specific object
#define NE_DELETE_OBJECT(_type) NE::Util::DeletePointer(_type);
//! Debug varible in the console window
#define NE_DEBUG_LOG(__variable) NE::Util::DebugLog(__variable);
//! Swap vector 
#define NE_SWAP_VECTOR_ARRAY(_vector_array) NE::Util::SwapVectorArray(_vector_array);

namespace NE
{
	//! Utilities. Use predefinied methods
	class Util
	{
	public:
		//! Calculate normals directly in arrays
		//! @param indices Insert array to indices as unsigned int indices
		//! @param indiceCount Insert array size of indices
		//! @param vertices Insert array to vertices as unsigned int indices
		//! @param indiceCount Insert array size of vertices
		//! @param vLength Insert vertice count per vertex
		//! @param normalOffset Insert normal count offset from start
		static void CalculateNormals(unsigned int * indices, unsigned int indiceCount, float * vertices, unsigned int verticeCount,
			unsigned int vLength, unsigned int normalOffset);

		//! Swap vector, use NE_SWAP_VECTOR_ARRAY(_vector_array)
		//! @param vertor Insert std::vector of type TEMPLATE as std::vector<T*>*
		template<typename T>
		static void SwapVectorArray(std::vector<T*>* vector);

		//! Check for errors, called via NE_ERROR_CHECK
		//! @param error Insert current NE_ERROR
		//! @param file Insert current file with __FILE__
		//! @param line Insert current line with __LINE__
		static void CheckForErrors(NE_ERROR error, char* file, int line);

		//! Delete a pointer if not nullptr
		//! @param t Insert pointer of type TEMPLATE
		template<typename T>
		static void DeletePointer(T* t) { if (t) delete t; }

		//! Debug log, use NE_DEBUG_LOG(__variable)
		//! @param t Insert output variable as type TEMPLATE
		template<typename T>
		static void DebugLog(T t)
		{
			if (std::is_same<T, Vector2>::value)
			{
				std::cout << t.ToString() << std::endl;
			}
			if (std::is_same<T, Vector3>::value)
			{
				std::cout << t.ToString() << std::endl;
			}
		}

	private:
		//! Returns error message
		static const char* NE_ErrorString(NE_ERROR error);
	};

	//! Main class for special math operations
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

	template<typename T>
	inline void Util::SwapVectorArray(std::vector<T*>* vector)
	{
		vector->_Swap_all();
	}

}