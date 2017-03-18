#include "shader.h"
#include <string>
#include <fstream>
#include <iostream>
#include <utility>


static std::string LoadShader(const std::string& fileName);
static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
static GLuint CreateShader(const std::string& text, GLenum shaderType);

Shader::Shader(const std::string & fileName)
{
	m_program = glCreateProgram();
	
	m_shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);			// creates vertex shader
	m_shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);			// creates fragment shader

	for(const auto & shader : m_shaders)
		glAttachShader(m_program, shader);

	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Program linking faild: ");

	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Program is invalid: ");

	// does not have any effect due to unknown reasons 
	// all locations are sepecified in the shader manualy
	//glBindAttribLocation(m_program, 0, "position");
	//glBindAttribLocation(m_program, 1, "normal");
	//glBindAttribLocation(m_program, 2, "texCoord");

	m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transform");
}

Shader::~Shader()
{
	for (auto & shader : m_shaders)
	{
		glDetachShader(m_program, shader);
		glDeleteShader(shader);
	}

	glDeleteProgram(m_program);
}


void Shader::Bind()
{
	glUseProgram(m_program);
}

void Shader::Update(const Transform & transform, const Camera & camera)
{
	glm::mat4 m4_ModelViewProjection = camera.GetViewProjection() * transform.GetModel();
	// update a uniform variable with a new model matrix
	glUniformMatrix4fv(
		m_uniforms[TRANSFORM_U],			// a handle to the uniform to be updated
		1,									// number of elements
		GL_FALSE,							// matrix transposition flag
		&m4_ModelViewProjection[0][0]);		// beginning of the matrix itself
}


static GLuint CreateShader(const std::string & text, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	if (shader == 0)
		std::cerr << "Error: Shader creation faild!" << std::endl;

	const GLchar* shaderSourceStrings[1];
	GLint shaderSourceStringLengths[1];

	shaderSourceStrings[0] = text.c_str();
	shaderSourceStringLengths[0] = static_cast<GLint>(text.length());

	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
	glCompileShader(shader);

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed: ");

	return shader;
}

static std::string LoadShader(const std::string & fileName)
{
	std::ifstream file{ fileName.c_str(), std::ifstream::in };

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader file: " << fileName << std::endl;
	}
	return output;
}

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string & errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram) 
		glGetProgramiv(shader, flag, &success);
	else 
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram) {
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		}
		else {
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		}
		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}
