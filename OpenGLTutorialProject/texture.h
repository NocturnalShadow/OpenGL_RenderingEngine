#pragma once

#include <string>
#include <GL/glew.h>


class Texture
{
private:
	GLuint m_texture;

public:
	Texture(const std::string& fileName);
	Texture(const Texture&) = delete;

	virtual ~Texture();

public:
	void operator=(const Texture&) = delete;

public:
	void Bind(unsigned int unit);
};

