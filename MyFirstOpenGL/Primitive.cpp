#include "Primitive.h"

Primitive::Primitive(glm::vec3 position, glm::vec3 rotation, glm::vec3 forward, glm::vec3 scale, float fVelocity, float fAngularVelocity, std::vector<GLfloat> point, float fScaleVelocity)
{
	transform = new Transform(position, rotation, forward, scale);
	this->fVelocity = fVelocity;
	this->fAngularVelocity = fAngularVelocity;
	this->point = point;
	this->fScaleVelocity = fScaleVelocity;
}

glm::mat4 Primitive::GenerateTranslationMatrix(glm::vec3 translation)
{
	return glm::translate(glm::mat4(1.f), translation);;
}

glm::mat4 Primitive::GenerateRotationMatrix(glm::vec3 axis, float fDegrees)
{
	return glm::rotate(glm::mat4(1.f), glm::radians(fDegrees), glm::normalize(axis));
}

glm::mat4 Primitive::GenerateScaleMatrix(glm::vec3 newScale)
{
	return glm::scale(glm::mat4(1.f), newScale);
}

Transform* Primitive::GetTransform()
{
	return transform;
}

glm::mat4 Primitive::GetModelMatrix()
{
	return modelMatrix;
}

float Primitive::GetFVelocity()
{
	return fVelocity;
}

float Primitive::GetFAngulargVelocity()
{
	return fAngularVelocity;
}

float Primitive::GetFScaleVelocity()
{
	return fScaleVelocity;
}

GLfloat* Primitive::GetPointData()
{
	GLfloat* pointData = point.data();
	return pointData;
}

std::vector<GLfloat> Primitive::GetPoint()
{
	return point;
}

void Primitive::SetModelMatrix(glm::mat4 matrix)
{
	modelMatrix = matrix;
}