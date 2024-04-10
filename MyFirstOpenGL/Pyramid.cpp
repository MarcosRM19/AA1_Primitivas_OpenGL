#include "Pyramid.h"

glm::mat4 Pyramid::ApplyMatrix()
{
	SetModelMatrix(glm::mat4(1.0f));

	GetTransform()->position = GetTransform()->position + GetTransform()->forward * GetFVelocity();
	GetTransform()->rotation = GetTransform()->rotation + glm::vec3(1.f, 1.f, 0.f) * GetFAngulargVelocity();

	if (GetTransform()->position.y >= 0.5f || GetTransform()->position.y <= -0.5f)
	{
		GetTransform()->forward = GetTransform()->forward * -1.f;
	}

	glm::mat4 pyramidTranslaionMatrix = GenerateTranslationMatrix(GetTransform()->position);
	glm::mat4 pyramidRotationMatrixY = GenerateRotationMatrix(glm::vec3(0.f, 1.f, 0.f), GetTransform()->rotation.y);
	glm::mat4 pyramidRotationMatrixX = GenerateRotationMatrix(glm::vec3(1.f, 0.f, 0.f), GetTransform()->rotation.x);

	SetModelMatrix(pyramidTranslaionMatrix * pyramidRotationMatrixX * pyramidRotationMatrixY * GetModelMatrix());

	return GetModelMatrix();
}
