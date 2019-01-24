#pragma once

#include <GL\glew.h>
#include <string>

#include "CommonValues.h"
#include "Util.h"

//! Main class for textures
class Texture
{
public:
	//! Create empty Texture
	//!
	Texture();
	//! Create Texture from file
	//! @param fileLoc Insert file location as const char array
	Texture(const char* fileLoc);

	//! Load texture, called automatically
	//! @return Returns a NE_ERROR
	NE_ERROR LoadTexture();

	//! Use Texture for next object
	//!
	void UseTexture();
	//! Use Texture for next object with index
	//! @param index Insert texture id as unsigned int
	void UseTexture(unsigned int index);
	//! Delete all data on ram
	//!
	void ClearTexture();

	//! Set linear or nearest filter
	//! true = linear //! false = nearest
	//! @param value Set linear filter as bool
	void SetLinearFilter(bool value);
	//! Get bool of linear filter
	//! @return Returns linear filter as bool
	bool GetLinearFilter();

	//! Set file location
	//! @param file Insert file location as std::string
	void SetFileLocation(std::string file);

	//! Set texture wrapping
	//! 1 = repeat
	//! 2 = mirrored repeat
	//! 3 = clamp to edge
	//! 4 = clamp to border
	//! @param i Insert texture wrapping as int
	void SetTextureRepeat(int i);
	//! Get texture warpping
	//!
	int GetTextureRepeat();

	//! Get internal texture id
	/*unsigned int GetTextureID();*/

	//! Returns the texture position on the gpu
	//!
	unsigned int GetTexturePosition();

	//! Returns the file location
	//!
	std::string GetFileLocation();

	//! Create Depth Buffer
	//!
	void CreateDepthBuffer();

	// Delete texture on memory
	~Texture();

private:
	unsigned int textureID;
	int width, height, bitDepth;

	const char* fileLocation;

	bool linearFilter = true;
	int repeat = 1;
};

