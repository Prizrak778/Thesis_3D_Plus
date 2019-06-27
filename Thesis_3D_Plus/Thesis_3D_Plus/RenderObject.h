#pragma once
#include "Vertex.h"
#include <GL/glew.h>
#include <GLFW\glfw3.h>
#include <GLFW\glfw3native.h>

class RenderObject
{
private:
	 bool _initialized;
	 GLuint _vertexArray;
	 int _buffer; //������ � ������� �������� ������
	 int _verticeCount;
	 GLint color_obj[4] = { 0, 0, 0, 0, };
	 GLint color_choice[4] = { 0, 0, 0, 0, };
	 GLint polygonmode = GL_LINE;
public:
	RenderObject(Vertex vertices[]);
	~RenderObject();
};

