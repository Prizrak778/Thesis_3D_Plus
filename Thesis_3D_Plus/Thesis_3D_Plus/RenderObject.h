#pragma once
#include "Vertex.h"
#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <GLFW\glfw3native.h>

class RenderObject
{
private:
	 bool _initialized;
	 GLuint _vertexArray;
	
	 GLint polygonmode = GL_LINE;
public:
	int _verticeCount;
	GLuint _buffer;
	float color_obj[4] = { 0, 0, 0, 0 };
	GLint color_choice[4] = { 0, 0, 0, 0 };
	RenderObject(std::vector<Vertex> vertices, float *color, GLint *color_choice);//сделать указатели структурой и сделать указатель на структуру и конст
	~RenderObject();
	void Bind();
	void Render();
	void PolygonMode_now(GLint polygon);
};

