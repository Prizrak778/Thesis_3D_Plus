#include "RenderObject.h"



RenderObject::RenderObject(std::vector<Vertex> vertices, GLint *color, GLint *color_c)
{
	_verticeCount = vertices.size();
	glGenVertexArrays(1, &_vertexArray);
	glGenBuffers(1, &_buffer);
	glBindVertexArray(_vertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, _buffer);
		
	glNamedBufferStorage(_buffer, vertices[0].Size * _verticeCount, vertices.data(), GL_MAP_WRITE_BIT);
	glVertexArrayAttribBinding(_vertexArray, 1, 0);
	glEnableVertexArrayAttrib(_vertexArray, 1);
	glVertexArrayAttribFormat(_vertexArray, 1, 4, GL_FLOAT, false, 0);

	glVertexArrayAttribBinding(_vertexArray, 2, 0);
	glEnableVertexArrayAttrib(_vertexArray, 2);
	glVertexArrayAttribFormat(_vertexArray, 2, 4, GL_FLOAT, false, 16);

	glVertexArrayAttribBinding(_vertexArray, 3, 0);
	glEnableVertexArrayAttrib(_vertexArray, 3);
	glVertexArrayAttribFormat(_vertexArray, 3, 4, GL_FLOAT, false, 32);
	_initialized = true;
	glVertexArrayVertexBuffer(_vertexArray, 0, _buffer, NULL, vertices[0].Size);
	std::copy(color, color + 4, color_obj);
	std::copy(color_c, color_c + 4, color_choice);
}

void RenderObject::Bind()//Сохранение буфера для дальнейшей отрисовки
{
	glBindVertexArray(_vertexArray);
}

void RenderObject::Render()
{
	glDrawArrays(GL_TRIANGLES, 0, _verticeCount);
}

RenderObject::~RenderObject()
{
	_initialized = false;
	glDeleteVertexArrays(1, &_vertexArray);
	glDeleteBuffers(1, &_buffer);
}
