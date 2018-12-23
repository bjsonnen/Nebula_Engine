#pragma once

#include <iostream>

// All nebula engine errors
enum NE_ERROR
{
	NE_OK,			// all fine
	NE_WARNING,		// simple warning
	NE_FATAL,		// fatal error, unable to start
	NE_RENDERER,	// fatal renderer error, unable to start
	NE_FALSE		// simple false
};

// Check for errors, simple debug error message
#define NE_ERROR_CHECK(_result) Util::CheckForErrors(_result, __FILE__, __LINE__);

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

private:
	// Returns error message
	static const char* NE_ErrorString(NE_ERROR error);

};

