#pragma once

#include "transform.h"
#include <string>
#include <GL/glew.h>
#include "camera.h"

class Shader
{
	enum 
	{ 
		TRANSFORM_U,	

		NUM_UNIFORMS
	};
	static const size_t num_shaders = 2;

private:
	GLuint m_program;
	GLuint m_shaders[num_shaders];
	GLuint m_uniforms[NUM_UNIFORMS];

public:
	Shader() { };
	Shader(const std::string& filename);
	Shader(const Shader&) = delete;

	virtual ~Shader();

public:
	Shader& operator=(const Shader&) = delete;

public:
	void Bind();
	void Update(const Transform& transform, const Camera& camera);
};

