#include "LightObject.h"


LightObject::LightObject(std::vector<Vertex> vertices, glm::vec4 color, glm::vec4 color_choice, glm::vec3 position, glm::vec4 attribute, glm::vec3 lighVecNormalized, glm::vec3 ambientIntensity, glm::vec3 angle_speed)
{
	LightRenderObject = RenderObject(vertices, position, color, color_choice);
	LightRenderObject.TybeObject = LightSourceObject;
	Angel_speed = angle_speed;
	Attribute = attribute;
	LightVecNormalized = lighVecNormalized;
	AmbirntIntensity = ambientIntensity;
	ColorRadiation = color;
}

LightObject::~LightObject()
{
}

void LightObject::SetColorRadiation(glm::vec4 color)
{
	ColorRadiation = color;
}

void LightObject::PositionLightUniform(int location)
{
	glm::vec4 position_v4 = glm::vec4(LightRenderObject.position_obj, 1);
	position_v4 = LightRenderObject.ModelMatrix * position_v4;
	glUniform4fv(location, 1, glm::value_ptr(position_v4));
}

void LightObject::MatrixViewUnifomr(int location)
{
	glm::mat4 modelview = glm::translate(glm::vec3(0.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(location, 1, false, glm::value_ptr(modelview));
}
