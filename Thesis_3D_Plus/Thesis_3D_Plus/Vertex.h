#pragma once
#include <vector>
#include <glm\gtc\constants.hpp>
#include <glm\trigonometric.hpp>
#include <glm\vec2.hpp>
#include <glm\vec3.hpp>
#include <glm\vec4.hpp>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <GLFW\glfw3native.h>

struct Vertex
{
	glm::vec4  _Position;
	glm::vec4  _NormalCoord;
	glm::vec2  _TexCoord;
	Vertex()
	{
		_Position = glm::vec4(0);
		_NormalCoord = glm::vec4(0);
		_TexCoord = glm::vec2(0);
	}

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
		//координаты дл€ треуголника, нормаль, текстурные координаты
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

static std::vector<Vertex> CreateSolidCube(float side, glm::vec3 position)
{
	return CreateSolidCube(side, position.x, position.y, position.z);
}
static void Spherecoord(glm::vec4** coord_s, glm::vec4** normal_s, glm::vec2** texcoord, float r, int nx, int ny, float k1, float k2)
{
	int ix, iy, i = 0;
	double x, y, z, sy, cy, sy1, cy1, sx, cx, piy, pix, ay, ay1, ax, tx, ty, ty1, dnx, dny, diy;
	dnx = 1.0 / (double)nx;
	dny = 1.0 / (double)ny;

	piy = glm::pi<float>() * dny;
	pix = glm::pi<float>() * dnx;
	for (iy = 0; iy < ny; iy++)
	{
		diy = (double)iy;
		ay = diy * piy;
		sy = glm::sin(ay);
		cy = glm::cos(ay);
		ty = diy * dny;
		ay1 = ay + piy;
		sy1 = glm::sin(ay1);
		cy1 = glm::cos(ay1);
		ty1 = ty + dny;
		for (ix = 0; ix <= nx; ix++)
		{
			ax = 2.0 * ix * pix;
			sx = k1 * glm::sin(ax);
			cx = k2 * glm::cos(ax);
			x = r * sy * cx;
			y = r * sy * sx;
			z = -r * cy;
			tx = (double)ix * dnx;
			//  оординаты нормали в текущей вершине
			(*normal_s)[i] = glm::vec4((float)x, (float)y, (float)z, 0.0f); // Ќормаль направлена от центра
			(*coord_s)[i] = glm::vec4((float)x, (float)y, (float)z, 1.0f);
			(*texcoord)[i] = glm::vec2((float)tx, (float)ty);
			i++;
			//  оординаты текстуры в текущей вершине
			x = r * sy1 * cx;
			y = r * sy1 * sx;
			z = -r * cy1;
			(*normal_s)[i] = glm::vec4((float)x, (float)y, (float)z, 0.0f);
			(*coord_s)[i] = glm::vec4((float)x, (float)y, (float)z, 1.0f);
			(*texcoord)[i] = glm::vec2((float)tx, (float)ty1);
			i++;
		}
	}
}

static std::vector<Vertex> CreateSphere(float side, glm::vec3 position, int nx, int ny, float k1, float k2)
{
	glm::vec4* coord_s = new glm::vec4[(nx + 1) * 2 * ny];
	glm::vec2* texcoord = new glm::vec2[(nx + 1) * 2 * ny];
	glm::vec4* normal_s = new glm::vec4[(nx + 1) * 2 * ny];
	Spherecoord(&coord_s, &normal_s, &texcoord, side / 2, nx, ny, k1, k2);
	std::vector<Vertex> vertices;
	vertices.resize((nx + 1) * 6 * ny);
	for (int i = 0; i < (nx + 1) * 2 * ny; i++)
	{
		coord_s[i].x += position.x;
		coord_s[i].y += position.y;
		coord_s[i].z += position.z;
	}
	for (int i = 0, j = 0; j < (nx + 1) * 2 * ny - 3; i += 6, j += 2)
	{

		vertices[i] = Vertex(coord_s[j], normal_s[j], texcoord[j]);
		vertices[i + 1] = Vertex(coord_s[j + 2], normal_s[j + 2], texcoord[j + 2]);
		vertices[i + 2] = Vertex(coord_s[j + 1], normal_s[j + 1], texcoord[j + 1]);
	}
	for (int i = 3, j = 1; j < (nx + 1) * 2 * ny - 3; i += 6, j += 2)
	{

		vertices[i] = Vertex(coord_s[j], normal_s[j], texcoord[j]);
		vertices[i + 1] = Vertex(coord_s[j + 1], normal_s[j + 1], texcoord[j + 1]);
		vertices[i + 2] = Vertex(coord_s[j + 2], normal_s[j + 2], texcoord[j + 2]);
	}
	return vertices;
}
