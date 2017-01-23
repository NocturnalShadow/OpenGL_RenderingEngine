#include "mesh.h"
#include "obj_loader.h"

#include <algorithm>


void Mesh::InitMesh(const IndexedModel & model)
{
	m_drawCount = (unsigned int) model.indices.size();
	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);

	glGenBuffers(NUM_BUFFERS, m_vertexBufferObject);
	
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), model.positions.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.texCoords.size() * sizeof(model.texCoords[0]), model.texCoords.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(model.normals[0]), model.normals.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexBufferObject[INDEX_VB]);		
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), model.indices.data(), GL_STATIC_DRAW);

	glBindVertexArray(0);
}

Mesh::Mesh(const std::vector<Vertex> & vertices, const std::vector<unsigned int> & indices)
{
	IndexedModel model;

	model.indices.reserve(vertices.size());
	model.texCoords.reserve(vertices.size());

	for (const auto& vertex : vertices)
	{
		model.positions.push_back(vertex.GetPos());
		model.texCoords.push_back(vertex.GetTexCoord());
		model.normals.push_back(vertex.GetNormal());
	}
	model.indices.reserve(indices.size());
	for (const auto & index : indices)
		model.indices.push_back(index);

	InitMesh(model);
}

Mesh::Mesh(const std::string & fileName)
{
	IndexedModel model = OBJModel(fileName).ToIndexedModel();
	InitMesh(model);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}


void Mesh::Draw()
{
	glBindVertexArray(m_vertexArrayObject);

	glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

void Mesh::Draw(GLenum drawType)
{
	glBindVertexArray(m_vertexArrayObject);

	glDrawElements(drawType, m_drawCount, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}
