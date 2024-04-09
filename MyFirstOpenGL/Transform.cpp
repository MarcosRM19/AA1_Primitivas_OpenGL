#include "Transform.h"

Transform::Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 forward, glm::vec3 scale)
{
	this->position = position;
	this->rotation = rotation;
	this->forward = forward;
	this->scale = scale;
}

void Transform::SetPosition(glm::vec3 newPosition)
{
	position = newPosition;
}

void Transform::SetRotation(glm::vec3 newRotation)
{
	rotation = newRotation;
}

void Transform::SetForward(glm::vec3 newForward)
{
	forward = newForward;
}

void Transform::SetScale(glm::vec3 newScale)
{
	scale = newScale;
}

glm::vec3 Transform::GetPosition()
{
	return position;
}

glm::vec3 Transform::GetRotation()
{
	return rotation;
}

glm::vec3 Transform::GetForward()
{
	return forward;
}

glm::vec3 Transform::GetScale()
{
	return scale;
}
