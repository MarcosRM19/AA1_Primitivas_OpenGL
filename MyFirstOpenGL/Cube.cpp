#include "Cube.h"

glm::mat4 Cube::ApplyMatrix()
{
	SetModelMatrix(glm::mat4(1.0f));

	GetTransform()->position = GetTransform()->position + GetTransform()->forward * GetFVelocity();
	GetTransform()->rotation = GetTransform()->rotation + glm::vec3(0.f, 1.f, 0.f) * GetFAngulargVelocity();

	if (GetTransform()->position.y >= 0.5f || GetTransform()->position.y <= -0.5f)
	{
		GetTransform()->forward = GetTransform()->forward * -1.f;
	}

	glm::mat4 cubeTranslaionMatrix = GenerateTranslationMatrix(GetTransform()->position);
	glm::mat4 cubeRotationMatrix = GenerateRotationMatrix(glm::vec3(0.f, 1.f, 0.f), GetTransform()->rotation.y);

	SetModelMatrix(cubeTranslaionMatrix * cubeRotationMatrix * GetModelMatrix());

	return GetModelMatrix();
}
