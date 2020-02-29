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

void LightObject::IntensityLightUniform(int location)
{
	glUniform3fv(location, 1, glm::value_ptr(AmbirntIntensity));
}

void LightObject::SendParmInShader(int location)
{
	SendParmInShader(location, "SpotLightInfo");
}

void LightObject::SendParmInShader(int location, std::string nameBlock)
{
	int index_SLI = glGetUniformBlockIndex(location, nameBlock.c_str());
	if (index_SLI != GL_INVALID_INDEX)
	{
		int blockSize;
		glGetActiveUniformBlockiv(location, index_SLI, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize);
		unsigned char* blockBuffer = new unsigned char[blockSize];
		std::string names[5] = { nameBlock + ".position_lgh", nameBlock + ".intensity_lgh", nameBlock + ".direction_lgh", nameBlock + ".exponent_lgh", nameBlock + ".cutoff_lgh" };
		const char* names_char[5] = { (names[0]).c_str(), (names[1]).c_str(), (names[2]).c_str(), (names[3]).c_str(), (names[4]).c_str() };
		GLuint* indices = new GLuint[5];
		glGetUniformIndices(location, 5, names_char, indices);
		int* offset = new int[5];
		glGetActiveUniformsiv(location, 5, indices, GL_UNIFORM_OFFSET, offset);
	}
}
