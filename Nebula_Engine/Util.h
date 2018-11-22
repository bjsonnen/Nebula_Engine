#pragma once
class Util
{
public:
	Util();

	// Calculate normals directly in arrays
	static void CalculateNormals(unsigned int * indices, unsigned int indiceCount, float * vertices, unsigned int verticeCount,
		unsigned int vLength, unsigned int normalOffset);

	~Util();
};

