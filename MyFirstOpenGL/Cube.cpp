#include "Cube.h"

void Cube::Update()
{
	Primitive::Update();

	GetTransform()->position = GetTransform()->position + GetTransform()->forward * GetFVelocity();
	GetTransform()->rotation = GetTransform()->rotation + glm::vec3(0.f, 1.f, 0.f) * GetFAngulargVelocity();

	if (GetTransform()->position.y >= 0.5f || GetTransform()->position.y <= -0.5f)
	{
		GetTransform()->forward = GetTransform()->forward * -1.f;
	}

	glUniform1i(glGetUniformLocation(SHADER.compiledPrograms[0], "isNotPyramid"), 1);

	//Definimos que queremos dibujar
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 14);

	//Dejamos de usar el VAO indicado anteriormente
	glBindVertexArray(0);
}

glm::mat4 Cube::ApplyMatrix()
{
	SetModelMatrix(glm::mat4(1.0f));

	glm::mat4 cubeTranslaionMatrix = GenerateTranslationMatrix(GetTransform()->position);
	glm::mat4 cubeRotationMatrix = GenerateRotationMatrix(glm::vec3(0.f, 1.f, 0.f), GetTransform()->rotation.y);

	SetModelMatrix(cubeTranslaionMatrix * cubeRotationMatrix * GetModelMatrix());

	return GetModelMatrix();
}
