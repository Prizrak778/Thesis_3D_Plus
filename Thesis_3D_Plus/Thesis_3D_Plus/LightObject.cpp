#include "LightObject.h"


LightObject::LightObject(std::vector<Vertex> vertices, glm::vec4 color, glm::vec4 color_choice, glm::vec3 position, glm::vec4 attribute, glm::vec3 lighVecNormalized, glm::vec3 ambientIntensity, glm::vec3 angle_speed, int program, std::string nameBlock)
{
	LightRenderObject = RenderObject(vertices, position, color, color_choice);
	LightRenderObject.TybeObject = LightSourceObject;
	Angel_speed = angle_speed;
	Attribute = attribute;
	LightVecNormalized = lighVecNormalized;
	AmbientIntensity = ambientIntensity;
	ColorRadiation = color;
	
	if (program != -1)
	{
		if (nameBlock.empty()) InitBufferForBlock(program);
		else InitBufferForBlock(program, nameBlock);
	}
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
	glUniform3fv(location, 1, glm::value_ptr(AmbientIntensity));
}

void LightObject::InitBufferForBlock(int program)
{
	InitBufferForBlock(program, "SpotLightInfo");
}

void LightObject::InitBufferForBlock(int program, std::string nameBlock)
{
	const GLchar *nameB = nameBlock.c_str();
	int index_SLI = glGetUniformBlockIndex(program, nameB);
	if (index_SLI != GL_INVALID_INDEX)
	{
		glGetActiveUniformBlockiv(program, index_SLI, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize);
		unsigned char* blockBuffer = new unsigned char[blockSize];
		std::string names[5] = { nameBlock + ".position_lgh", nameBlock + ".intensity_lgh", nameBlock + ".direction_lgh", nameBlock + ".exponent_lgh", nameBlock + ".cutoff_lgh" };
		const char* names_char[5] = { (names[0]).c_str(), (names[1]).c_str(), (names[2]).c_str(), (names[3]).c_str(), (names[4]).c_str() };
		GLuint* indices = new GLuint[5];
		glGetUniformIndices(program, 5, names_char, indices);
		int* offset = new int[5];
		glGetActiveUniformsiv(program, 5, indices, GL_UNIFORM_OFFSET, offset);
		
		float position_lgh[] = { LightRenderObject.position_obj.x, LightRenderObject.position_obj.y, LightRenderObject.position_obj.z, 0.0f };
		float intensity_lgh[] = { AmbientIntensity.x, AmbientIntensity.y, AmbientIntensity.z }; //интенсивность света
		float direction_lgh[] = { LightVecNormalized.x, LightVecNormalized.y, LightVecNormalized.z }; //направление света
		float exponent[] = { 1.0f }; // Экспанента углового ослабления света
		float cutoff[] = { 30.0f }; //угол отсечения

		memcpy(blockBuffer + offset[0], position_lgh, sizeof(float) * 4);
		memcpy(blockBuffer + offset[1], intensity_lgh, sizeof(float) * 3);
		memcpy(blockBuffer + offset[2], direction_lgh, sizeof(float) * 3);
		memcpy(blockBuffer + offset[3], exponent, sizeof(float));
		memcpy(blockBuffer + offset[4], cutoff, sizeof(float));

		glGenBuffers(1, &uboHandle);
		glBindBuffer(GL_UNIFORM_BUFFER, uboHandle);
		glBufferData(GL_UNIFORM_BUFFER, blockSize, blockBuffer, GL_DYNAMIC_DRAW);
	}
}
