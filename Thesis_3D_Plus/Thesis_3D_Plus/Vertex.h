#pragma once
#include <vector>
#include <GL/glew.h>
#include <GLFW\glfw3.h>
#include <GLFW\glfw3native.h>

struct Vertex
{
	const int Size = (4 + 4 + 2) * 4; // size of struct in bytes

	GLfloat _Position[4];
	GLfloat _NormalCoord[4];
	GLfloat _TexCoord[2];

	Vertex(GLfloat position[4], GLfloat normal[4], GLfloat texcoord[2])
	{
		for (int i = 0; i < 4; i++)
		{
			_Position[i] = position[i];
			_NormalCoord[i] = normal[i];
		}
		for (int i = 0; i < 2; i++)
		{
			_TexCoord[i] = texcoord[i];
		}
	}
	
};
static std::vector<Vertex> CreateSolidCube(float side, float shift_lr, float shift_y, float shift_ud)
{
	side = (float)side / 2;
	std::vector<Vertex> vertices = 
	{
		//координаты для треуголника, нормаль, текстурные координаты
		//на каждый куб по 12 треугольников(36 точек)

		Vertex(new GLfloat[4]{-side + shift_lr, -side + shift_y, -side + shift_ud, 1.0f}, new GLfloat[4]{-1.0, 0, 0, 0.0f}, new GLfloat[2]{0, 0}),
		Vertex(new GLfloat[4]{-side + shift_lr,  side + shift_y, -side + shift_ud, 1.0}, new GLfloat[4]{-1.0, 0, 0, 0.0}, new GLfloat[2]{0, 1}),
		Vertex(new GLfloat[4]{-side + shift_lr, -side + shift_y,  side + shift_ud, 1.0}, new GLfloat[4]{-1.0, 0, 0, 0.0}, new GLfloat[2]{1, 0}),

		Vertex(new GLfloat[4]{-side + shift_lr, -side + shift_y,  side + shift_ud, 1.0}, new GLfloat[4]{-1.0, 0, 0, 0.0}, new GLfloat[2]{1, 0}),
		Vertex(new GLfloat[4]{-side + shift_lr,  side + shift_y, -side + shift_ud, 1.0}, new GLfloat[4]{-1.0, 0, 0, 0.0}, new GLfloat[2]{0, 1}),
		Vertex(new GLfloat[4]{-side + shift_lr,  side + shift_y,  side + shift_ud, 1.0}, new GLfloat[4]{-1.0, 0, 0, 0.0}, new GLfloat[2]{1, 1}),

		//+x
		Vertex(new GLfloat[4]{ side + shift_lr, -side + shift_y, -side + shift_ud, 1.0}, new GLfloat[4]{1.0, 0, 0, 0.0}, new GLfloat[2]{0, 0}),
		Vertex(new GLfloat[4]{ side + shift_lr,  side + shift_y, -side + shift_ud, 1.0}, new GLfloat[4]{1.0, 0, 0, 0.0}, new GLfloat[2]{0, 1}),
		Vertex(new GLfloat[4]{ side + shift_lr, -side + shift_y,  side + shift_ud, 1.0}, new GLfloat[4]{1.0, 0, 0, 0.0}, new GLfloat[2]{1, 0}),
					 		 															  								 
		Vertex(new GLfloat[4]{ side + shift_lr, -side + shift_y,  side + shift_ud, 1.0}, new GLfloat[4]{1.0, 0, 0, 0.0}, new GLfloat[2]{1, 0}),
		Vertex(new GLfloat[4]{ side + shift_lr,  side + shift_y, -side + shift_ud, 1.0}, new GLfloat[4]{1.0, 0, 0, 0.0}, new GLfloat[2]{0, 1}),
		Vertex(new GLfloat[4]{ side + shift_lr,  side + shift_y,  side + shift_ud, 1.0}, new GLfloat[4]{1.0, 0, 0, 0.0}, new GLfloat[2]{1, 1}),

		//-z
		Vertex(new GLfloat[4]{-side + shift_lr, -side + shift_y, -side + shift_ud, 1.0}, new GLfloat[4]{0, -1.0, 0, 0.0}, new GLfloat[2]{0, 0}),
		Vertex(new GLfloat[4]{ side + shift_lr, -side + shift_y, -side + shift_ud, 1.0}, new GLfloat[4]{0, -1.0, 0, 0.0}, new GLfloat[2]{1, 0}),
		Vertex(new GLfloat[4]{-side + shift_lr, -side + shift_y,  side + shift_ud, 1.0}, new GLfloat[4]{0, -1.0, 0, 0.0}, new GLfloat[2]{0, 1}),
					 	  
		Vertex(new GLfloat[4]{-side + shift_lr, -side + shift_y,  side + shift_ud, 1.0}, new GLfloat[4]{0, -1.0, 0, 0.0}, new GLfloat[2]{0, 1}),
		Vertex(new GLfloat[4]{ side + shift_lr, -side + shift_y, -side + shift_ud, 1.0}, new GLfloat[4]{0, -1.0, 0, 0.0}, new GLfloat[2]{1, 0}),
		Vertex(new GLfloat[4]{ side + shift_lr, -side + shift_y,  side + shift_ud, 1.0}, new GLfloat[4]{0, -1.0, 0, 0.0}, new GLfloat[2]{1, 1}),

		//z+
		Vertex(new GLfloat[4]{-side + shift_lr,  side + shift_y, -side + shift_ud, 1.0}, new GLfloat[4]{0,  1.0,  0, 0.0}, new GLfloat[2]{0, 0}),
		Vertex(new GLfloat[4]{-side + shift_lr,  side + shift_y,  side + shift_ud, 1.0}, new GLfloat[4]{0,  1.0,  0, 0.0}, new GLfloat[2]{0, 1}),
		Vertex(new GLfloat[4]{ side + shift_lr,  side + shift_y, -side + shift_ud, 1.0}, new GLfloat[4]{0,  1.0,  0, 0.0}, new GLfloat[2]{1, 0}),
						 
		Vertex(new GLfloat[4]{ side + shift_lr,  side + shift_y, -side + shift_ud, 1.0}, new GLfloat[4]{0,  1.0,  0, 0.0}, new GLfloat[2]{1, 0}),
		Vertex(new GLfloat[4]{-side + shift_lr,  side + shift_y,  side + shift_ud, 1.0}, new GLfloat[4]{0,  1.0,  0, 0.0}, new GLfloat[2]{0, 1}),
		Vertex(new GLfloat[4]{ side + shift_lr,  side + shift_y,  side + shift_ud, 1.0}, new GLfloat[4]{0,  1.0,  0, 0.0}, new GLfloat[2]{1, 1}),
						 
		//y-			 
		Vertex(new GLfloat[4]{-side + shift_lr, -side + shift_y, -side + shift_ud, 1.0}, new GLfloat[4]{0, 0, -1.0, 0.0}, new GLfloat[2]{0, 0}),
		Vertex(new GLfloat[4]{-side + shift_lr,  side + shift_y, -side + shift_ud, 1.0}, new GLfloat[4]{0, 0, -1.0, 0.0}, new GLfloat[2]{0, 1}),
		Vertex(new GLfloat[4]{ side + shift_lr, -side + shift_y, -side + shift_ud, 1.0}, new GLfloat[4]{0, 0, -1.0, 0.0}, new GLfloat[2]{1, 0}),
					 	  															 			   					 		  	   		  
		Vertex(new GLfloat[4]{ side + shift_lr, -side + shift_y, -side + shift_ud, 1.0}, new GLfloat[4]{0, 0, -1.0, 0.0}, new GLfloat[2]{1, 0}),
		Vertex(new GLfloat[4]{-side + shift_lr,  side + shift_y, -side + shift_ud, 1.0}, new GLfloat[4]{0, 0, -1.0, 0.0}, new GLfloat[2]{0, 1}),
		Vertex(new GLfloat[4]{ side + shift_lr,  side + shift_y, -side + shift_ud, 1.0}, new GLfloat[4]{0, 0, -1.0, 0.0}, new GLfloat[2]{1, 1}),
						 
		//y+			 
		Vertex(new GLfloat[4]{-side + shift_lr, -side + shift_y,  side + shift_ud, 1.0}, new GLfloat[4]{0, 0,  1.0, 0.0}, new GLfloat[2]{0, 0}),
		Vertex(new GLfloat[4]{ side + shift_lr, -side + shift_y,  side + shift_ud, 1.0}, new GLfloat[4]{0, 0,  1.0, 0.0}, new GLfloat[2]{1, 0}),
		Vertex(new GLfloat[4]{-side + shift_lr,  side + shift_y,  side + shift_ud, 1.0}, new GLfloat[4]{0, 0,  1.0, 0.0}, new GLfloat[2]{0, 1}),
					 	  								  				   			 		  	   					 		  	   		  
		Vertex(new GLfloat[4]{-side + shift_lr,  side + shift_y,  side + shift_ud, 1.0}, new GLfloat[4]{0, 0,  1.0, 0.0}, new GLfloat[2]{0, 1}),
		Vertex(new GLfloat[4]{ side + shift_lr, -side + shift_y,  side + shift_ud, 1.0}, new GLfloat[4]{0, 0,  1.0, 0.0}, new GLfloat[2]{1, 0}),
		Vertex(new GLfloat[4]{ side + shift_lr,  side + shift_y,  side + shift_ud, 1.0}, new GLfloat[4]{0, 0,  1.0, 0.0}, new GLfloat[2]{1, 1}),
	};
	return vertices;
}