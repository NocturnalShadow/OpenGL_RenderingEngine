#pragma once

#include "obj_loader.h"

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <vector>

class Vertex
{
private:
	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;

public:
	Vertex(const glm::vec3& pos_, const glm::vec2& texCoord_, const glm::vec3& normal_ = glm::vec3(0.0, 0.0, 0.0)) 
		: pos{ pos_ }, texCoord{ texCoord_ }, normal{normal_}
	{	}

public:
	const glm::vec3& GetPos() const { return pos; }
	const glm::vec2& GetTexCoord() const { return texCoord; }
	const glm::vec3& GetNormal() const { return normal; }
};


class Mesh
{
	enum { 
		POSITION_VB,
		TEXCOORD_VB,
		NORMAL_VB,
		INDEX_VB,	
		NUM_BUFFERS };

private:
	GLuint m_vertexArrayObject;
	GLuint m_vertexBufferObject[NUM_BUFFERS];
	unsigned int m_drawCount;

	void InitMesh(const IndexedModel&);

public:
	Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
	Mesh(const std::vector<glm::vec3> positions, const std::vector<glm::vec2> textures, const std::vector<unsigned int> indices);
	Mesh(const std::string& fileName);
	Mesh(const Mesh&) = delete;

	virtual ~Mesh();

public:
	void operator=(const Mesh&) = delete;

public:
	void Draw();
	void Draw(GLenum);
};

