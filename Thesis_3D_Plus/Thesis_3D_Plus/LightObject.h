#pragma once
#include "RenderObject.h"
#include <glm\gtc/type_ptr.hpp>


class LightObject
{

public:
	glm::vec3 Angel_speed;
	glm::vec4 Attribute;
	glm::vec3 LightVecNormalized;
	glm::vec3 AmbirntIntensity;
	glm::vec4 ColorRadiation;
	RenderObject LightRenderObject; // наследование идет к черту 
	LightObject(std::vector<Vertex> vertices, glm::vec4 color, glm::vec4 color_choice, glm::vec3 position, glm::vec4 attribute, glm::vec3 lighVecNormalized, glm::vec3 ambientIntensity, glm::vec3 angle_speed);
	~LightObject();
	void SetColorRadiation(glm::vec4 color);
	void PositionLightUniform(int location);
	void MatrixViewUnifomr(int location);
};