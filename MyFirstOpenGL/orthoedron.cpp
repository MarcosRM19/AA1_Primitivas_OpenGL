#include "Orthoedron.h"

void Orthoedron::Update()
{
	glm::vec3 scale = GetTransform()->scale;

	if (isIncreasing)
		scale.y = scale.y / (1 - GetFScaleVelocity());
	else
		scale.y = scale.y * (1 - GetFScaleVelocity());


	GetTransform()->scale = scale;
	GetTransform()->rotation = GetTransform()->rotation + glm::vec3(0.f, 0.f, 1.f) * GetFAngulargVelocity();

	if (GetTransform()->scale.y >= 1.f || GetTransform()->scale.y <= 0.5f)
	{
		isIncreasing = !isIncreasing;
	}
}

glm::mat4 Orthoedron::ApplyMatrix()
{
	SetModelMatrix(glm::mat4(1.0f));

	glm::mat4 cubeScaleMatrix = GenerateScaleMatrix(GetTransform()->scale);
	glm::mat4 cubeRotationMatrix = GenerateRotationMatrix(glm::vec3(0.f, 0.f, 1.f), GetTransform()->rotation.z);

	SetModelMatrix(cubeRotationMatrix * cubeScaleMatrix * GetModelMatrix());

	return GetModelMatrix();
}
