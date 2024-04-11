#include "Cube.h"

void Cube::Update(int programIndex)
{
	Primitive::Update(programIndex);

	GetTransform()->position = GetTransform()->position + GetTransform()->forward * GetFVelocity();
	GetTransform()->rotation = GetTransform()->rotation + glm::vec3(0.f, 1.f, 0.f) * GetFAngulargVelocity();

	if (GetTransform()->position.y >= 0.5f || GetTransform()->position.y <= -0.5f)
	{
		GetTransform()->forward = GetTransform()->forward * -1.f;
	}

	ApplyMatrix();

	//Definimos que queremos dibujar
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 14);

	//Dejamos de usar el VAO indicado anteriormente
	glBindVertexArray(0);
}

void Cube::ApplyMatrix()
{
	SetTransitionMatrix(glm::mat4(1.0f));
	SetRotationMatrix(glm::mat4(1.0f));
	SetScaleMatrix(glm::mat4(1.0f));

	SetTransitionMatrix(GenerateTranslationMatrix(GetTransform()->position));
	SetRotationMatrix(GenerateRotationMatrix(glm::vec3(0.f, 1.f, 0.f), GetTransform()->rotation.y));
}

void Cube::InitVao()
{
	Primitive::InitVao();
}
