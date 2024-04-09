#include "Cube.h"

glm::mat4 Cube::ApplyMatrix()
{
	SetModelMatrix(glm::mat4(1.0f));

	GetTransform()->SetPosition(GetTransform()->GetPosition() + GetTransform()->GetForward() * GetFVelocity());
	GetTransform()->SetRotation(GetTransform()->GetRotation() + glm::vec3(0.f, 1.f, 0.f) * GetFAngulargVelocity());

	if (GetTransform()->GetPosition().y >= 0.5f || GetTransform()->GetPosition().y <= -0.5f)
	{
		GetTransform()->SetForward(GetTransform()->GetForward() * -1.f);
	}

	glm::mat4 cubeTranslaionMatrix = GenerateTranslationMatrix(GetTransform()->GetPosition());
	glm::mat4 cubeRotationMatrix = GenerateRotationMatrix(glm::vec3(0.f, 1.f, 0.f), GetTransform()->GetRotation().y);

	SetModelMatrix(cubeTranslaionMatrix * cubeRotationMatrix * GetModelMatrix());

	return GetModelMatrix();
}
