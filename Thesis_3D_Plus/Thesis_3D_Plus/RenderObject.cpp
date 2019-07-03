#include "RenderObject.h"



RenderObject::RenderObject(std::vector<Vertex> vertices,  glm::vec4 color, glm::vec4 color_c)
{
	_verticeCount = vertices.size();
	glGenVertexArrays(1, &_vertexArray);
	glGenBuffers(1, &_buffer);

	glBindVertexArray(_vertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, _buffer);
	
	glNamedBufferStorage(_buffer, sizeof(Vertex) * _verticeCount, vertices.data(), GL_MAP_WRITE_BIT);
	glVertexArrayAttribBinding(_vertexArray, 1, 0);
	glEnableVertexArrayAttrib(_vertexArray, 1);
	glVertexArrayAttribFormat(_vertexArray, 1, 4, GL_FLOAT, GL_FALSE, 0);

	glVertexArrayAttribBinding(_vertexArray, 2, 0);
	glEnableVertexArrayAttrib(_vertexArray, 2);
	glVertexArrayAttribFormat(_vertexArray, 2, 4, GL_FLOAT, GL_FALSE, 16);

	glVertexArrayAttribBinding(_vertexArray, 3, 0);
	glEnableVertexArrayAttrib(_vertexArray, 3);
	glVertexArrayAttribFormat(_vertexArray, 3, 4, GL_FLOAT, GL_FALSE, 32);
	_initialized = true;
	glVertexArrayVertexBuffer(_vertexArray, 0, _buffer, NULL, sizeof(Vertex));
	color_obj = color;
	color_choice = color_c;
	vertices.clear();
}

void RenderObject::Bind()//Сохранение буфера для дальнейшей отрисовки
{
	glBindVertexArray(_vertexArray);
}
	

void RenderObject::PolygonMode_now(GLint polygon)//тип полигона для отрисовки(Fill, Line, Point)
{
	polygonmode = polygon;
	glPolygonMode(GL_FRONT_AND_BACK, polygon);
}

void RenderObject::Render()
{
	glDrawArrays(GL_TRIANGLES, 0, _verticeCount);
}
void RenderObject::clear()
{
	glDeleteVertexArrays(1, &_vertexArray);
	glDeleteBuffers(1, &_buffer);
}

RenderObject::~RenderObject()
{
	_initialized = false;
}
