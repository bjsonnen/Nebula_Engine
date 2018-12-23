#pragma once

#include <GL\glew.h>
#include <string>

#include "CommonValues.h"
#include "Util.h"

class Texture
{
public:
	Texture();
	// Create Texture from file
	Texture(const char* fileLoc);

	// Load texture, called automatically
	NE_ERROR LoadTexture();

	// Use Texture for next object
	void UseTexture();
	// Use Texture for next object with index
	void UseTexture(unsigned int index);
	// Delete all data on ram
	void ClearTexture();

	// Set linear or nearest filter
	// true = linear // false = nearest
	void SetLinearFilter(bool value);
	// Get bool of linear filter
	bool GetLinearFilter();

	// Set file location
	void SetFileLocation(std::string file);

	// Set texture wrapping
	// 1 = repeat
	// 2 = mirrored repeat
	// 3 = clamp to edge
	// 4 = clamp to border
	void SetTextureRepeat(int i);
	// Get texture warpping
	int GetTextureRepeat();

	unsigned int GetTextureID();

	// Returns the texture position on the gpu
	unsigned int GetTexturePosition();

	// Returns the file location
	std::string GetFileLocation();

	// Create Depth Buffer
	void CreateDepthBuffer();

	~Texture();

private:
	unsigned int textureID;
	int width, height, bitDepth;

	const char* fileLocation;

	bool linearFilter = true;
	int repeat = 1;
};

