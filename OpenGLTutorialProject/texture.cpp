#include "texture.h"
#include "stb_image.h"
#include <cassert>
#include <iostream>

Texture::Texture(const std::string & fileName)
{
	int width, height, numComponents;
	// load image data from a file to the memory
	auto imageData = stbi_load(fileName.c_str(), &width, &height, &numComponents, 4);

	if (imageData == NULL)
		std::cerr << "Texture loading faild for texture: " << fileName << std::endl;

	// create texture
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	// behaviour in case of reading outside of texture ->
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);			// -> width		
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);			// -> height

	// behaviour in case if taxture takes 
	// more(GL_TEXTURE_MAG_FILTER)/fewer(GL_TEXTURE_MIN_FILTER) pixel
	// than its resolution
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);		// GL_LINEAR - pixels liniary iterpolate between existing pixels
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);		// GL_NEAREST also possible

	// level = 0 - mipmapping is off
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

	// release image data memory
	stbi_image_free(imageData);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_texture);
}


void Texture::Bind(unsigned int unit)
{
	assert(unit >= 0 && unit <= 32);
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, m_texture);
}
