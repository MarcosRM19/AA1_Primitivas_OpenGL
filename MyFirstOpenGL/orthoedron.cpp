#include "Orthoedron.h"

void Orthoedron::Update(int programIndex)
{
	Primitive::Update(programIndex);

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
	
	ApplyMatrix();

	//Definimos que queremos dibujar
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 14);

	//Dejamos de usar el VAO indicado anteriormente
	glBindVertexArray(0);
}

void Orthoedron::ApplyMatrix()
{
	SetTransitionMatrix(glm::mat4(1.0f));
	SetRotationMatrix(glm::mat4(1.0f));
	SetScaleMatrix(glm::mat4(1.0f));

	SetScaleMatrix(GenerateScaleMatrix(GetTransform()->scale));
	SetRotationMatrix(GenerateRotationMatrix(glm::vec3(0.f, 0.f, 1.f), GetTransform()->rotation.z));

}

void Orthoedron::InitVao()
{
	Primitive::InitVao();

}
