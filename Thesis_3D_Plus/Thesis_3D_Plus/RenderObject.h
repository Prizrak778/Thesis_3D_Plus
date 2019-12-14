#pragma once
#include "Vertex.h"
#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <glm\vec4.hpp>
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
	glm::vec4 color_obj = glm::vec4(0, 0, 0, 1);
	glm::vec4 color_choice = glm::vec4(0, 0, 0, 1);
	RenderObject(std::vector<Vertex> vertices, glm::vec4 color, glm::vec4 color_choice);//сделать указатели структурой и сделать указатель на структуру и конст
	~RenderObject();
	void clear();
	void Bind();
	void Render();
	void Render_line();
	void PolygonMode_now(GLint polygon);
};

