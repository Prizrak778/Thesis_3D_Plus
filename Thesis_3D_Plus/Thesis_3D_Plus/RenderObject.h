#pragma once
#include "Vertex.h"
#include <string>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <glm\vec3.hpp>
#include <glm\vec4.hpp>

#include <glm\gtx\transform.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\mat4x4.hpp>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <GLFW\glfw3native.h>

enum TypeObjectRender
{
	SimpleObject,
	LightSourceObject,
	FlatObject
};

class RenderObject
{
private:
	 bool _initialized;
	 GLuint _vertexArray;
	 GLint polygonmode = GL_LINE;
public:
	int _verticeCount;
	GLuint _buffer;
	glm::vec3 position_obj = glm::vec3(0, 0, 0);
	glm::vec4 color_obj = glm::vec4(0, 0, 0, 1);
	glm::vec4 color_choice = glm::vec4(0, 0, 0, 1);
	glm::mat4 ModelMatrix = glm::translate(glm::vec3(0.0f, 0.0f, 0.0f));
	int TybeObject = SimpleObject;
	RenderObject();
	RenderObject(std::vector<Vertex> vertices, glm::vec3 position, glm::vec4 color, glm::vec4 color_choice);//сделать указатели структурой и сделать указатель на структуру и конст
	~RenderObject();
	void clear();
	void Bind();
	void Render();
	void Render_line();
	void changeModelMstrix(glm::vec3);
	void PolygonMode_now(GLint polygon);
};

