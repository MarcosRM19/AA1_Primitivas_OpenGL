#include "orthoedron.h"

glm::mat4 Orthoedron::ApplyMatrix()
{
	SetModelMatrix(glm::mat4(1.0f));

	glm::vec3 scale = GetTransform()->GetScale();

	if (isIncreasing)
		scale.y = scale.y / GetFScaleVelocity();
	else
		scale.y = scale.y * GetFScaleVelocity();


	GetTransform()->SetScale(scale);
	GetTransform()->SetRotation(GetTransform()->GetRotation() + glm::vec3(0.f, 0.f, 1.f) * GetFAngulargVelocity());

	if (GetTransform()->GetScale().y >= 1.f || GetTransform()->GetScale().y <= 0.5f)
	{
		isIncreasing = !isIncreasing;
	}

	glm::mat4 cubeScaleMatrix = GenerateScaleMatrix(GetTransform()->GetScale());
	glm::mat4 cubeRotationMatrix = GenerateRotationMatrix(glm::vec3(0.f, 0.f, 1.f), GetTransform()->GetRotation().z);

	SetModelMatrix(cubeRotationMatrix * cubeScaleMatrix * GetModelMatrix());

	return GetModelMatrix();
}
