#pragma once
#include "RenderObject.h"
#include <glm\gtc/type_ptr.hpp>


class LightObject
{

public:
	glm::vec3 Angel_speed;
	glm::vec4 Attribute;
	glm::vec3 LightVecNormalized;
	glm::vec3 AmbientIntensity;
	glm::vec4 ColorRadiation;
	GLuint uboHandle = -1;
	int blockSize = -1;
	RenderObject LightRenderObject; // наследование идет к черту 
	LightObject(std::vector<Vertex> vertices, glm::vec4 color, glm::vec4 color_choice, glm::vec3 position, glm::vec4 attribute, glm::vec3 lighVecNormalized, glm::vec3 ambientIntensity, glm::vec3 angle_speed, int program = -1, std::string nameBlock = "");
	~LightObject();
	void SetColorRadiation(glm::vec4 color);
	void PositionLightUniform(int location);
	void MatrixViewUnifomr(int location);
	void IntensityLightUniform(int location);
	void InitBufferForBlock(int program);
	void InitBufferForBlock(int program, std::string nameBlock);
	void UpdatePositionForBlock();
	void UpdateBufferForBlock(int program);
	void UpdateBufferForBlock(int program, std::string nameBlock);
};