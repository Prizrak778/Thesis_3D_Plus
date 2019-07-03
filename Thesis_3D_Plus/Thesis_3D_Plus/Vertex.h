#pragma once
#include <vector>
#include <glm\vec2.hpp>
#include <glm\vec4.hpp>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <GLFW\glfw3native.h>

struct Vertex
{
	glm::vec4  _Position;
	glm::vec4  _NormalCoord;
	glm::vec2  _TexCoord;


	Vertex(glm::vec4 position, glm::vec4 normal, glm::vec2 texcoord)
	{
		_Position = position;
		_NormalCoord = normal;
		_TexCoord = texcoord;
	}
	
};
static std::vector<Vertex> CreateSolidCube(float side, float shift_lr, float shift_y, float shift_ud)
{
	side = (float)side / 2;
	std::vector<Vertex> vertices = 
	{
		//координаты для треуголника, нормаль, текстурные координаты
		//на каждый куб по 12 треугольников(36 точек)

		Vertex(glm::vec4(-side + shift_lr, -side + shift_y, -side + shift_ud, 1.0f), glm::vec4(-1.0, 0, 0, 0.0f), glm::vec2(0, 0)),
		Vertex(glm::vec4(-side + shift_lr,  side + shift_y, -side + shift_ud, 1.0), glm::vec4(-1.0, 0, 0, 0.0), glm::vec2(0, 1)),
		Vertex(glm::vec4(-side + shift_lr, -side + shift_y,  side + shift_ud, 1.0), glm::vec4(-1.0, 0, 0, 0.0), glm::vec2(1, 0)),

		Vertex(glm::vec4(-side + shift_lr, -side + shift_y,  side + shift_ud, 1.0), glm::vec4(-1.0, 0, 0, 0.0), glm::vec2(1, 0)),
		Vertex(glm::vec4(-side + shift_lr,  side + shift_y, -side + shift_ud, 1.0), glm::vec4(-1.0, 0, 0, 0.0), glm::vec2(0, 1)),
		Vertex(glm::vec4(-side + shift_lr,  side + shift_y,  side + shift_ud, 1.0), glm::vec4(-1.0, 0, 0, 0.0), glm::vec2(1, 1)),

		//+x
		Vertex(glm::vec4( side + shift_lr, -side + shift_y, -side + shift_ud, 1.0), glm::vec4(1.0, 0, 0, 0.0), glm::vec2(0, 0)),
		Vertex(glm::vec4( side + shift_lr,  side + shift_y, -side + shift_ud, 1.0), glm::vec4(1.0, 0, 0, 0.0), glm::vec2(0, 1)),
		Vertex(glm::vec4( side + shift_lr, -side + shift_y,  side + shift_ud, 1.0), glm::vec4(1.0, 0, 0, 0.0), glm::vec2(1, 0)),
					 		 															  								 
		Vertex(glm::vec4( side + shift_lr, -side + shift_y,  side + shift_ud, 1.0), glm::vec4(1.0, 0, 0, 0.0), glm::vec2(1, 0)),
		Vertex(glm::vec4( side + shift_lr,  side + shift_y, -side + shift_ud, 1.0), glm::vec4(1.0, 0, 0, 0.0), glm::vec2(0, 1)),
		Vertex(glm::vec4( side + shift_lr,  side + shift_y,  side + shift_ud, 1.0), glm::vec4(1.0, 0, 0, 0.0), glm::vec2(1, 1)),

		//-z
		Vertex(glm::vec4(-side + shift_lr, -side + shift_y, -side + shift_ud, 1.0), glm::vec4(0, -1.0, 0, 0.0), glm::vec2(0, 0)),
		Vertex(glm::vec4( side + shift_lr, -side + shift_y, -side + shift_ud, 1.0), glm::vec4(0, -1.0, 0, 0.0), glm::vec2(1, 0)),
		Vertex(glm::vec4(-side + shift_lr, -side + shift_y,  side + shift_ud, 1.0), glm::vec4(0, -1.0, 0, 0.0), glm::vec2(0, 1)),
					 	  
		Vertex(glm::vec4(-side + shift_lr, -side + shift_y,  side + shift_ud, 1.0), glm::vec4(0, -1.0, 0, 0.0), glm::vec2(0, 1)),
		Vertex(glm::vec4( side + shift_lr, -side + shift_y, -side + shift_ud, 1.0), glm::vec4(0, -1.0, 0, 0.0), glm::vec2(1, 0)),
		Vertex(glm::vec4( side + shift_lr, -side + shift_y,  side + shift_ud, 1.0), glm::vec4(0, -1.0, 0, 0.0), glm::vec2(1, 1)),

		//z+
		Vertex(glm::vec4(-side + shift_lr,  side + shift_y, -side + shift_ud, 1.0), glm::vec4(0,  1.0,  0, 0.0), glm::vec2(0, 0)),
		Vertex(glm::vec4(-side + shift_lr,  side + shift_y,  side + shift_ud, 1.0), glm::vec4(0,  1.0,  0, 0.0), glm::vec2(0, 1)),
		Vertex(glm::vec4( side + shift_lr,  side + shift_y, -side + shift_ud, 1.0), glm::vec4(0,  1.0,  0, 0.0), glm::vec2(1, 0)),
						 
		Vertex(glm::vec4( side + shift_lr,  side + shift_y, -side + shift_ud, 1.0), glm::vec4(0,  1.0,  0, 0.0), glm::vec2(1, 0)),
		Vertex(glm::vec4(-side + shift_lr,  side + shift_y,  side + shift_ud, 1.0), glm::vec4(0,  1.0,  0, 0.0), glm::vec2(0, 1)),
		Vertex(glm::vec4( side + shift_lr,  side + shift_y,  side + shift_ud, 1.0), glm::vec4(0,  1.0,  0, 0.0), glm::vec2(1, 1)),
						 
		//y-			 
		Vertex(glm::vec4(-side + shift_lr, -side + shift_y, -side + shift_ud, 1.0), glm::vec4(0, 0, -1.0, 0.0), glm::vec2(0, 0)),
		Vertex(glm::vec4(-side + shift_lr,  side + shift_y, -side + shift_ud, 1.0), glm::vec4(0, 0, -1.0, 0.0), glm::vec2(0, 1)),
		Vertex(glm::vec4( side + shift_lr, -side + shift_y, -side + shift_ud, 1.0), glm::vec4(0, 0, -1.0, 0.0), glm::vec2(1, 0)),
					 	  															 			   					 		  	   		  
		Vertex(glm::vec4( side + shift_lr, -side + shift_y, -side + shift_ud, 1.0), glm::vec4(0, 0, -1.0, 0.0), glm::vec2(1, 0)),
		Vertex(glm::vec4(-side + shift_lr,  side + shift_y, -side + shift_ud, 1.0), glm::vec4(0, 0, -1.0, 0.0), glm::vec2(0, 1)),
		Vertex(glm::vec4( side + shift_lr,  side + shift_y, -side + shift_ud, 1.0), glm::vec4(0, 0, -1.0, 0.0), glm::vec2(1, 1)),
						 
		//y+			 
		Vertex(glm::vec4(-side + shift_lr, -side + shift_y,  side + shift_ud, 1.0), glm::vec4(0, 0,  1.0, 0.0), glm::vec2(0, 0)),
		Vertex(glm::vec4( side + shift_lr, -side + shift_y,  side + shift_ud, 1.0), glm::vec4(0, 0,  1.0, 0.0), glm::vec2(1, 0)),
		Vertex(glm::vec4(-side + shift_lr,  side + shift_y,  side + shift_ud, 1.0), glm::vec4(0, 0,  1.0, 0.0), glm::vec2(0, 1)),
					 	  								  				   			 		  	   					 		  	   		  
		Vertex(glm::vec4(-side + shift_lr,  side + shift_y,  side + shift_ud, 1.0), glm::vec4(0, 0,  1.0, 0.0), glm::vec2(0, 1)),
		Vertex(glm::vec4( side + shift_lr, -side + shift_y,  side + shift_ud, 1.0), glm::vec4(0, 0,  1.0, 0.0), glm::vec2(1, 0)),
		Vertex(glm::vec4( side + shift_lr,  side + shift_y,  side + shift_ud, 1.0), glm::vec4(0, 0,  1.0, 0.0), glm::vec2(1, 1)),
	};
	return vertices;
}