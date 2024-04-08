#include "Primitive.h"

Primitive::Primitive(glm::vec3 position, glm::vec3 rotation, glm::vec3 forward, float fVelocity, float fAngularVelocity)
{
	this->position = position;
	this->rotation = rotation;
	this->forward = forward;
	this->fVelocity = fVelocity;
	this->fAngularVelocity = fAngularVelocity;
}

glm::mat4 Primitive::GenerateTranslationMatrix(glm::vec3 translation)
{
	return glm::translate(glm::mat4(1.f), translation);;
}

glm::mat4 Primitive::GenerateRotationMatrix(glm::vec3 axis, float fDegrees)
{
	return glm::rotate(glm::mat4(1.f), glm::radians(fDegrees), glm::normalize(axis));
}

glm::mat4 GenerateScaleMatrix(glm::vec3 newScale)
{
	return glm::scale(glm::mat4(1.f), newScale);
}

void Primitive::SetPosition(glm::vec3 newPosition)
{
	position = newPosition;
}

void Primitive::SetRotation(glm::vec3 newRotation)
{
	rotation = newRotation;
}

void Primitive::SetForward(glm::vec3 newForward)
{
	forward = newForward;
}

glm::vec3 Primitive::GetPosition()
{
	return position;
}

glm::vec3 Primitive::GetRotation()
{
	return rotation;
}

glm::vec3 Primitive::GetForward()
{
	return forward;
}

float Primitive::GetFVelocity()
{
	return fVelocity;
}

float Primitive::GetFAngulargVelocity()
{
	return fAngularVelocity;
}
