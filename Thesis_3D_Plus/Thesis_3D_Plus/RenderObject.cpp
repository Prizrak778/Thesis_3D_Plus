#include "RenderObject.h"



RenderObject::RenderObject(Vertex vertices[])
{
	_verticeCount = vertices->Size;
	glGenVertexArrays(1, &_vertexArray);
}


RenderObject::~RenderObject()
{
}
