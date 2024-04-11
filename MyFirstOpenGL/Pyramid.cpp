#include "Pyramid.h"

void Pyramid::Update()
{
	Primitive::Update();

	currentTime = glfwGetTime();

	GetTransform()->position = GetTransform()->position + GetTransform()->forward * GetFVelocity();
	GetTransform()->rotation = GetTransform()->rotation + glm::vec3(1.f, 1.f, 0.f) * GetFAngulargVelocity();

	if (GetTransform()->position.y >= 0.5f || GetTransform()->position.y <= -0.5f)
	{
		GetTransform()->forward = GetTransform()->forward * -1.f;
	}

	glUniform1i(glGetUniformLocation(SHADER.compiledPrograms[0], "isNotPyramid"), 0);
	glUniform1f(glGetUniformLocation(SHADER.compiledPrograms[0], "u_Time"), currentTime);

	//Definimos que queremos dibujar
	glDrawArrays(GL_TRIANGLE_FAN, 0, 6);
	glDrawArrays(GL_TRIANGLE_STRIP, 6, 4);

	//Dejamos de usar el VAO indicado anteriormente
	glBindVertexArray(0);
}

glm::mat4 Pyramid::ApplyMatrix()
{
	SetModelMatrix(glm::mat4(1.0f));

	glm::mat4 pyramidTranslaionMatrix = GenerateTranslationMatrix(GetTransform()->position);
	glm::mat4 pyramidRotationMatrixY = GenerateRotationMatrix(glm::vec3(0.f, 1.f, 0.f), GetTransform()->rotation.y);
	glm::mat4 pyramidRotationMatrixX = GenerateRotationMatrix(glm::vec3(1.f, 0.f, 0.f), GetTransform()->rotation.x);

	SetModelMatrix(pyramidTranslaionMatrix * pyramidRotationMatrixX * pyramidRotationMatrixY *  GetModelMatrix());

	return GetModelMatrix();
}
