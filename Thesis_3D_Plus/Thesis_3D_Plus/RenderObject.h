#pragma once
#include <GL/glew.h>
#include <GLFW\glfw3.h>
#include <GLFW\glfw3native.h>

class RenderObject
{
private:
	 bool _initialized;
	 int _vertexArray;
	 int _buffer; //Буффер в котором хранится объект
	 int _verticeCount;
public:
	RenderObject();
	~RenderObject();
};

