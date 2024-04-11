#include "Pyramid.h"

void Pyramid::Update(int programIndex)
{
	Primitive::Update(programIndex);

	currentTime = glfwGetTime();

	GetTransform()->position = GetTransform()->position + GetTransform()->forward * GetFVelocity();
	GetTransform()->rotation = GetTransform()->rotation + glm::vec3(1.f, 1.f, 0.f) * GetFAngulargVelocity();

	if (GetTransform()->position.y >= 0.5f || GetTransform()->position.y <= -0.5f)
	{
		GetTransform()->forward = GetTransform()->forward * -1.f;
	}

	ApplyMatrix();

	glUniform1f(glGetUniformLocation(SHADER.compiledPrograms[programIndex], "u_Time"), currentTime);

	//Definimos que queremos dibujar
	glDrawArrays(GL_TRIANGLE_FAN, 0, 6);
	glDrawArrays(GL_TRIANGLE_STRIP, 6, 4);

	//Dejamos de usar el VAO indicado anteriormente
	glBindVertexArray(0);
}

void Pyramid::ApplyMatrix()
{
	SetTransitionMatrix(glm::mat4(1.0f));
	SetRotationMatrix(glm::mat4(1.0f));
	SetScaleMatrix(glm::mat4(1.0f));

	SetTransitionMatrix(GenerateTranslationMatrix(GetTransform()->position));
	SetRotationMatrix(GenerateRotationMatrix(glm::vec3(1.f, 0.f, 0.f), GetTransform()->rotation.x) 
		* GenerateRotationMatrix(glm::vec3(0.f, 1.f, 0.f), GetTransform()->rotation.y));

}

void Pyramid::InitVao()
{
	Primitive::InitVao();

}
