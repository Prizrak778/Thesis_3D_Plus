#pragma once
#include "Vertex.h"
#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <GL/glew.h>
#include <GLFW\glfw3.h>
#include <GLFW\glfw3native.h>

class RenderObject
{
private:
	 bool _initialized;
	 GLuint _vertexArray;
	 GLuint _buffer; //������ � ������� �������� ������
	 int _verticeCount;
	 GLint polygonmode = GL_LINE;
public:
	GLint color_obj[4] = { 0, 0, 0, 0 };
	GLint color_choice[4] = { 0, 0, 0, 0 };
	RenderObject(std::vector<Vertex> vertices, GLint *color, GLint *color_choice);//������� ��������� ���������� � ������� ��������� �� ��������� � �����
	~RenderObject();
	void Bind();
	void Render();

};

